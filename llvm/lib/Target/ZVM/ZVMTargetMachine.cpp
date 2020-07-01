#include "ZVMTargetMachine.h"
#include "ZVMSubtarget.h"
// #include "MCTargetDesc/ZVMMCTargetDesc.h"
#include "TargetInfo/ZVMTargetInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/InitializePasses.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/CodeGen/GlobalISel/IRTranslator.h"
#include "llvm/CodeGen/GlobalISel/InstructionSelect.h"
#include "llvm/CodeGen/GlobalISel/Legalizer.h"
#include "llvm/CodeGen/GlobalISel/RegBankSelect.h"


using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeZVMTarget() {
  // Register the target.
  RegisterTargetMachine<ZVMTargetMachine> X(getTheZVMTarget());

  auto PR = PassRegistry::getPassRegistry();
  initializeGlobalISel(*PR); 
}

static std::string computeDataLayout()
{
	return "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128";
}

static Reloc::Model getZvmRelocModel(Optional<Reloc::Model> RM) {
  if (!RM) {
    return Reloc::Static;
  }
  return *RM;
}

static CodeModel::Model getZvmCodeModel(Optional<CodeModel::Model> CM) {
  if (!CM) {
    return CodeModel::Small;
  }
  return *CM;
}

ZVMTargetMachine::ZVMTargetMachine(const Target &T, const Triple &TT,
                                   StringRef CPU, StringRef FS,
                                   const TargetOptions &Options,
                                   Optional<Reloc::Model> RM,
                                   Optional<CodeModel::Model> CM,
                                   CodeGenOpt::Level OL, bool JIT)
    : LLVMTargetMachine(T, computeDataLayout(), TT, CPU, FS, Options,
                        getZvmRelocModel(RM), getZvmCodeModel(CM), OL),
      Subtarget(TT, std::string(CPU), std::string(FS), *this),
      TLOF(std::make_unique<ZVMMachOTargetObjectFile>()) {
  initAsmInfo();
  setGlobalISel(true);
}

namespace {
class ZVMPassConfig : public TargetPassConfig {
public:
  ZVMPassConfig(ZVMTargetMachine *TM, PassManagerBase &PM)
    : TargetPassConfig(*TM, PM) {}

  ZVMTargetMachine &getZVMTargetMachine() const {
    return getTM<ZVMTargetMachine>();
  }

  bool addIRTranslator() {
    addPass(new IRTranslator());
    return false;
  }

  bool addLegalizeMachineIR() {
    addPass(new Legalizer());
    return false;
  }

  bool addRegBankSelect() {
    addPass(new RegBankSelect());
    return false;
  }

  bool addGlobalInstructionSelect() {
    addPass(new InstructionSelect());
    return false;
  }

};
}

TargetPassConfig *ZVMTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new ZVMPassConfig(this, PM);
}