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

    return tok;
}

namespace lexer {
    tokens getNextToken() {
        int tok = get_next();
        while (isspace(tok)) {
            tok = get_next();
        }

        curr_token = tok;

        std::istringstream sub(curr_buffer);
        std::string curr_sub = "";

        while (sub >> curr_sub) {
            //std::cout << curr_sub << std::endl;
            for (unsigned i = 0; i < curr_sub.size(); i++, curr_token_index++) {
                if (isdigit(curr_sub[i])) {
                    // read ahead
                    if (!isdigit(curr_sub[i]))
                        return tok_number;
                    token_number_str += curr_sub[i];
                }
            }
        }

        return tok_invalid;
    }
};
