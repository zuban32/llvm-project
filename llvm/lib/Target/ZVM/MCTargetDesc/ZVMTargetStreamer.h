//===-- ZVMTargetStreamer.h - ZVM Target Streamer ----------*- C++ -*--===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_ZVM_MCTARGETDESC_ZVMTARGETSTREAMER_H
#define LLVM_LIB_TARGET_ZVM_MCTARGETDESC_ZVMTARGETSTREAMER_H

#include "llvm/MC/MCStreamer.h"

namespace llvm {
class ZVMTargetStreamer : public MCTargetStreamer {
  virtual void anchor();

public:
  ZVMTargetStreamer(MCStreamer &S);
  /// Emit ".register <reg>, #ignore".
  virtual void emitZVMRegisterIgnore(unsigned reg) = 0;
  /// Emit ".register <reg>, #scratch".
  virtual void emitZVMRegisterScratch(unsigned reg) = 0;
};
}

#endif
