set (LLVM_TARGET_DEFINITIONS ZVM.td)

add_llvm_target(ZVMCodeGen ZVMTargetMachine.cpp)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
