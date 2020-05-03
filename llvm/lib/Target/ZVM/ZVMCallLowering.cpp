#include "ZVMCallLowering.h"

#define DEBUG_TYPE "zvm-call-lowering"

using namespace llvm;

ZVMCallLowering::ZVMCallLowering(const ZVMTargetLowering &TLI)
    : CallLowering(&TLI) {}

bool ZVMCallLowering::lowerReturn(MachineIRBuilder &MIRBuilder,
                                  const Value *Val, ArrayRef<Register> VRegs,
                                  Register SwiftErrorVReg) const {
  return true;
}

bool ZVMCallLowering::lowerFormalArguments(
    MachineIRBuilder &MIRBuilder, const Function &F,
    ArrayRef<ArrayRef<Register>> VRegs) const {
  return true;
}

bool ZVMCallLowering::lowerCall(MachineIRBuilder &MIRBuilder,
                                CallLoweringInfo &Info) const {
  return true;
}