#ifndef __PARSER_HPP
#define __PARSER_HPP

#include "ast.hpp"
#include <map>

extern std::map<char, int> binopPrecedence;

namespace parser {
    void parseBuffer();

    std::unique_ptr<ast::ExprAST> parseStatement();

    void parseFunctionPrototype();

    void parseFunction();

    std::unique_ptr<ast::ExprAST> parseKeywordStatement();

    static std::unique_ptr<ast::ExprAST> ParseBinOpRHS(int, std::unique_ptr<ast::ExprAST>);

    std::unique_ptr<ast::ExprAST> parseNumberExpr();

    std::unique_ptr<ast::ExprAST> parsePrimary();

    int getOperatorPrecedence();
}

#endif
