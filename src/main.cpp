#include "../include/lexer.hpp"
#include "../include/utils.hpp"

std::string curr_buffer;
int curr_line;

void init_globals() {
    curr_buffer = "";
    curr_line = 1;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "%s: error: no input files\n", program_name.c_str());
        return EXIT_FAILURE;
    }

    std::string filename = std::string(argv[1]);

    if (file_exists(filename) == false) {
        std::fprintf(stderr, "%s: no such file or directory: %s\n", program_name.c_str(), argv[1]);
        std::fprintf(stderr, "%s: error: no input files\n", program_name.c_str());
        return EXIT_FAILURE;
    }

    init_globals();

    curr_buffer = "";
    input_stream.open(filename, std::fstream::in);

    while (std::getline(input_stream, curr_buffer)) {
        std::cout << curr_buffer << std::endl;
        // Process the current line buffer
        lexer::getNextToken();
    }

    input_stream.close();

    return 0;
}