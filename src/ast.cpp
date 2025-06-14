#include "../include/ast.hpp"

namespace ast {
    std::unique_ptr<llvm::LLVMContext> llvmContext;
    std::unique_ptr<llvm::Module> llvmModule;
    std::unique_ptr<llvm::IRBuilder<>> llvmBuilder;
    std::map<std::string, llvm::Value*> NamedValues;

    llvm::Value* ast::IntNumberExprAST::codegen() {
        return llvm::ConstantInt::get(*llvmContext, llvm::APInt(8, value, true));
    }

    llvm::Value* ast::DoubleNumberExprAST::codegen() {
        return llvm::ConstantFP::get(*llvmContext, llvm::APFloat(value));
    }

    llvm::Value* ast::VariableExprAST::codegen() {
        llvm::Value* value = NamedValues[name];
        return value;
    }

    llvm::Value* ast::BinaryExprAST::codegen() {
        llvm::Value* Left = LHS->codegen();
        llvm::Value* Right = RHS->codegen();
        if (!Left || !Right)
            return nullptr;

        /*switch (op) {
            case '+':
                return llvmBuilder-
        }*/
       return nullptr;
    }

    llvm::Value* ast::IdentifierExprAST::codegen() {
        auto value = NamedValues[name];
        return value;
    }
};
