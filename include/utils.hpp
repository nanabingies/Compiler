#include <memory>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>

// compile name
static std::string program_name = "compiler";

// input file stream
static std::unique_ptr<std::fstream> input_stream{};

// Current Line number
static int curr_line = 1;

inline bool file_exists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}
