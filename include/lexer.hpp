#ifndef __LEXER_HPP_
#define __LEXER_HPP_

#include <map>
#include <string.h>
#include <iostream>
#include <unordered_set>

//===----------------------------------------------------------------------===//
// Lexer
//===----------------------------------------------------------------------===//

enum tokens : std::int32_t {
    tok_invalid = -1,
    tok_eof = 0,
    tok_semicolon,

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
    tok_double,
    tok_keyword,

    tok_func_def,   // function definition
    tok_func_decl,  // function declaration
    tok_print       // printf
};

extern tokens curr_token;
extern int curr_token_index;

extern std::string identifier_str;
extern std::string keyword_str;

extern int token_number_int;
extern double token_number_double;

static std::unordered_set<std::string> keywords = { 
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
    "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "printf",
    "register", "return", "short", "signed", "sizeof", "static", "struct", "switch",
    "typedef", "union", "unsigned", "void", "volatile", "while",

    // Additional Keywords in C99
    "_Bool", "_Complex", "_Imaginary", "inline", "restrict",

    // Additional Keywords in C11
    "_Alignas", "_Alignof", "_Atomic", "_Generic", "_Noreturn", "_Static_assert",
    "_Thread_local"
};

const std::unordered_set<std::string> binaryOperators = {
    "+", "-", "*", "/", "%", "=", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "!", "&", "|", "^"
};

namespace lexer {
    tokens getNextToken();
    void putback();

    bool isKeyword(std::string&);
    bool isBinaryOperator(const std::string&);
}

#endif
