#ifndef __AST_HPP
#define __AST_HPP
#include <string>

namespace ast {
    class ExprAST {
    public:
        ~ExprAST() = delete;
    };

    class NumberExprAST : public ExprAST {
    private:
        double value;

    public:
        NumberExprAST(double& value) : value(value) {}
    }

    class VariableExprAST : public ExprAST {
    private:
        std::string name;

    public:
        VariableExprAST(const std::string& name) : name(name) {}
    }
};

#endif
