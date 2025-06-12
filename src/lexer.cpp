#include "../include/lexer.hpp"
#include "../include/utils.hpp"

int curr_token = 0;
int curr_token_index = 0;

std::string identifier_str;
std::string keyword_str;
int token_number_int;
//std::string token_number_str;

int getNext() {
    const int tok = static_cast<unsigned char>(curr_buffer[curr_token_index++]);

    if (tok == '\n') {
        curr_line++;
        curr_token_index = 0;
    }
    curr_token = tok;
    return tok;
}

bool isKeyword(std::string& word) {
    return keywords.find(word) != keywords.end();
}

bool isBinaryOperator(const std::string& token) {
    return binaryOperators.find(token) != binaryOperators.end();
}

namespace lexer {
    tokens getNextToken() {
        int tok = getNext();
        while (isspace(tok)) {
            tok = getNext();
        }

        // Identifiers
        if (isalpha(tok)) {
            identifier_str = static_cast<char>(tok);

            while (isalnum(tok = getNext())) {
                identifier_str += static_cast<char>(tok);
            }
            curr_token_index -= 1;

            // Keywords
            if (isKeyword(identifier_str)) {
                return tok_keyword;
            }

            return tok_identifier;
        }

        // Number literals
        if (isdigit(tok) || static_cast<char>(tok) == '.') {
            std::string number_str;
            token_number_int = 0;
            do {
                number_str += tok;
                tok = getNext();
            } while (isdigit(tok) || static_cast<char>(tok) == '.');

            // Putback the previous read token
            curr_token_index -= 1;

            token_number_int = std::stoi(number_str); //strtod(number_str.c_str(), nullptr);
            return tok_number;
        }

        // EOF characters
        if (static_cast<char>(tok) == EOF || static_cast<char>(tok) == '\0') {
            return tok_eof;
        }

        // Binary operators
        if (isBinaryOperator(std::to_string(tok))) {
            std::cout << "Token '" << static_cast<char>(tok) << "' is an operator.\n";
        }

        if (static_cast<char>(tok) == '+') {
            return tok_plus;
        } else if (static_cast<char>(tok) == '-') {
            return tok_minus;
        } else if (static_cast<char>(tok) == '*') {
            return tok_mul;
        } else if (static_cast<char>(tok) == '/') {
            return tok_div;
        } else if (static_cast<char>(tok) == ';') {
            return tok_semicolon;
        }

        return tok_invalid;
    }
};
