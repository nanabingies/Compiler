#ifndef __PARSER_HPP
#define __PARSER_HPP

#include "ast.hpp"
#include "codegen.hpp"
#include <map>
#include <utility>

extern std::map<tokens, int> binopPrecedence;

namespace parser {
    int getOperatorPrecedence();

    void parseTokenStatement(int);

    class Parser {

    public:
        explicit Parser() = default;

        std::unique_ptr<ast::ExprAST> parseStatement();
        std::unique_ptr<ast::ExprAST> parseKeywordStatement();
        std::unique_ptr<ast::ExprAST> parseFunction();
        std::unique_ptr<ast::ExprAST> parseFunctionPrototype();

        std::unique_ptr<ast::ExprAST> ParseBinOpRHS(int, std::unique_ptr<ast::ExprAST>);
        std::unique_ptr<ast::ExprAST> parseNumberExpr();
        std::unique_ptr<ast::ExprAST> parseDoubleExpr();
        //std::unique_ptr<ast::ExprAST> parseIdentifierExpr();

        std::unique_ptr<ast::ExprAST> parsePrimary();
        std::unique_ptr<ast::ExprAST> parsePrimaryVariable();
        std::unique_ptr<ast::ExprAST> parseBinOpExpr();
    };

    void parseBuffer(Parser);
};

#endif
