

#include "ballistics.hpp"
#include "rootsolver.hpp"
#include <VECTORS/vectors.hpp>
#include <VECTORS/matrices.hpp>
#include <iostream>



namespace blstc {
    std::ostream& operator<<(std::ostream& os, const Solution& s) {
        os << "SOLUTION" << '\n'
           << "azimuth: " << s.azimuth << '\n'
           << "elevation: "  << s.elevation  << '\n'
           << "time: " << s.time << '\n'
           << "error: " << s.error;

        return os; // so we can chain together std::cout << inputs << more_inputs
    }

    std::ostream& operator<<(std::ostream& os, const Conditions& c) {
        os << "CONDITIONS" << '\n'
           << "speed: " << c.speed << '\n'
           << "drag: "  << c.drag  << '\n'
           << "target: (" << c.x << ", " << c.y << ", " << c.z << ")\n"
           << "velocity: (" << c.vx << ", " << c.vy << ", " << c.vz << ")\n"
           << "max: " << c.max << '\n'
           << "desired error: " << c.desired;

        return os; // so we can chain together std::cout << inputs
    }

    Solution solve(const Conditions &c) {
        Vector<3> guess{0.f, 0.f, 0.f}; // initial guess
        Vector<3> sol = solver::solve<3>(
                1,
                guess, 
                [c](const Vector<3> &vars) -> Vector<3> { return error(vars, c); }, 
                [c](const Vector<3> &state) -> Matrix<3, 3> { return jacobian(state, c); }
                );

        Solution s;
        s.azimuth = sol[0];
        s.elevation = sol[1];
        s.time = sol[2];

        return s;

    }


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
        float x_t = v * std::cos(a) * std::cos(p) * exp;

        float y_a = 0;
        float y_p = v * std::cos(p) * (1 - exp) / d;
        float y_t = g/d - exp * (g/d - v * std::sin(p));

        float z_a = v * std::cos(a) * std::cos(p) * (1 - exp) / d;
        float z_p = -v * std::sin(a) * std::sin(p) * (1- exp) / d;
        float z_t = v * std::sin(a) * std::cos(p) * exp;


        Matrix<3, 3> jacobian{{{x_a, x_p, x_t}, {y_a, y_p, y_t}, {z_a, z_p, z_t}}};

        return jacobian;
    }

    Vector<3> error(const Vector<3> &vars, const Conditions &c) {
        float g = c.gravity;
        float d = c.drag;
        float t = vars[2];
        float v = c.speed;

        float v_x = v * std::cos(vars[0]) * std::cos(vars[1]);
        float v_y = v * std::sin(vars[1]);
        float v_z = v * std::sin(vars[0]) * std::cos(vars[1]);

        float x = v_x * (1 - std::exp(-d * t)) / d;
        float y = (g * (t - 1/d) + v_y + std::exp(-d * t) * (g/d - v_y)) / d;
        float z = v_z * (1 - std::exp(-d * t)) / d;

        Vector<3> position{x, y, z};

        Vector<3> target{c.x, c.y, c.z};
        Vector<3> vel{c.vx, c.vy, c.vz};
        Vector<3> extrapolated = target + vel * vars[2];

        return position - extrapolated;

        
    }
}
