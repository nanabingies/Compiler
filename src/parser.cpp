#include "../include/lexer.hpp"
#include "../include/parser.hpp"

#include "../include/ast.hpp"
#include "../include/utils.hpp"

namespace parser {
    tokens prevToken = tok_invalid;

    int getOperatorPrecedence() {
        auto tok = lexer::getNextToken();
        prevToken = tok;

        if (tok == tok_plus) {
            return binopPrecedence['+'];
        } else if (tok == tok_minus) {
            return binopPrecedence['-'];
        } else if (tok == tok_mul) {
            return binopPrecedence['*'];
        } else if (tok == tok_div) {
            return binopPrecedence['/'];
        }

        return tok_invalid;
    }

    void parseBuffer(Parser parser) {
        curr_token_index = 0;
        while (true) {
            auto tok = lexer::getNextToken();

            switch (tok) {
                case tok_eof:
                    return;
                case tok_identifier:
                    std::fprintf(stdout, "Handling tok_identifier\n");
                    parser.parseStatement();
                    break;
                case tok_keyword:
                    std::fprintf(stdout, "Handling tok_keyword\n");
                    parser.parseKeywordStatement();
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

    std::unique_ptr<ast::ExprAST> Parser::parseKeywordStatement() {
        if (keyword_str.empty())    return nullptr;

        if (keyword_str == "int") {
            // read identifier token
            lexer::getNextToken();
            auto identStr = identifier_str;

            if (lexer::getNextToken() != tok_equals) {
                std::fprintf(stderr, "error: Expected '=' at line %d\n", curr_line);
                std::exit(EXIT_FAILURE);
            }

            // is it a number, string or identifier
            auto tempToken = lexer::getNextToken();
            auto nextToken = lexer::getNextToken();

            if (tempToken == tok_invalid || tempToken == tok_semicolon) {
                std::fprintf(stderr, "error: Expected literal at line %d\n", curr_line);
                std::exit(EXIT_FAILURE);
            }

            if (tempToken == tok_number && nextToken == tok_number) {
                std::fprintf(stderr, "error: syntax error on line %d\n", curr_line);
                std::exit(EXIT_FAILURE);
            }

            // end of statement.
            // build a VariableExprAST
            if (nextToken == tok_semicolon) {
                if (tempToken == tok_number) {
                    return std::make_unique<ast::VariableExprAST<int>>(identStr, token_number_int);
                } else if (tempToken == tok_double) {
                    return std::make_unique<ast::VariableExprAST<double>>(identStr, token_number_int);
                } else if (tempToken == tok_identifier) {
                    return std::make_unique<ast::VariableExprAST<std::string>>(identStr, identifier_str);
                }
            }

            if (nextToken == tok_plus || nextToken == tok_minus || nextToken == tok_mul || nextToken == tok_div) {
                lexer::putback();  // return operator
                lexer::putback();  // return previous number

                auto LHS = parsePrimary();
                if (!LHS)   return nullptr;

                return ParseBinOpRHS(0, std::move(LHS));
            }

            return nullptr;
        }

        else if (keyword_str == "char") {
            // read next token
            //auto nextToken = lexer::getNextToken();

            if (lexer::getNextToken() != '=') {
                std::fprintf(stderr, "error: Expected '=' at line %d\n", curr_line);
                std::exit(EXIT_FAILURE);
            }

            return nullptr;
        }

        return nullptr;
    }

    std::unique_ptr<ast::ExprAST> Parser::parseStatement() {
        if (identifier_str.empty()) return nullptr;

        if (identifier_str == "int")
            return parseKeywordStatement();

        return nullptr;
    }

    std::unique_ptr<ast::ExprAST> Parser::ParseBinOpRHS(int ExprPrec, std::unique_ptr<ast::ExprAST> LHS) {
        // If this is a binop, find its precedence.
        while (true) {
            int TokPrec = getOperatorPrecedence();

            // If this is a binop that binds at least as tightly as the current binop,
            // consume it, otherwise we are done.
            if (TokPrec < ExprPrec)
                return LHS;

            // Okay, we know this is a binop.
            tokens BinOp = prevToken;

            // Parse the primary expression after the binary operator.
            auto RHS = parsePrimary();
            if (!RHS)
                return nullptr;

            // If BinOp binds less tightly with RHS than the operator after RHS, let
            // the pending operator take RHS as its LHS.
            int NextPrec = getOperatorPrecedence();
            if (TokPrec < NextPrec) {
                RHS = ParseBinOpRHS(TokPrec + 1, std::move(RHS));
                if (!RHS)
                    return nullptr;
            }

            // Merge LHS/RHS.
            LHS = std::make_unique<ast::BinaryExprAST>(BinOp, std::move(LHS), std::move(RHS));
        }
    }

    std::unique_ptr<ast::ExprAST> Parser::parseFunctionPrototype() {
        return nullptr;
    }

    std::unique_ptr<ast::ExprAST>  Parser::parseFunction() {
        return nullptr;
    }

    std::unique_ptr<ast::ExprAST> Parser::parseNumberExpr() {
        auto result = std::make_unique<ast::IntNumberExprAST>(token_number_int);
        return std::move(result);
    }

    std::unique_ptr<ast::ExprAST> Parser::parseDoubleExpr() {
        auto result = std::make_unique<ast::DoubleNumberExprAST>(token_number_double);
        return std::move(result);
    }

    std::unique_ptr<ast::ExprAST> Parser::parsePrimary() {
        auto tok = lexer::getNextToken();

        if (tok == tok_number || tok == tok_double) {
            return parseNumberExpr();
        } else if (tok == tok_identifier) {
            // first check if variable is already defined.
            // then build ast for that.
        }

        return nullptr;
    }

};
