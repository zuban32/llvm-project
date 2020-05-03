#ifndef LIB_TARGET_ZVM_ZVMSUBTARGET_H_
#define LIB_TARGET_ZVM_ZVMSUBTARGET_H_

#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/CodeGen/GlobalISel/CallLowering.h"

#include "ZVMFrameLowering.h"
#include "ZVMTargetLowering.h"
#include "ZVMInstrInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "ZVMGenSubtargetInfo.inc"

namespace llvm {

class ZVMSubtarget : public ZVMGenSubtargetInfo {
  Triple TargetTriple;
  ZVMInstrInfo InstrInfo;
  ZVMFrameLowering FrameLowering;
  ZVMTargetLowering TLInfo;

  std::unique_ptr<CallLowering> CallLoweringInfo;
  // std::unique_ptr<InstructionSelector> InstSelector;
  // std::unique_ptr<LegalizerInfo> Legalizer;
  // std::unique_ptr<RegisterBankInfo> RegBankInfo;

public:
  ZVMSubtarget(const Triple &TT, const std::string &CPU,
                 const std::string &FS, const TargetMachine &TM);

  /// ParseSubtargetFeatures - Parses features string setting specified
  /// subtarget options.  Definition of function is auto generated by tblgen.
  void ParseSubtargetFeatures(StringRef CPU, StringRef FS);
  ZVMSubtarget &initializeSubtargetDependencies(StringRef CPU, StringRef FS);

  const ZVMFrameLowering *getFrameLowering() const override {
    return &FrameLowering;
  }
  const ZVMTargetLowering *getTargetLowering() const override {
    return &TLInfo;
  }
  const ZVMInstrInfo *getInstrInfo() const override { return &InstrInfo; }
  const TargetRegisterInfo *getRegisterInfo() const override {
    return &InstrInfo.getRegisterInfo();
  }

  const CallLowering *getCallLowering() const override;
  // InstructionSelector *getInstructionSelector() const override;
  // const LegalizerInfo *getLegalizerInfo() const override;
  // const RegisterBankInfo *getRegBankInfo() const override;
};


}

#endif