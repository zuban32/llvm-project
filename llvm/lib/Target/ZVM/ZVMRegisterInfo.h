#ifndef LLVM_LIB_TARGET_ZVM_ZVMREGISTERINFO_H
#define LLVM_LIB_TARGET_ZVM_ZVMREGISTERINFO_H

#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "ZVMGenRegisterInfo.inc"

namespace llvm {

struct ZVMRegisterInfo : public ZVMGenRegisterInfo {

  ZVMRegisterInfo();

  const MCPhysReg *getCalleeSavedRegs(const MachineFunction *MF) const override {}

  BitVector getReservedRegs(const MachineFunction &MF) const override {}

  void eliminateFrameIndex(MachineBasicBlock::iterator MI, int SPAdj,
                           unsigned FIOperandNum,
                           RegScavenger *RS = nullptr) const override {}

  Register getFrameRegister(const MachineFunction &MF) const override {}
};
}

#endif
