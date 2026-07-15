
#include "parser.hpp"
#include "ballistics.hpp"
#include <iostream>
#include <fstream>

#define SAVE_DEFAULT "params.txt"
#define SAVE_COMMENT "//"


// parse the command line args for the save location (if none given use defualt)
char* find_save(int argc, char **argv) {
    if (!argc) {
        return SAVE_DEFAULT;
    }
    return argv[0];

}


// in-place, strips comments from a line
void strip_comment(std::string &string) {
    size_t pos = string.find(SAVE_COMMENT);
    if (pos == std::string::npos) {
        return; // pos returned -1, substring was not found
    }
    string.erase(pos); // removes everything past the pos. erase(0,5) removes in range

}


// splits a string in two at the first instance of a colon
// "key: value"
std::array<std::string, 2> split(const std::string& line, char letter) {
    std::array<std::string, 2> delimited; // "" in each string
    
    size_t pos = line.find(letter);
    if (pos == std::string::npos) {
        delimited[0] = line;
        return delimited;

    }
    std::string key = line.substr(0, pos); // everything up until pos
    std::string val = line.substr(pos + 1); // everything beyond pos
    
    delimited[0] = key;
    delimited[1] = val;

    return delimited;

}

// parses a save file into a blstc::Conditions struct.
blstc::Conditions parse_params(char *save_path) {
    blstc::Conditions conditions;
    
    // how to process the value of each key into the struct
    std::unordered_map<std::string, std::function<void(const std::string&)>> setters = {
        {"speed", [&](const std::string &v){conditions.speed = std::stof(v);}},
        {"drag", [&](const std::string &v){conditions.drag = std::stof(v);}},
        {"x", [&](const std::string &v){conditions.x = std::stof(v);}},
        {"y", [&](const std::string &v){conditions.y = std::stof(v);}},
        {"z", [&](const std::string &v){conditions.z = std::stof(v);}},
        {"vx", [&](const std::string &v){conditions.vx = std::stof(v);}},
        {"vy", [&](const std::string &v){conditions.vy = std::stof(v);}},
        {"vz", [&](const std::string &v){conditions.vz = std::stof(v);}},
        {"max", [&](const std::string &v){conditions.max = std::stoi(v);}},
        {"desired", [&](const std::string &v){conditions.desired = std::stof(v);}},
        {"gravity", [&](const std::string &v){conditions.gravity = std::stof(v);}}
    };

    std::ifstream file(save_path);
    if (!file) {
        std::cerr << "FAILED TO FIND INITIAL CONDITIONS FILE: " << save_path << std::endl;
        return conditions;
    }

    std::string line;
    while (std::getline(file, line)) {
        strip_comment(line);
        std::array<std::string, 2> key_value = split(line, ':');
        std::string key = key_value[0];
        std::string val = key_value[1];

        if (!key.length()) {
            continue; // if key empty (most likely line was empty)
        }

        auto it = setters.find(key); // iterator of key value pair
        if (it != setters.end()) {
            it->second(val);
        }
    }

    return conditions;

}

