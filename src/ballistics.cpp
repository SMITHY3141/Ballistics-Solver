

#include "ballistics.hpp"
#include "rootsolver.hpp"
#include <VECTORS/vectors.hpp>
#include <VECTORS/matrices.hpp>
#include <iostream>



namespace blstc {
    std::ostream& operator<<(std::ostream& os, const Solution& s) {
        os << "SOLUTION" << '\n'
           << "azimuth: " << s.azimuth << " rads" << '\n'
           << "elevation: "  << s.elevation << " rads" << '\n'
           << "time: " << s.time << " s" << '\n'
           << "error: " << s.error << " m";

        return os; // so we can chain together std::cout << inputs << more_inputs
    }

    std::ostream& operator<<(std::ostream& os, const Conditions& c) {
        os << "CONDITIONS" << '\n'
           << "speed: " << c.speed << " m/s" << '\n'
           << "drag: "  << c.drag << '\n'
           << "gravity: " << c.gravity << " m/s/s" << '\n'
           << "target: (" << c.x << ", " << c.y << ", " << c.z << ") m\n"
           << "velocity: (" << c.vx << ", " << c.vy << ", " << c.vz << ") m/s\n"
           << "max: " << c.max << '\n'
           << "desired error: " << c.desired << " m";

        return os;
    }

    // just makes a call to the root solver
    // has to process 
    Solution solve(const Conditions &c) {

        float azimuth = std::atan2(c.y, c.x); // initial guesses
        float elevation = std::atan2(c.z, std::sqrt(c.x * c.x + c.y * c.y));

        Vector<3> guess{azimuth, elevation, time_to_hit(elevation, c)};
        Vector<3> sol = solver::solve<3>(
                c.max,
                guess,
                c.desired,
                [c](const Vector<3> &vars) -> Vector<3> { return error(vars, c); }, 
                [c](const Vector<3> &state) -> Matrix<3, 3> { return jacobian(state, c); }
                );

        Solution s;
        s.azimuth = sol[0];
        s.elevation = sol[1];
        s.time = sol[2];

        Vector<3> miss = error(sol, c);
        s.error = miss.length();

        return s;

    }

    // Projectile position at a given launch and time after launch.
    Vector<3> position(const Vector<3> &vars, const Conditions &c) {
        // was having some precision issues, promoting to double fixed it
        double g = c.gravity;
        double d = c.drag;
        double v = c.speed;

        float a = vars[0];
        float p = vars[1];
        float t = vars[2];

        double exp = std::exp(-d * t);

        float x = v * std::cos(a) * std::cos(p) * (1 - exp) / d;
        float y = v * std::sin(a) * std::cos(p) * (1 - exp) / d;
        float z = g * (exp/d + t - 1/d)/d + v * std::sin(p) * (1 - exp) / d;
        
        Vector<3> position{x, y, z};

        return position;

    }

    // Difference in predicted projectile position and extrapolated
    // target position.
    Vector<3> error(const Vector<3> &vars, const Conditions &c) {
        Vector<3> pos = position(vars, c);

        Vector<3> target{c.x, c.y, c.z};
        Vector<3> vel{c.vx, c.vy, c.vz};
        Vector<3> extrapolated = target + vel * vars[2];

        return pos - extrapolated;
    
    }

    // Partial derivatives of the error terms wrt azimuth angle, elevation
    // angle, and time after launch.
    Matrix<3, 3> jacobian(const Vector<3> &state, const Conditions &c) {
        float g = c.gravity;
        float d = c.drag;
        float v = c.speed;

        float a = state[0];
        float p = state[1];
        float t = state[2];

        float exp = std::exp(-d * t);

        float x_a = -v * std::sin(a) * std::cos(p) * (1 - exp) / d;
        float x_p = -v * std::cos(a) * std::sin(p) * (1 - exp) / d;
        float x_t = v * std::cos(a) * std::cos(p) * exp - c.vx;

        float y_a = v * std::cos(a) * std::cos(p) * (1 - exp) / d;
        float y_p = -v * std::sin(a) * std::sin(p) * (1- exp) / d;
        float y_t = v * std::sin(a) * std::cos(p) * exp - c.vy;

        float z_a = 0;
        float z_p = v * std::cos(p) * (1 - exp) / d;
        float z_t = g * (1 - exp) / d + v * std::sin(p) * exp - c.vz;

        Matrix<3, 3> jacobian{{{x_a, x_p, x_t}, {y_a, y_p, y_t}, {z_a, z_p, z_t}}};

        return jacobian;
    }

    // simple guess of time to hit based on initial conditions
    // assumes constant target velocity, derived from error() equations
    float time_to_hit(float p, const Conditions &c) {
        double distance = std::sqrt(c.x * c.x + c.y * c.y);
        double log = std::log(1 - distance * c.drag / c.speed / std::cos(p));
        return - log / c.drag;

    }
}
