#ifndef LIB_TARGET_ZVM_ZVMTARGETMACHINE_H_
#define LIB_TARGET_ZVM_ZVMTARGETMACHINE_H_

#include "ZVMInstrInfo.h"
#include "ZVMSubtarget.h"
#include "ZVMTargetObjectFile.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class ZVMTargetMachine : public LLVMTargetMachine {
  ZVMSubtarget Subtarget;
  std::unique_ptr<TargetLoweringObjectFile> TLOF;

public:
  ZVMTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                   StringRef FS, const TargetOptions &Options,
                   Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                   CodeGenOpt::Level OL, bool JIT);

  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
  const ZVMSubtarget *getSubtargetImpl() const { return &Subtarget; };
  const ZVMSubtarget *getSubtargetImpl(const Function &F) const override {
    return &Subtarget;
  };
  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};
} // namespace llvm

#endif /* LIB_TARGET_ZVM_ZVMTARGETMACHINE_H_ */
