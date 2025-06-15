#include "../include/ast.hpp"

namespace ast {
    std::unique_ptr<llvm::LLVMContext> llvmContext;
    std::unique_ptr<llvm::Module> llvmModule;
    std::unique_ptr<llvm::IRBuilder<>> llvmBuilder;
    std::map<std::string, llvm::Value*> NamedValues;
    std::string defaultFunctionName;

    VariableExprAST::VariableExprAST(std::string c_name, int c_value) {
        name = std::move(c_name);
        value = std::move(c_value);
        //NamedValues[name] = llvm::ConstantInt(llvm::Type::getInt64Ty(*llvmContext), llvm::APInt(value));
        llvm::Function* function = llvmModule->getFunction(defaultFunctionName);
        if (function == nullptr) {
            // Create function
            llvm::FunctionType *funcType = llvm::FunctionType::get(llvm::Type::getVoidTy(*llvmContext), false);
            function = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, defaultFunctionName, *llvmModule);
        }

        if (function == nullptr) {
            std::cerr << "Failed to get function for variable definition" << std::endl;
            return;
        }

        llvm::BasicBlock *BB = llvm::BasicBlock::Create(*llvmContext, "entry", function);
        llvmBuilder->SetInsertPoint(BB);

        llvm::Type *intType = llvm::Type::getInt64Ty(*llvmContext);
        llvm::Value *xAlloca = llvmBuilder->CreateAlloca(intType, nullptr, name);
        llvm::Value *intConstant = llvm::ConstantInt::get(intType, value);

        llvmBuilder->CreateStore(intConstant, xAlloca);

        // Add return void
        llvmBuilder->CreateRetVoid();

        NamedValues[name] = intConstant;

        llvm::verifyFunction(*function);
    }

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
        llvm::Value* left = LHS->codegen();
        llvm::Value* right = RHS->codegen();
        if (!left || !right)
            return nullptr;

        switch (op) {
            case tok_plus:
                return createAddFunc(std::move(left), std::move(right));
            case tok_minus:
                return createSubFunc(std::move(left), std::move(right));
            case tok_mul:
                return llvmBuilder->CreateMul(left, right, "c_mul");
            case tok_div:
                return llvmBuilder->CreateSDiv(left, right, "c_div");
            default:
                return nullptr;
        }
    }

    llvm::Value* ast::IdentifierExprAST::codegen() {
        auto value = NamedValues[name];
        return value;
    }

    llvm::Value* BinaryExprAST::createAddFunc(llvm::Value* left, llvm::Value* right) {
        llvm::Function* function = llvmModule->getFunction(defaultFunctionName);
        if (function == nullptr) {
            // Create function
            llvm::FunctionType *funcType = llvm::FunctionType::get(llvm::Type::getVoidTy(*llvmContext), false);
            function = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, defaultFunctionName, *llvmModule);
        }

        if (function == nullptr) {
            std::cerr << "Failed to get function for variable definition" << std::endl;
            return nullptr;
        }

        llvm::BasicBlock *BB = llvm::BasicBlock::Create(*llvmContext, "entry", function);
        llvmBuilder->SetInsertPoint(BB);

        llvm::Type *intType = llvm::Type::getInt64Ty(*llvmContext);
        llvm::Value *xAlloca = llvmBuilder->CreateAlloca(intType, nullptr); // x
        
        auto result = llvmBuilder->CreateAdd(left, right, "c_add");

        llvmBuilder->CreateStore(result, xAlloca);

        // Add return void
        llvmBuilder->CreateRetVoid();

        if (llvm::verifyFunction(*function) == true)    return nullptr;

        return result;
    }

    llvm::Value* BinaryExprAST::createSubFunc(llvm::Value* left, llvm::Value* right) {
        llvm::Function* function = llvmModule->getFunction(defaultFunctionName);
        if (function == nullptr) {
            // Create function
            llvm::FunctionType *funcType = llvm::FunctionType::get(llvm::Type::getVoidTy(*llvmContext), false);
            function = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, defaultFunctionName, *llvmModule);
        }

        if (function == nullptr) {
            std::cerr << "Failed to get function for variable definition" << std::endl;
            return nullptr;
        }

        llvm::BasicBlock *BB = llvm::BasicBlock::Create(*llvmContext, "entry", function);
        llvmBuilder->SetInsertPoint(BB);

        llvm::Type *intType = llvm::Type::getInt64Ty(*llvmContext);
        llvm::Value *xAlloca = llvmBuilder->CreateAlloca(intType, nullptr); // x
        
        auto result = llvmBuilder->CreateSub(left, right, "c_sub");

        llvmBuilder->CreateStore(result, xAlloca);

        // Add return void
        llvmBuilder->CreateRetVoid();

        if (llvm::verifyFunction(*function) == true)    return nullptr;

        return result;
    }

};
