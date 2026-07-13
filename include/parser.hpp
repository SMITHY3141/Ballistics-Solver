
#ifndef PARSER_HPP
#define PARSER_HPP
#include "ballistics.hpp"

char* find_save(int argc, char **argv);
blstc::Conditions parse_params(char *save_path);

#endif // PARSER_HPP
