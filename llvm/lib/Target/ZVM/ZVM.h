#ifndef LLVM_LIB_TARGET_ZVM_ZVM_H
#define LLVM_LIB_TARGET_ZVM_ZVM_H

#include "llvm/CodeGen/GlobalISel/InstructionSelector.h"

#include "ZVMSubtarget.h"
#include "ZVMTargetMachine.h"
#include "ZVMRegisterBankInfo.h"

namespace llvm {

InstructionSelector *createZVMInstructionSelector(const ZVMTargetMachine &,
                                                  ZVMSubtarget &,
                                                  ZVMRegisterBankInfo &);
} // namespace llvm

#endif