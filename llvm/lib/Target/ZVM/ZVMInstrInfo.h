#ifndef LLVM_LIB_TARGET_ZVM_ZVMINSTRINFO_H
#define LLVM_LIB_TARGET_ZVM_ZVMINSTRINFO_H

#include "MCTargetDesc/ZVMMCTargetDesc.h"
#include "ZVMRegisterInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "ZVMGenInstrInfo.inc"

namespace llvm {

class ZVMInstrInfo : public ZVMGenInstrInfo {
  const ZVMRegisterInfo RI;

public:
  ZVMInstrInfo();

  const ZVMRegisterInfo &getRegisterInfo() const { return RI; }

};
}

#endif