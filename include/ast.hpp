#ifndef __AST_HPP
#define __AST_HPP

#include "../include/lexer.hpp"
#include "llvm/IR/Value.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include <string>
#include <memory>
#include <utility>

namespace ast {

    extern std::unique_ptr<llvm::LLVMContext> llvmContext;
    extern std::unique_ptr<llvm::Module> llvmModule;
    extern std::unique_ptr<llvm::IRBuilder<>> llvmBuilder;

    class ExprAST {
    public:
        virtual ~ExprAST() = default;
        virtual llvm::Value* codegen() = 0;
    };

    class IntNumberExprAST : public ExprAST {
        int value;

    public:
        explicit IntNumberExprAST(const double value) : value(value) {}

        llvm::Value* codegen() override;
    };

    class DoubleNumberExprAST : public ExprAST {
        double value;

    public:
        explicit DoubleNumberExprAST(const double value) : value(value) {}

        llvm::Value* codegen() override;
    };

    class VariableExprAST : public ExprAST {
        std::string name;

    public:
        VariableExprAST(std::string  name) : name(std::move(name)) {}

        llvm::Value* codegen() override;
    };

    class BinaryExprAST : public ExprAST {
        tokens op;
        std::unique_ptr<ExprAST> LHS;
        std::unique_ptr<ExprAST> RHS;

    public:
        BinaryExprAST(const tokens op, std::unique_ptr<ExprAST> left, std::unique_ptr<ExprAST> right)
            : op(op), LHS(std::move(left)), RHS(std::move(right)) {}

        llvm::Value* codegen() override;
    };

    class IdentifierExprAST : public ExprAST {
        std::string name;
        std::unique_ptr<ExprAST> value;

    public:
        IdentifierExprAST(std::string  name, std::unique_ptr<ExprAST> value)
            : name(std::move(name)), value(std::move(value)) {}

        llvm::Value* codegen() override;
    };
};

#endif
