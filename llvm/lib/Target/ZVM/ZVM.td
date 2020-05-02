include "llvm/Target/Target.td"

include "ZVMRegisterInfo.td"
include "ZVMInstrInfo.td"

def ZVMInstrInfo : InstrInfo;

class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"zvm0",  []>;

def ZVM : Target {
  let InstructionSet = ZVMInstrInfo;
}