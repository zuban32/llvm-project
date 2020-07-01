#ifndef LLVM_LIB_TARGET_ZVM_BPFTARGETLOWERING_H
#define LLVM_LIB_TARGET_ZVM_BPFTARGETLOWERING_H

#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {

class ZVMSubtarget;

class ZVMTargetLowering : public TargetLowering {
public:
  explicit ZVMTargetLowering(const TargetMachine &TM, const ZVMSubtarget &STI): TargetLowering(TM) {}
};

}

#endif
