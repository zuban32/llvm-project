#ifndef LLVM_LIB_TARGET_ZVM_ZVMCALLLOWERING_H
#define LLVM_LIB_TARGET_ZVM_ZVMCALLLOWERING_H

#include "llvm/ADT/ArrayRef.h"
#include "llvm/CodeGen/GlobalISel/CallLowering.h"
#include "llvm/IR/CallingConv.h"

#include "ZVMTargetLowering.h"

#include <cstdint>
#include <functional>

namespace llvm {

class ZVMCallLowering: public CallLowering {
public:
  ZVMCallLowering(const ZVMTargetLowering &TLI);

  bool lowerReturn(MachineIRBuilder &MIRBuilder, const Value *Val,
                   ArrayRef<Register> VRegs,
                   Register SwiftErrorVReg) const override;

  bool lowerFormalArguments(MachineIRBuilder &MIRBuilder, const Function &F,
                            ArrayRef<ArrayRef<Register>> VRegs) const override;

  bool lowerCall(MachineIRBuilder &MIRBuilder,
                 CallLoweringInfo &Info) const override;
};

}

#endif