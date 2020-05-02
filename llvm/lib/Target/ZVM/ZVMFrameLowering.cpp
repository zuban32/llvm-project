#include "ZVMFrameLowering.h"
#include "ZVMInstrInfo.h"
#include "ZVMSubtarget.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"

using namespace llvm;

bool ZVMFrameLowering::hasFP(const MachineFunction &MF) const { return true; }

void ZVMFrameLowering::emitPrologue(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const {}

void ZVMFrameLowering::emitEpilogue(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const {}

void ZVMFrameLowering::determineCalleeSaves(MachineFunction &MF,
                                            BitVector &SavedRegs,
                                            RegScavenger *RS) const {
  TargetFrameLowering::determineCalleeSaves(MF, SavedRegs, RS);
//   SavedRegs.reset(ZVM::R6);
//   SavedRegs.reset(ZVM::R7);
//   SavedRegs.reset(ZVM::R8);
//   SavedRegs.reset(ZVM::R9);
}