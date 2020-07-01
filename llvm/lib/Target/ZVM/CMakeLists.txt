set (LLVM_TARGET_DEFINITIONS ZVM.td)

tablegen(LLVM ZVMGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM ZVMGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM ZVMGenRegisterBank.inc -gen-register-bank)
tablegen(LLVM ZVMGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM ZVMGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM ZVMGenGlobalISel.inc -gen-global-isel)

add_public_tablegen_target(ZVMCommonTableGen)

add_llvm_target(ZVMCodeGen
	ZVMTargetMachine.cpp
	ZVMAsmPrinter.cpp
	ZVMSubtarget.cpp
	ZVMRegisterInfo.cpp
	ZVMFrameLowering.cpp
	ZVMAsmPrinter.cpp
	ZVMTargetLowering.cpp
	ZVMInstrInfo.cpp
	ZVMCallLowering.cpp
	ZVMLegalizerInfo.cpp
	ZVMTargetObjectFile.cpp
	ZVMRegisterBankInfo.cpp
	ZVMInstructionSelector.cpp
)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
