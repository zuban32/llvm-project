#include "ZVMSubtarget.h"
#include "ZVMTargetLowering.h"

#define DEBUG_TYPE "zvm-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "ZVMGenSubtargetInfo.inc"

using namespace llvm;

ZVMSubtarget::ZVMSubtarget(const Triple &TT, const std::string &CPU,
                           const std::string &FS, const TargetMachine &TM)
    : ZVMGenSubtargetInfo(TT, CPU, FS), FrameLowering(*this), TLInfo(TM, *this) {}