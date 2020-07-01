#include "ZVMRegisterBankInfo.h"
#include "ZVMInstrInfo.h"
#include "llvm/CodeGen/GlobalISel/RegisterBank.h"
#include "llvm/CodeGen/GlobalISel/RegisterBankInfo.h"
#include "llvm/ADT/SmallVector.h"

#define GET_TARGET_REGBANK_IMPL
#include "ZVMGenRegisterBank.inc"

// This file will be TableGen'ed at some point.
// #include "ZVMGenRegisterBankInfo.def"

using namespace llvm;

ZVMRegisterBankInfo::ZVMRegisterBankInfo(const TargetRegisterInfo &TRI)
    : ZVMGenRegisterBankInfo() {}

const RegisterBankInfo::InstructionMapping &
ZVMRegisterBankInfo::getInstrMapping(const MachineInstr &MI) const {
  const auto &Mapping = getInstrMappingImpl(MI);
  if (Mapping.isValid())
    return Mapping;

  const MachineFunction &MF = *MI.getParent()->getParent();
//   const TargetSubtargetInfo &STI = MF.getSubtarget();
//   const TargetRegisterInfo &TRI = *STI.getRegisterInfo();
  const MachineRegisterInfo &MRI = MF.getRegInfo();

  unsigned Cost = 1;
  unsigned NumOperands = MI.getNumOperands();
  SmallVector<const ValueMapping *, 8> OpdsMapping(NumOperands);
  for (unsigned Idx = 0; Idx < NumOperands; ++Idx) {
    if (MI.getOperand(Idx).isReg()) {
      LLT Ty = MRI.getType(MI.getOperand(Idx).getReg());
      auto Size = Ty.getSizeInBits();
      OpdsMapping[Idx] = &getValueMapping(0, Size, ZVM::GPRRegBank);
    }
  }
  return getInstructionMapping(DefaultMappingID, Cost,
                               getOperandsMapping(OpdsMapping), NumOperands);
}