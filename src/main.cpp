

#include "parser.hpp"
#include "setup.hpp"
#include <iostream>

int main(int argc, char **argv) {
    argc--;
    argv++;

    char* save_path = find_save(argc, argv);
    Conditions conditions = parse_params(save_path);

    std::cout << conditions << '\n';
}

