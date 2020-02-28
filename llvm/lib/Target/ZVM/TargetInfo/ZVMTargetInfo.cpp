#include "llvm/IR/Module.h"
#include "llvm/Support/TargetRegistry.h"

Target llvm::getTheZVMTarget();

extern "C" void LLVMInitializeZVMTargetInfo() {
  RegisterTarget<llvm::Triple::zvm, false>
    X(getTheZVMTarget(), "zvm", "ZVM");
}