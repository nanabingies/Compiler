#ifndef __LEXER_HPP_
#define __LEXER_HPP_

#include <iostream>

//===----------------------------------------------------------------------===//
// Lexer
//===----------------------------------------------------------------------===//

enum tokens : std::int32_t {
    tok_invalid = -1,
    tok_eof = 0,

    // Binary operators
    tok_plus,   // +
    tok_minus,  // -
    tok_mul,    // *
    tok_div,    // /
    tok_cmplt,  // <
    tok_cmpgt,  // >
    tok_equals, // =

    // Unary operators
    tok_open_b,     // (
    tok_close_b,    // )
    tok_open_c,   // {
    tok_close_c,    // }

    // Language impls
    tok_identifier,
    tok_number,
    tok_keyword,
};

extern int curr_token;
extern int curr_token_index;

extern std::string identifier_str;
extern std::string keyword_str;

extern int token_number_int;
extern std::string token_number_str;

namespace lexer {
    tokens getNextToken();
}

#endif
