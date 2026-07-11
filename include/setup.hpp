
#ifndef SETUP_HPP
#define SETUP_HPP

#include <iostream>

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
std::ostream& operator<<(std::ostream& os, const Conditions& c);

#endif // SETUP_HPP
