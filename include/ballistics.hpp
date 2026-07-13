

#ifndef BALLISTICS_HPP
#define BALLISTICS_HPP

#include <iostream>

namespace blstc {
    struct Conditions {
        float speed = 0.f; ///< Projectile launch speed
        float drag = 0.f; ///< Projectile linear drag v[n+1] = v[n] - (1-drag) * v[n]

        float x = 0.f;
        float y = 0.f;
        float z = 0.f;

        float vx = 0.f;
        float vy = 0.f;
        float vz = 0.f;

        int max = 15; ///< max number of iterations in solver
        float desired = 0.f; ///< desired error (will stop solver early if reached)

    };

    struct Solution {
        float azimuth = 0.f;
        float elevation = 0.f; ///< required elevation angle
        float time = 0.f; ///< time to reach target

        float error = 0.f;
    };

    std::ostream& operator<<(std::ostream& os, const Conditions &c);
    std::ostream& operator<<(std::ostream& os, const Solution &s);

    Solution solve(const Conditions &c);
    Matrix<3, 3> jacobian(const Vector<3> &state, const Conditions &c);
    Vector<3> error(const Vector<3> &vars, const Conditions &c); // azimuth, elevation, time_to_reach



}

#endif // BALLISTICS_HPP
