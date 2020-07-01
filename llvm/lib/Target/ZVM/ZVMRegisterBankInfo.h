#ifndef LLVM_LIB_TARGET_AARCH64_AARCH64REGISTERBANKINFO_H
#define LLVM_LIB_TARGET_AARCH64_AARCH64REGISTERBANKINFO_H

#include "llvm/CodeGen/GlobalISel/RegisterBankInfo.h"

#define GET_REGBANK_DECLARATIONS
#include "ZVMGenRegisterBank.inc"

namespace llvm {

class TargetRegisterInfo;

class ZVMGenRegisterBankInfo : public RegisterBankInfo {
protected:
#define GET_TARGET_REGBANK_CLASS
#include "ZVMGenRegisterBank.inc"
};

class ZVMRegisterBankInfo final : public ZVMGenRegisterBankInfo {
public:
    ZVMRegisterBankInfo(const TargetRegisterInfo &TRI);

    const RegisterBankInfo::InstructionMapping &
    getInstrMapping(const MachineInstr &MI) const override;
};
}

#endif
