#ifndef __UTILS_HPP_
#define __UTILS_HPP_

#include <cctype>
#include <memory>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>

// compile name
static std::string program_name = "compiler";

// input file stream
static std::fstream input_stream{};

// Current Line number
extern int curr_line;

// String to hold current line number
extern std::string curr_buffer;

// Check if input file exists on filesystem
inline bool file_exists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

#endif
