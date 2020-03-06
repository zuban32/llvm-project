#include "ZVMMCTargetDesc.h"
#include "TargetInfo/ZVMTargetInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define GET_REGINFO_MC_DESC
#include "ZVMGenRegisterInfo.inc"

static MCInstrInfo *createZVMMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
//  InitZVMMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createZVMMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitZVMMCRegisterInfo(X, ZVM::R0);
  return X;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeZVMTargetMC() {
  // Register the MC asm info.
//  RegisterMCAsmInfoFn X(getTheZVMTarget(), createZVMMCAsmInfo);

  for (Target *T :
       {&getTheZVMTarget()}) {
    // Register the MC instruction info.
//    TargetRegistry::RegisterMCInstrInfo(*T, createZVMMCInstrInfo);

    // Register the MC register info.
    TargetRegistry::RegisterMCRegInfo(*T, createZVMMCRegisterInfo);

    // Register the MC subtarget info.
//    TargetRegistry::RegisterMCSubtargetInfo(*T, createZVMMCSubtargetInfo);

    // Register the MC Code Emitter.
//    TargetRegistry::RegisterMCCodeEmitter(*T, createZVMMCCodeEmitter);

    // Register the asm backend.
//    TargetRegistry::RegisterMCAsmBackend(*T, createZVMAsmBackend);

    // Register the object target streamer.
//    TargetRegistry::RegisterObjectTargetStreamer(*T,
//                                                 createObjectTargetStreamer);
//
//    // Register the asm streamer.
//    TargetRegistry::RegisterAsmTargetStreamer(*T, createTargetAsmStreamer);
//
//    // Register the MCInstPrinter
//    TargetRegistry::RegisterMCInstPrinter(*T, createZVMMCInstPrinter);
  }
}
