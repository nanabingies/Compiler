#include "../include/lexer.hpp"
#include "../include/parser.hpp"

#include "../include/ast.hpp"
#include "../include/utils.hpp"

namespace parser {
    void parseBuffer() {
        curr_token_index = 0;
        while (true) {
            auto tok = lexer::getNextToken();

            switch (tok) {
                case tok_identifier:
                    std::fprintf(stdout, "Handling tok_identifier\n");
                    parseStatement();
                    break;
                case tok_keyword:
                    std::fprintf(stdout, "Handling tok_keyword\n");
                    parseKeywordStatement();
                    break;
                case tok_print:
                    std::fprintf(stderr, "Print Not yet implemented\n");
                    break;
                default:
                    std::fprintf(stderr, "Unknown token %c\n", static_cast<char>(tok));
                    std::exit(EXIT_FAILURE);
            }
        }
    }

    void parseTokenStatement(const int tok) {
        curr_token_index = 0;
        while (true) {
            //int32_t tok = lexer::getNextToken();
            
            switch (tok) {
                case tok_invalid: {
                    std::fprintf(stderr, "Invalid token passed. Line %d\n", curr_line);
                    std::exit(EXIT_FAILURE);
                }

                case tok_eof: {
                    std::fprintf(stderr, "EOF encountered. Line %d\n", curr_line);
                    curr_buffer = "";
                    return;
                }

                case tok_semicolon: {
                    std::fprintf(stderr, "';' encountered. Line %d\n", curr_line);
                    break;
                }

                case tok_plus: {
                    std::fprintf(stderr, "'+' encountered. Line %d\n", curr_line);
                    break;
                }

                case tok_minus: {
                    std::fprintf(stderr, "'-' encountered. Line %d\n", curr_line);
                    break;
                }

                case tok_mul: {
                    std::fprintf(stderr, "'*' encountered. Line %d\n", curr_line);
                    break;
                }

                case tok_div: {
                    std::fprintf(stderr, "'/' encountered. Line %d\n", curr_line);
                    break;
                }

                case tok_cmplt: {
                    std::fprintf(stderr, "'<' encountered. Line %d\n", curr_line);
                    break;
                }

                case tok_cmpgt: {
                    std::fprintf(stderr, "'>' encountered. Line %d\n", curr_line);
                    break;
                }

                case tok_equals: {
                    std::fprintf(stderr, "'=' encountered. Line %d\n", curr_line);
                    break;
                }

                case tok_open_b: {
                    std::fprintf(stderr, "'(' encountered. Line %d\n", curr_line);
                    break;
                }

                case tok_close_b: {
                    std::fprintf(stderr, "')' encountered. Line %d\n", curr_line);
                    break;
                }

                case tok_open_c: {
                    std::fprintf(stderr, "'{' encountered. Line %d\n", curr_line);
                    break;
                }

                case tok_close_c: {
                    std::fprintf(stderr, "'}' encountered. Line %d\n", curr_line);
                    break;
                }

                case tok_identifier: {
                    std::fprintf(stderr, "Identifier '%s', Line %d\n", identifier_str.c_str(), curr_line);
                    break;
                }

                case tok_number: {
                    std::fprintf(stderr, "Number '%d', Line %d\n", token_number_int, curr_line);
                    break;
                }

                case tok_keyword: {
                    std::fprintf(stderr, "Keyword '%s', Line %d\n", keyword_str.c_str(), curr_line);
                    break;
                }
    
                default: {
                    std::fprintf(stderr, "Invalid token passed. Line %d\n", curr_line);
                    return;
                }
            }
        }
    }

    void parseKeywordStatement() {
        if (keyword_str.empty())    return;

        if (keyword_str == "int") {
            // read identifier token
            lexer::getNextToken();
            auto identStr = identifier_str;

            if (lexer::getNextToken() != tok_equals) {
                std::fprintf(stderr, "error: Expected '=' at line %d\n", curr_line);
                std::exit(EXIT_FAILURE);
            }

            // is it a number, string or identifier
            auto nextToken = lexer::getNextToken();
            if (nextToken == tok_number) {
                auto variableAst = std::make_unique<ast::VariableExprAST<int>>(identStr, token_number_int);
            } else if (nextToken == tok_double) {
                auto variableAst = std::make_unique<ast::VariableExprAST<double>>(identStr, token_number_int);
            } else if (nextToken == tok_identifier) {
                auto variableAst = std::make_unique<ast::VariableExprAST<std::string>>(identStr, identifier_str);
            }
        }

        else if (keyword_str == "char") {
            // read next token
            //auto nextToken = lexer::getNextToken();

            if (lexer::getNextToken() != '=') {
                std::fprintf(stderr, "error: Expected '=' at line %d\n", curr_line);
                std::exit(EXIT_FAILURE);
            }
        }
    }

    void parseStatement() {
        if (identifier_str.empty()) return;

        if (identifier_str == "int")
            return parseKeywordStatement();
    }

    void parseFunctionPrototype() {

    }

    void parseFunction() {

    }


};
