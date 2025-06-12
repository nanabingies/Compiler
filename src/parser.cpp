#include "../include/lexer.hpp"
#include "../include/parser.hpp"
#include "../include/utils.hpp"

namespace parser {
    void parse_statements() {
        while (true) {
            int32_t tok = lexer::getNextToken();
            
            switch (tok) {
                case tok_invalid: {
                    std::fprintf(stderr, "Invalid token passed. Token '%c', Line %d\n", static_cast<char>(tok), static_cast<int>(curr_line));
                    return;
                }

                case tok_eof: {
                    std::fprintf(stderr, "EOF encountered. Token '%c', Line %d\n", static_cast<char>(tok), static_cast<int>(curr_line));
                    return;
                }

                case tok_plus: {
                    std::fprintf(stderr, "'+' encountered. Token '%c', Line %d\n", static_cast<char>(tok), static_cast<int>(curr_line));
                    break;
                }

                case tok_minus: {
                    std::fprintf(stderr, "'-' encountered. Token '%c', Line %d\n", static_cast<char>(tok), static_cast<int>(curr_line));
                    break;
                }

                case tok_mul: {
                    std::fprintf(stderr, "'*' encountered. Token '%c', Line %d\n", static_cast<char>(tok), static_cast<int>(curr_line));
                    break;
                }

                case tok_div: {
                    std::fprintf(stderr, "'/' encountered. Token '%c', Line %d\n", static_cast<char>(tok), static_cast<int>(curr_line));
                    break;
                }

                case tok_cmplt: {
                    std::fprintf(stderr, "'<' encountered. Token '%c', Line %d\n", static_cast<char>(tok), static_cast<int>(curr_line));
                    break;
                }

                case tok_cmpgt: {
                    std::fprintf(stderr, "'>' encountered. Token '%c', Line %d\n", static_cast<char>(tok), static_cast<int>(curr_line));
                    break;
                }

                case tok_equals: {
                    std::fprintf(stderr, "'=' encountered. Token '%c', Line %d\n", static_cast<char>(tok), static_cast<int>(curr_line));
                    break;
                }

                case tok_open_b: {
                    std::fprintf(stderr, "'(' encountered. Token '%c', Line %d\n", static_cast<char>(tok), static_cast<int>(curr_line));
                    break;
                }

                case tok_close_b: {
                    std::fprintf(stderr, "')' encountered. Token '%c', Line %d\n", static_cast<char>(tok), static_cast<int>(curr_line));
                    break;
                }

                case tok_open_c: {
                    std::fprintf(stderr, "'{' encountered. Token '%c', Line %d\n", static_cast<char>(tok), static_cast<int>(curr_line));
                    break;
                }

                case tok_close_c: {
                    std::fprintf(stderr, "'}' encountered. Token '%c', Line %d\n", static_cast<char>(tok), static_cast<int>(curr_line));
                    break;
                }

                case tok_identifier: {
                    std::fprintf(stderr, "Identifier '%s', Token '%c', Line %d\n", identifier_str.c_str(), static_cast<char>(tok), static_cast<int>(curr_line));
                    break;
                }

                case tok_number: {
                    std::fprintf(stderr, "Number '%d', Token '%c', Line %d\n", static_cast<int>(token_number_int), static_cast<char>(tok), static_cast<int>(curr_line));
                    break;
                }

                case tok_keyword: {
                    std::fprintf(stderr, "Keyword '%s', Token '%c', Line %d\n", keyword_str.c_str(), static_cast<char>(tok), static_cast<int>(curr_line));
                    break;
                }
    
                default: {
                    std::fprintf(stderr, "Invalid token passed. Line %d\n", static_cast<int>(curr_line));
                    return;
                }
            }
        }
    }
};
