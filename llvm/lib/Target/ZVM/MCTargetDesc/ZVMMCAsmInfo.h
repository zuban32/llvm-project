//=====-- AArch64MCAsmInfo.h - AArch64 asm properties ---------*- C++ -*--====//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the AArch64MCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_ZVM_MCTARGETDESC_ZVMMCASMINFO_H
#define LLVM_LIB_TARGET_ZVM_MCTARGETDESC_ZVMMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"
#include "llvm/MC/MCAsmInfoDarwin.h"

namespace llvm {
class MCStreamer;
class Target;
class Triple;

struct ZVMMCAsmInfoELF : public MCAsmInfoELF {
  explicit ZVMMCAsmInfoELF();
};

struct ZVMMCAsmInfoDarwin : public MCAsmInfoDarwin {
  explicit ZVMMCAsmInfoDarwin();
};

} // namespace llvm

#endif
