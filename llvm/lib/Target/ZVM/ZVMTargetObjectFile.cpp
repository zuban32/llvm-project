//===------- ZVMTargetObjectFile.cpp - ZVM Object Info Impl -----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ZVMTargetObjectFile.h"
#include "llvm/BinaryFormat/Dwarf.h"
#include "llvm/CodeGen/MachineModuleInfoImpls.h"
#include "llvm/CodeGen/TargetLowering.h"

using namespace llvm;

void ZVMMachOTargetObjectFile::Initialize(MCContext &Ctx,
                                          const TargetMachine &TM) {
  TargetLoweringObjectFileMachO::Initialize(Ctx, TM);
}

const MCExpr *ZVMMachOTargetObjectFile::getTTypeGlobalReference(
    const GlobalValue *GV, unsigned Encoding, const TargetMachine &TM,
    MachineModuleInfo *MMI, MCStreamer &Streamer) const {

  return TargetLoweringObjectFileMachO::getTTypeGlobalReference(GV, Encoding, TM,
                                                              MMI, Streamer);
}
