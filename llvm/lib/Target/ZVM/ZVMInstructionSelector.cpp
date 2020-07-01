#include "ZVM.h"
#include "ZVMRegisterInfo.h"

#include "llvm/CodeGen/GlobalISel/InstructionSelectorImpl.h"

#define DEBUG_TYPE "zvm-isel"

using namespace llvm;

namespace {

#define GET_GLOBALISEL_PREDICATE_BITSET
#include "ZVMGenGlobalISel.inc"
#undef GET_GLOBALISEL_PREDICATE_BITSET

class ZVMInstructionSelector : public InstructionSelector {
  /// tblgen-erated 'select' implementation, used as the initial selector for
  /// the patterns that don't require complex C++.
  bool selectImpl(MachineInstr &I, CodeGenCoverage &CoverageInfo) const;

  const ZVMTargetMachine &TM;
  const ZVMSubtarget &STI;
  const ZVMInstrInfo &TII;
  const ZVMRegisterInfo &TRI;
  const ZVMRegisterBankInfo &RBI;

public:
  ZVMInstructionSelector(const ZVMTargetMachine &TM, const ZVMSubtarget &STI,
                         const ZVMRegisterBankInfo &RBI);

  bool select(MachineInstr &I) override;
  
  static const char *getName() { return DEBUG_TYPE; }

#define GET_GLOBALISEL_PREDICATES_DECL
#include "ZVMGenGlobalISel.inc"
#undef GET_GLOBALISEL_PREDICATES_DECL

// We declare the temporaries used by selectImpl() in the class to minimize the
// cost of constructing placeholder values.
#define GET_GLOBALISEL_TEMPORARIES_DECL
#include "ZVMGenGlobalISel.inc"
#undef GET_GLOBALISEL_TEMPORARIES_DECL
};

} // namespace

#define GET_GLOBALISEL_IMPL
#include "ZVMGenGlobalISel.inc"
#undef GET_GLOBALISEL_IMPL

ZVMInstructionSelector::ZVMInstructionSelector(const ZVMTargetMachine &TM,
                                               const ZVMSubtarget &STI,
                                               const ZVMRegisterBankInfo &RBI)
    : InstructionSelector(), TM(TM), STI(STI), TII(*STI.getInstrInfo()),
      TRI(*STI.getRegisterInfo()), RBI(RBI),
#define GET_GLOBALISEL_PREDICATES_INIT
#include "ZVMGenGlobalISel.inc"
#undef GET_GLOBALISEL_PREDICATES_INIT
#define GET_GLOBALISEL_TEMPORARIES_INIT
#include "ZVMGenGlobalISel.inc"
#undef GET_GLOBALISEL_TEMPORARIES_INIT
{
}

bool ZVMInstructionSelector::select(MachineInstr &I) {
  if (selectImpl(I, *CoverageInfo))
    return true;
  return false;
}

namespace llvm {
InstructionSelector *createZVMInstructionSelector(const ZVMTargetMachine &TM,
                                                  ZVMSubtarget &Subtarget,
                                                  ZVMRegisterBankInfo &RBI) {
  return new ZVMInstructionSelector(TM, Subtarget, RBI);
}
} // namespace llvm
