#ifndef LLVM_LIB_TARGET_ZVM_ZVMMACHINELEGALIZER_H
#define LLVM_LIB_TARGET_ZVM_ZVMMACHINELEGALIZER_H

#include "llvm/CodeGen/GlobalISel/GISelChangeObserver.h"
#include "llvm/CodeGen/GlobalISel/LegalizerInfo.h"

namespace llvm {

class LLVMContext;
class ZVMSubtarget;

/// This class provides the information for the target register banks.
class ZVMLegalizerInfo : public LegalizerInfo {
public:
  ZVMLegalizerInfo(const ZVMSubtarget &ST);

  bool legalizeIntrinsic(MachineInstr &MI, MachineIRBuilder &MIRBuilder,
                         GISelChangeObserver &Observer) const override;
};
} // End llvm namespace.
#endif