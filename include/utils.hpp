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
#include <string_view>

// compile name
static std::string program_name = "compiler";

// input file stream
static std::fstream input_stream{};

// Current Line number
extern int curr_line;

// String to hold current line number
extern std::string curr_buffer;

inline void logError(const std::string& msg) {
    std::fprintf(stderr, "%s\n", msg.c_str());
    std::exit(EXIT_FAILURE);
}

// Check if input file exists on filesystem
inline bool file_exists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

inline bool ends_with(std::string_view str, std::string_view suffix) {
    return str.size() >= suffix.size() && str.compare(str.size()-suffix.size(), suffix.size(), suffix) == 0;
}

#endif
