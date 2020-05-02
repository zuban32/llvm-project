#include "MCTargetDesc/ZVMInstPrinter.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"

using namespace llvm;

#define DEBUG_TYPE "asm-printer"

// Include the auto-generated portion of the assembly writer.
#include "ZVMGenAsmWriter.inc"

void ZVMInstPrinter::printInst(const MCInst *MI, uint64_t Address,
                               StringRef Annot, const MCSubtargetInfo &STI,
                               raw_ostream &O) {
  printInstruction(MI, Address, O);
//   printAnnotation(O, Annot);
}

void ZVMInstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
                                  raw_ostream &O, const char *Modifier) {
//   assert((Modifier == 0 || Modifier[0] == 0) && "No modifiers supported");
//   const MCOperand &Op = MI->getOperand(OpNo);
//   if (Op.isReg()) {
//     O << getRegisterName(Op.getReg());
//   } else if (Op.isImm()) {
//     O << formatImm((int32_t)Op.getImm());
//   } else {
//     assert(Op.isExpr() && "Expected an expression");
//     printExpr(Op.getExpr(), O);
//   }
}