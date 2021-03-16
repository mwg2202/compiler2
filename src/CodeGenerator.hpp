#define LLVM_DISABLE_ABI_BREAKING_CHECKS_ENFORCING 1
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"


class CodeGenerator {
    llvm::Module* makeLLVMModule();

    public:
    CodeGenerator(); 
};
