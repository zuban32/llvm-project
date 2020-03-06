set (LLVM_TARGET_DEFINITIONS ZVM.td)

tablegen(LLVM ZVMGenRegisterInfo.inc -gen-register-info)

add_public_tablegen_target(ZVMCommonTableGen)

add_llvm_target(ZVMCodeGen ZVMTargetMachine.cpp)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
