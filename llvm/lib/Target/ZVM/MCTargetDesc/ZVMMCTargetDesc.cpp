#include "ZVMMCTargetDesc.h"
#include "ZVMMCAsmInfo.h"
#include "ZVMInstPrinter.h"
#include "TargetInfo/ZVMTargetInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "ZVMGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "ZVMGenSubtargetInfo.inc"

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

static MCAsmInfo *createZVMMCAsmInfo(const MCRegisterInfo &MRI,
                                     const Triple &TheTriple,
                                     const MCTargetOptions &Options) {
  MCAsmInfo *MAI;
  if (TheTriple.isOSBinFormatELF())
    MAI = new ZVMMCAsmInfoELF();
  else if (TheTriple.isOSBinFormatMachO())
    MAI = new ZVMMCAsmInfoDarwin();
  else
    report_fatal_error("invalid target");

  // Initial state of the frame pointer is SP.
  // unsigned Reg = MRI.getDwarfRegNum(AArch64::SP, true);
  // MCCFIInstruction Inst = MCCFIInstruction::createDefCfa(nullptr, Reg, 0);
  // MAI->addInitialFrameState(Inst);

  return MAI;
}

static MCInstPrinter *createZVMMCInstPrinter(const Triple &T,
                                             unsigned SyntaxVariant,
                                             const MCAsmInfo &MAI,
                                             const MCInstrInfo &MII,
                                             const MCRegisterInfo &MRI) {
  if (SyntaxVariant == 0)
    return new ZVMInstPrinter(MAI, MII, MRI);
  return nullptr;
}

static MCSubtargetInfo *createZVMMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU, StringRef FS) {
  return createZVMMCSubtargetInfoImpl(TT, CPU, FS);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeZVMTargetMC() {
  for (Target *T : {&getTheZVMTarget()}) {
    RegisterMCAsmInfoFn X(*T, createZVMMCAsmInfo);
    // Register the MC instruction info.
    TargetRegistry::RegisterMCInstrInfo(*T, createZVMMCInstrInfo);

    // Register the MC register info.
    TargetRegistry::RegisterMCRegInfo(*T, createZVMMCRegisterInfo);

    // Register the MC subtarget info.
    TargetRegistry::RegisterMCSubtargetInfo(*T, createZVMMCSubtargetInfo);

    // Register the MC Code Emitter.
    //    TargetRegistry::RegisterMCCodeEmitter(*T, createZVMMCCodeEmitter);

    // Register the asm backend.
    //    TargetRegistry::RegisterMCAsmBackend(*T, createZVMAsmBackend);

    // Register the object target streamer.
    //    TargetRegistry::RegisterObjectTargetStreamer(*T,
    //                                                 createObjectTargetStreamer);
    //
    //    // Register the asm streamer.
    //    TargetRegistry::RegisterAsmTargetStreamer(*T,
    //    createTargetAsmStreamer);
    //
    // Register the MCInstPrinter
    TargetRegistry::RegisterMCInstPrinter(*T, createZVMMCInstPrinter);
  }
}
