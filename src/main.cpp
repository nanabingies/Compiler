#include "../include/lexer.hpp"
#include "../include/utils.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "%s: error: no input files\n", program_name.c_str());
        return EXIT_FAILURE;
    }

    if (file_exists(argv[1]) == false) {
        std::fprintf(stderr, "%s: no such file or directory: %s\n", program_name.c_str(), argv[1]);
        std::fprintf(stderr, "%s: error: no input files\n", program_name.c_str());
        return EXIT_FAILURE;
    }

    input_stream = std::make_unique<std::fstream>();
    input_stream->open(argv[1], std::fstream::in);



    input_stream->close();

    return 0;
}