#include "../include/lexer.hpp"
#include "../include/utils.hpp"

int curr_token = 0;
int curr_token_index = 0;

std::string identifier_str;
std::string keyword_str;
int token_number_int;
std::string token_number_str;

int get_next() {
    int tok = curr_buffer[curr_token_index++];

    if (tok == '\n') {
        curr_line++;
        curr_token_index = 0;
    }
    curr_token = tok;

    return tok;
}

bool is_keyword(std::string& word) {
    for (auto key : keywords) {
        if (key == word)
            return true;
    }

    return false;
}

namespace lexer {
    tokens getNextToken() {
        int tok = get_next();
        while (isspace(tok)) {
            tok = get_next();
        }

        if (isalpha(tok)) {
            identifier_str = static_cast<char>(tok);

            while (isalnum(tok = get_next())) {
                identifier_str += static_cast<char>(tok);
            }

            if (is_keyword(identifier_str)) {
                // Keywords
            }
        }

        if (isdigit(tok) || static_cast<char>(tok) == '.') {
            do {
                token_number_str += tok;
                tok = get_next();
            } while (isdigit(tok) || static_cast<char>(tok) == '.');

            token_number_int = strtod(token_number_str.c_str(), nullptr);
            return tok_number;
        }

        if (static_cast<char>(tok) == EOF) {
            return tok_eof;
        }

        return tok_invalid;
    }
};
