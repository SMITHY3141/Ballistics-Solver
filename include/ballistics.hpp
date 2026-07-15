

#ifndef BALLISTICS_HPP
#define BALLISTICS_HPP

#include <iostream>
#include <VECTORS/vectors.hpp>
#include <VECTORS/matrices.hpp>


namespace blstc {
    struct Conditions {
        float speed = 300.f; ///< Projectile launch speed
        float drag = 0.05f; ///< Projectile linear drag v[n+1] = v[n] - (1-drag) * v[n]

        // target position relative to projectile starting position
        float x = 1900.f; 
        float y = 500.f;
        float z = 900.f;

        // target velocity
        float vx = 0.f;
        float vy = 0.f;
        float vz = 0.f;

        int max = 15; ///< max number of iterations in solver
        float desired = 0.f; ///< desired error (will stop solver early if reached)

        float gravity = -9.8f; // m/s/s
    };

    struct Solution {
        float azimuth = 0.f; ///< required azimuth angle
        float elevation = 0.f; ///< required elevation angle
        float time = 0.f; ///< time to reach target

        float error = 0.f; /// final miss distance
    };

    std::ostream& operator<<(std::ostream& os, const Conditions &c);
    std::ostream& operator<<(std::ostream& os, const Solution &s);

    Solution solve(const Conditions &c);

    Vector<3> position(const Vector<3> &vars, const Conditions &c); 
    Vector<3> error(const Vector<3> &vars, const Conditions &c); 
    Matrix<3, 3> jacobian(const Vector<3> &state, const Conditions &c);
    float time_to_hit(float p, const Conditions &c);

}

#endif // BALLISTICS_HPP
