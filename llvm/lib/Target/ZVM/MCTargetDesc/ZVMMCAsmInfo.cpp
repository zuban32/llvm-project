//===-- AArch64MCAsmInfo.cpp - AArch64 asm properties ---------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the AArch64MCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "ZVMMCAsmInfo.h"
#include "llvm/ADT/Triple.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/Support/CommandLine.h"

using namespace llvm;

ZVMMCAsmInfoELF::ZVMMCAsmInfoELF() {
  CodePointerSize = 4;
}
