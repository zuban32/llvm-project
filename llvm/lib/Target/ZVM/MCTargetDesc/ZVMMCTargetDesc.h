/*
 * ZVMMCTargetDesc.h
 *
 *  Created on: 6 мар. 2020 г.
 *      Author: zuban
 */

#ifndef LIB_TARGET_ZVM_MCTARGETDESC_ZVMMCTARGETDESC_H_
#define LIB_TARGET_ZVM_MCTARGETDESC_ZVMMCTARGETDESC_H_


#include "llvm/Support/DataTypes.h"

#include <memory>

namespace llvm {
class MCAsmBackend;
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCObjectTargetWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class MCTargetOptions;
class Target;
class Triple;
class StringRef;
class raw_pwrite_stream;
class raw_ostream;

MCCodeEmitter *createZVMMCCodeEmitter(const MCInstrInfo &MCII,
                                        const MCRegisterInfo &MRI,
                                        MCContext &Ctx);
MCAsmBackend *createZVMAsmBackend(const Target &T, const MCSubtargetInfo &STI,
                                    const MCRegisterInfo &MRI,
                                    const MCTargetOptions &Options);
std::unique_ptr<MCObjectTargetWriter> createZVMELFObjectWriter(bool Is64Bit,
                                                                 uint8_t OSABI);
} // End llvm namespace

// Defines symbolic names for ZVM registers.  This defines a mapping from
// register name to register number.
//
#define GET_REGINFO_ENUM
#include "ZVMGenRegisterInfo.inc"

// Defines symbolic names for the ZVM instructions.
//
#define GET_INSTRINFO_ENUM
//#include "ZVMGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
//#include "ZVMGenSubtargetInfo.inc"


#endif /* LIB_TARGET_ZVM_MCTARGETDESC_ZVMMCTARGETDESC_H_ */
