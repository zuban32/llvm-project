#ifndef LIB_TARGET_ZVM_ZVMTARGETMACHINE_H_
#define LIB_TARGET_ZVM_ZVMTARGETMACHINE_H_

//#include "ZVMInstrInfo.h"
//#include "ZVMSubtarget.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class ZVMTargetMachine : public LLVMTargetMachine {
public:
	ZVMTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
            StringRef FS, const TargetOptions &Options,
            Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
            CodeGenOpt::Level OL, bool JIT);
};

}


#endif /* LIB_TARGET_ZVM_ZVMTARGETMACHINE_H_ */
