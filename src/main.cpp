#include "../include/lexer.hpp"
#include "../include/parser.hpp"
#include "../include/utils.hpp"

std::string curr_buffer;
int curr_line;
std::map<char, int> binopPrecedence;

void init_globals() {
    curr_buffer = "";
    curr_line = 0;
    identifier_str = "";
    keyword_str = "";

    binopPrecedence['+'] = 10;
    binopPrecedence['-'] = 10;
    binopPrecedence['*'] = 20;
    binopPrecedence['/'] = 20;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "%s: error: no input files\n", program_name.c_str());
        return EXIT_FAILURE;
    }

    const auto filename = std::string(argv[1]);

    if (file_exists(filename) == false) {
        std::fprintf(stderr, "%s: no such file or directory: %s\n", program_name.c_str(), argv[1]);
        std::fprintf(stderr, "%s: error: no input files\n", program_name.c_str());
        return EXIT_FAILURE;
    }

    if (ends_with(filename, ".c") == false) {
        std::fprintf(stderr, "%s: error: invalid source file extension\n", program_name.c_str());
        return EXIT_FAILURE;
    }

    init_globals();

    input_stream.open(filename, std::fstream::in);
    parser::Parser parser(filename);

    while (std::getline(input_stream, curr_buffer)) {
        curr_line++;
        if (!curr_buffer.empty()) {
            std::cout << "Parsing source line: " << curr_buffer << std::endl;
            // Process the current line buffer
            parser::parseBuffer(parser);
        }
    }

    input_stream.close();

    return 0;
}