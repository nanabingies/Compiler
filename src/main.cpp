#include "../include/lexer.hpp"
#include "../include/parser.hpp"
#include "../include/utils.hpp"

std::string curr_buffer;
int curr_line;
std::map<tokens, int> binopPrecedence;

void init_globals() {
    curr_buffer = "";
    curr_line = 0;
    identifier_str = "";
    keyword_str = "";

    binopPrecedence[tok_plus] = 10;
    binopPrecedence[tok_minus] = 10;
    binopPrecedence[tok_mul] = 20;
    binopPrecedence[tok_div] = 20;

    ast::llvmContext = std::make_unique<llvm::LLVMContext>();
    ast::llvmModule = std::make_unique<llvm::Module>("compiler", *ast::llvmContext);
    ast::llvmBuilder = std::make_unique<llvm::IRBuilder<>>(*ast::llvmContext);
    ast::NamedValues = {};
    ast::defaultFunctionName = "__global_func";   // function for global variables
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "%s: error: no input files\n", program_name.c_str());
        return EXIT_FAILURE;
    }

    const auto filename = std::string(argv[1]);
    if (argv[2] != NULL) {
        const auto disassFileName = std::string(argv[2]);
        disass_stream.open(disassFileName, std::fstream::out | std::ios::trunc);
    }

    if (file_exists(filename) == false) {
        std::fprintf(stderr, "%s: no such file or directory: %s\n", program_name.c_str(), argv[1]);
        std::fprintf(stderr, "%s: error: no input files\n", program_name.c_str());
        return EXIT_FAILURE;
    }

    if (ends_with(filename, ".c") == false) {
        std::fprintf(stderr, "%s: error: invalid source file extension\n", program_name.c_str());
        return EXIT_FAILURE;
    }

    //if (file_exists(disassFileName) == true) {
    //    // Delete the file
    //    std::filesystem::remove(disassFileName);
    //}

    init_globals();

    input_stream.open(filename, std::fstream::in);
    
    parser::Parser parser;

    while (std::getline(input_stream, curr_buffer)) {
        curr_line++;
        if (!curr_buffer.empty()) {
            std::cout << "Parsing source line: " << curr_buffer << std::endl;
            // Process the current line buffer
            parser::parseBuffer(parser);
        }
    }

    input_stream.close();
    if (disass_stream.is_open())
        disass_stream.close();

    return 0;
}