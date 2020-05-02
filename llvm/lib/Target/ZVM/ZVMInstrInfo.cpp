#include "ZVMInstrInfo.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/IR/DebugLoc.h"
#include "llvm/Support/ErrorHandling.h"
#include <cassert>
#include <iterator>

#define GET_INSTRINFO_CTOR_DTOR
#include "ZVMGenInstrInfo.inc"

using namespace llvm;

ZVMInstrInfo::ZVMInstrInfo()
    : ZVMGenInstrInfo(ZVM::ADD, ZVM::ADD) {}