
#include "parser.hpp"
#include "ballistics.hpp"
#include <iostream>
#include <fstream>

#define SAVE_DEFAULT "params.txt"
#define SAVE_COMMENT "//"


// TODO parse the command args for the save location (if none given use defualt)
char* find_save(int argc, char **argv) {
    if (!argc) {
        return SAVE_DEFAULT;
    }
    return argv[0];

}


// in-place, only splits on the first instance of //
void strip_comment(std::string &string) {
    size_t pos = string.find(SAVE_COMMENT);
    if (pos == std::string::npos) {
        return; // pos returned -1, substring was not found
    }
    string.erase(pos); // removes everything past the pos. erase(0,5) removes in range

}


// std::vector is dynamic .push_back(), .pop_back(), .resize()
std::array<std::string, 2> strip_past_colon(const std::string& line) {
    std::array<std::string, 2> delimited; // "" in each string
    
    size_t pos = line.find(":");
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


blstc::Conditions parse_params(char *save_path) {
    blstc::Conditions conditions;
    
    // signature of void (*)(const std::string&)
    // [] is a capture clause, it reaches into the surrounding scope to pull variables in
    // [&] is used in the lambda, it reaches into the surrounding scope so we can use them by reference
    // [=] to capture by value, so capturing the entire scope by value would be expensive
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

    //ifstream as in input fstream, there's also ofstream
    std::ifstream file(save_path);

    std::string line;
    while (std::getline(file, line)) {
        strip_comment(line);
        std::array<std::string, 2> key_value = strip_past_colon(line);
        std::string key = key_value[0];
        std::string val = key_value[1];

        if (!key.length()) {
            continue; // if key empty (most likely line was empty)
        }

        // .find() returns an iterator
        // say int nums[] = {1,2}; int *p = nums;
        // iterator in cpp is it's way of abstracting this p ptr
        // nums.begin() is an iterator, deref to get 1, it++
        // in .find() case, the iterator is of the entire map;
        auto it = setters.find(key); // iterator of key value pair
        if (it != setters.end()) {
            it->second(val);
        }
    }

    return conditions;

}

