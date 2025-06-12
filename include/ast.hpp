#ifndef __AST_HPP
#define __AST_HPP
#include <string>
#include <memory>

namespace ast {
    class ExprAST {
    public:
        virtual ~ExprAST() = default;
    };

    class NumberExprAST : public ExprAST {
        double value;

    public:
        NumberExprAST(const double value) : value(value) {}
    };

    class VariableExprAST : public ExprAST {
        std::string name;

    public:
        VariableExprAST(const std::string& name) : name(name) {}
    };

    class BinaryExprAST : public ExprAST {
        std::unique_ptr<ExprAST> LHS;
        std::unique_ptr<ExprAST> RHS;

    public:
        BinaryExprAST(std::unique_ptr<ExprAST> left, std::unique_ptr<ExprAST> right)
            : LHS(std::move(left)), RHS(std::move(right)) {}
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
