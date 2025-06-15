#ifndef __AST_HPP
#define __AST_HPP

#include "../include/lexer.hpp"
#include "llvm/IR/Value.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include <string>
#include <memory>
#include <utility>

namespace ast {

    extern std::unique_ptr<llvm::LLVMContext> llvmContext;
    extern std::unique_ptr<llvm::Module> llvmModule;
    extern std::unique_ptr<llvm::IRBuilder<>> llvmBuilder;
    extern std::map<std::string, llvm::Value*> NamedValues;
    extern std::string defaultFunctionName;

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
        int value;

    public:
        VariableExprAST(std::string name, int value);

        llvm::Value* codegen() override;
    };

    class VariableConstantExprAST : public VariableExprAST {
        int constantValue;

    public:
        VariableConstantExprAST(std::string name, const int value)
            : VariableExprAST(name, value), constantValue(value) {}
    };

    class BinaryExprAST : public ExprAST {
        tokens op;
        std::unique_ptr<ExprAST> LHS;
        std::unique_ptr<ExprAST> RHS;

    public:
        BinaryExprAST(const tokens op, std::unique_ptr<ExprAST> left, std::unique_ptr<ExprAST> right)
            : op(op), LHS(std::move(left)), RHS(std::move(right)) {}

        llvm::Value* codegen() override;
        llvm::Value* createAddFunc(llvm::Value*, llvm::Value*);
        llvm::Value* createSubFunc(llvm::Value*, llvm::Value*);
        llvm::Value* createMulFunc(llvm::Value*, llvm::Value*);
        llvm::Value* createDivFunc(llvm::Value*, llvm::Value*);
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
