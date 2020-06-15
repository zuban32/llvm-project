#include "ZVMLegalizerInfo.h"
#include "ZVMSubtarget.h"
#include "llvm/CodeGen/GlobalISel/LegalizerHelper.h"
#include "llvm/CodeGen/GlobalISel/MachineIRBuilder.h"
#include "llvm/CodeGen/GlobalISel/Utils.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/TargetOpcodes.h"
#include "llvm/CodeGen/ValueTypes.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Type.h"

#define DEBUG_TYPE "ZVM-legalinfo"

using namespace llvm;
// using namespace LegalizeActions;
// using namespace LegalizeMutations;
// using namespace LegalityPredicates;

ZVMLegalizerInfo::ZVMLegalizerInfo(const ZVMSubtarget &ST) {
  using namespace TargetOpcode;
  const LLT p0 = LLT::pointer(0, 64);
  const LLT s16 = LLT::scalar(16);
  const LLT s32 = LLT::scalar(32);

  getActionDefinitionsBuilder({G_STORE, G_LOAD})
      .legalFor({{s32, p0}});

  getActionDefinitionsBuilder(G_FRAME_INDEX).legalFor({p0});
  getActionDefinitionsBuilder(G_CONSTANT).legalFor({s32});
  getActionDefinitionsBuilder(G_ADD).legalFor({s32});
  computeTables();
  // verify(*ST.getInstrInfo());
}

bool ZVMLegalizerInfo::legalizeIntrinsic(MachineInstr &MI,
                                         MachineIRBuilder &MIRBuilder,
                                         GISelChangeObserver &Observer) const {
  switch (MI.getIntrinsicID()) {
  case Intrinsic::memcpy:
  case Intrinsic::memset:
  case Intrinsic::memmove:
    if (createMemLibcall(MIRBuilder, *MIRBuilder.getMRI(), MI) ==
        LegalizerHelper::UnableToLegalize)
      return false;
    MI.eraseFromParent();
    return true;
  default:
    break;
  }
  return true;
}