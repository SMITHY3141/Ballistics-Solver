

#include "parser.hpp"
#include "ballistics.hpp"
#include <iostream>

int main(int argc, char **argv) {
    argc--;
    argv++;

    // Get initial conditions for solve
    char* save_path = find_save(argc, argv);
    blstc::Conditions conditions = parse_params(save_path);
    std::cout << '\n' << conditions << '\n' << '\n';


    // solve for firing solution
    blstc::Solution solution = blstc::solve(conditions);
    std::cout << '\n' << solution << '\n' << std::endl;

}



