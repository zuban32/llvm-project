#ifndef LLVM_LIB_TARGET_ZVM_ZVMFRAMELOWERING_H
#define LLVM_LIB_TARGET_ZVM_ZVMFRAMELOWERING_H

#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {
class ZVMSubtarget;

class ZVMFrameLowering : public TargetFrameLowering {
public:
  explicit ZVMFrameLowering(const ZVMSubtarget &sti)
      : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, Align(8), 0) {}

  void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;

  bool hasFP(const MachineFunction &MF) const override;
  void determineCalleeSaves(MachineFunction &MF, BitVector &SavedRegs,
                            RegScavenger *RS) const override;

  MachineBasicBlock::iterator
  eliminateCallFramePseudoInstr(MachineFunction &MF, MachineBasicBlock &MBB,
                                MachineBasicBlock::iterator MI) const override {
    return MBB.erase(MI);
  }
};
}
#endif