#include "TargetInfo/ZVMTargetInfo.h"
#include "llvm/Support/TargetRegistry.h"

llvm::Target &llvm::getTheZVMTarget() {
  static Target TheZVMTarget;
  return TheZVMTarget;
}

extern "C" void LLVMInitializeZVMTargetInfo() {
  llvm::RegisterTarget<llvm::Triple::zvm, false>
    X(llvm::getTheZVMTarget(), "zvm", "ZVM", "zvm");
}
