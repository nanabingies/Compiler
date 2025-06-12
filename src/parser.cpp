#include "../include/lexer.hpp"
#include "../include/parser.hpp"
#include "../include/utils.hpp"

namespace parser {
    void parse_statements() {
        while (true) {
            auto tok = lexer::getNextToken();
            
            switch (tok) {
                case tok_invalid: {
                    std::fprintf(stderr, "Invalid token passed. Line %d\n", static_cast<int>(curr_line));
                    return;
                }

                case tok_eof:
                    return;

                case tok_plus:
                    break;

                case tok_minus:
                    break;

                case tok_mul:
                    break;

                case tok_div:
                    break;

                case tok_cmplt:
                    break;

                case tok_cmpgt:
                    break;

                case tok_equals:
                    break;

                case tok_open_b:
                    break;

                case tok_close_b:
                    break;

                case tok_open_c:
                    break;

                case tok_close_c:
                    break;

                case tok_identifier:
                    break;

                case tok_number:
                    break;

                case tok_keyword:
                    break;
    
                default: {
                    std::fprintf(stderr, "Invalid token passed. Line %d\n", static_cast<int>(curr_line));
                    return;
                }
            }
        }
    }
};
