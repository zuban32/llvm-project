#include "ZVMRegisterInfo.h"
#include "ZVMSubtarget.h"
#include "MCTargetDesc/ZVMMCTargetDesc.h"

#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/IR/DiagnosticInfo.h"
#include "llvm/Support/ErrorHandling.h"
 
#define GET_REGINFO_TARGET_DESC
#include "ZVMGenRegisterInfo.inc"

using namespace llvm;

ZVMRegisterInfo::ZVMRegisterInfo()
    : ZVMGenRegisterInfo(ZVM::R0) {}
