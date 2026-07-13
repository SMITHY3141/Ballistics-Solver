

#include "ballistics.hpp"

#include <iostream>

namespace blstc {
    std::ostream& operator<<(std::ostream& os, const blstc::Solution& s) {
        os << "SOLUTION" << '\n'
           << "azimuth: " << s.azimuth << '\n'
           << "elevation: "  << s.elevation  << '\n'
           << "time: " << s.time << '\n'
           << "error: " << s.error;

        return os; // so we can chain together std::cout << inputs << more_inputs
    }

    std::ostream& operator<<(std::ostream& os, const blstc::Conditions& c) {
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
        Solution s;


        return s;

    }


    Matrix<3, 3> jacobian(Vector<3> &state, const Conditions &c) {
       
        
    }

    Vector<3> error(Vector<3> &vars, const Conditions &c) {

    }
}
