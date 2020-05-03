set (LLVM_TARGET_DEFINITIONS ZVM.td)

tablegen(LLVM ZVMGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM ZVMGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM ZVMGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM ZVMGenSubtargetInfo.inc -gen-subtarget)

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
)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
