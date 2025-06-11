#ifndef __LEXER_HPP_
#define __LEXER_HPP_

#include <iostream>

//===----------------------------------------------------------------------===//
// Lexer
//===----------------------------------------------------------------------===//

enum tokens : std::uint32_t {
    tok_eof = 0,

    // Binary operators
    tok_plus,   // +
    tok_minus,  // -
    tok_mul,    // *
    tok_div,    // /
    tok_cmplt,  // <
    tok_cmpgt,  // >
    tok_equals, // =

    // Language impls
    tok_identifier,
    tok_number,
    tok_keyword,
};

#endif
