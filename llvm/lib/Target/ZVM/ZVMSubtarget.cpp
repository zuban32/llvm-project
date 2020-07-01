#include "ZVM.h"
#include "ZVMTargetMachine.h"
#include "ZVMSubtarget.h"
#include "ZVMCallLowering.h"
#include "ZVMTargetLowering.h"

#define DEBUG_TYPE "zvm-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "ZVMGenSubtargetInfo.inc"

using namespace llvm;

ZVMSubtarget::ZVMSubtarget(const Triple &TT, const std::string &CPU,
                           const std::string &FS, const TargetMachine &TM)
    : ZVMGenSubtargetInfo(TT, CPU, FS), FrameLowering(*this),
      TLInfo(TM, *this) {
  CallLoweringInfo.reset(new ZVMCallLowering(*getTargetLowering()));
  Legalizer.reset(new ZVMLegalizerInfo(*this));

  auto *RBI = new ZVMRegisterBankInfo(*getRegisterInfo());

  InstSelector.reset(createZVMInstructionSelector(
      *static_cast<const ZVMTargetMachine *>(&TM), *this, *RBI));

  RegBankInfo.reset(RBI);
}

const CallLowering *ZVMSubtarget::getCallLowering() const {
  return CallLoweringInfo.get();
}

InstructionSelector *ZVMSubtarget::getInstructionSelector() const {
  return InstSelector.get();
}

const LegalizerInfo *ZVMSubtarget::getLegalizerInfo() const {
  return Legalizer.get();
}

const RegisterBankInfo *ZVMSubtarget::getRegBankInfo() const {
  return RegBankInfo.get();
}
