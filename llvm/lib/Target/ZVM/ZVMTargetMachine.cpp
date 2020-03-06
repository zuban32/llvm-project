#include "ZVMTargetMachine.h"
#include "TargetInfo/ZVMTargetInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeZVMTarget() {
  // Register the target.
  RegisterTargetMachine<ZVMTargetMachine> X(getTheZVMTarget());
}

static std::string computeDataLayout()
{
	return "";
}

ZVMTargetMachine::ZVMTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
        StringRef FS, const TargetOptions &Options,
        Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
        CodeGenOpt::Level OL, bool JIT):
        		LLVMTargetMachine(T, computeDataLayout(), TT, CPU, FS, Options, *RM, *CM, OL) {}
