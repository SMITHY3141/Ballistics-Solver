
#include "setup.hpp"
#include <iostream>

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


