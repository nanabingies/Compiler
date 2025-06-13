#ifndef __AST_HPP
#define __AST_HPP

#include "../include/lexer.hpp"
#include <string>
#include <memory>

namespace ast {
    class ExprAST {
    public:
        virtual ~ExprAST() = default;
    };

    class IntNumberExprAST : public ExprAST {
        int value;

    public:
        IntNumberExprAST(const double value) : value(value) {}
    };

    class DoubleNumberExprAST : public ExprAST {
        double value;

    public:
        DoubleNumberExprAST(const double value) : value(value) {}
    };

    template<typename T>
    class VariableExprAST : public ExprAST {
        std::string name;
        T value;

    public:
        VariableExprAST(const std::string& name, T value)
            : name(name), value(std::move(value)) {}
    };

    class BinaryExprAST : public ExprAST {
        tokens op;
        std::unique_ptr<ExprAST> LHS;
        std::unique_ptr<ExprAST> RHS;

    public:
        BinaryExprAST(const tokens op, std::unique_ptr<ExprAST> left, std::unique_ptr<ExprAST> right)
            : op(op), LHS(std::move(left)), RHS(std::move(right)) {}
    };

    class IdentifierExprAST : public ExprAST {
        std::string name;
        std::unique_ptr<ExprAST> value;

    public:
        IdentifierExprAST(const std::string& name, std::unique_ptr<ExprAST> value)
            : name(name), value(std::move(value)) {}
    };
};

#endif
