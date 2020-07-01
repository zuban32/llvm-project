#include "ZVMInstrInfo.h"
// #include "ZVMMCInstLower.h"
#include "ZVMTargetMachine.h"
#include "TargetInfo/ZVMTargetInfo.h"
#include "MCTargetDesc/ZVMTargetStreamer.h"
#include "MCTargetDesc/ZVMInstPrinter.h"
#include "TargetInfo/ZVMTargetInfo.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#define DEBUG_TYPE "asm-printer"

namespace {
class ZVMAsmPrinter : public AsmPrinter {
  ZVMTargetStreamer &getTargetStreamer() {
    return static_cast<ZVMTargetStreamer &>(*OutStreamer->getTargetStreamer());
  }

public:
  explicit ZVMAsmPrinter(TargetMachine &TM,
                         std::unique_ptr<MCStreamer> Streamer)
      : AsmPrinter(TM, std::move(Streamer)) {}

  bool doInitialization(Module &M) override;

  StringRef getPassName() const override { return "ZVM Assembly Printer"; }
  void printOperand(const MachineInstr *MI, int OpNum, raw_ostream &O);

  bool PrintAsmOperand(const MachineInstr *MI, unsigned OpNo,
                       const char *ExtraCode, raw_ostream &O) override;
  bool PrintAsmMemoryOperand(const MachineInstr *MI, unsigned OpNum,
                             const char *ExtraCode, raw_ostream &O) override;

  void emitFunctionBodyStart() override;
  void emitInstruction(const MachineInstr *MI) override;
};
} // namespace

bool ZVMAsmPrinter::doInitialization(Module &M) {
  AsmPrinter::doInitialization(M);

  return false;
}

void ZVMAsmPrinter::printOperand(const MachineInstr *MI, int OpNum,
                                 raw_ostream &O) {
  const MachineOperand &MO = MI->getOperand(OpNum);

  switch (MO.getType()) {
  case MachineOperand::MO_Register:
    O << ZVMInstPrinter::getRegisterName(MO.getReg());
    break;

  case MachineOperand::MO_Immediate:
    O << MO.getImm();
    break;

  case MachineOperand::MO_MachineBasicBlock:
    O << *MO.getMBB()->getSymbol();
    break;

  case MachineOperand::MO_GlobalAddress:
    O << *getSymbol(MO.getGlobal());
    break;

  case MachineOperand::MO_BlockAddress: {
    MCSymbol *BA = GetBlockAddressSymbol(MO.getBlockAddress());
    O << BA->getName();
    break;
  }

  case MachineOperand::MO_ExternalSymbol:
    O << *GetExternalSymbolSymbol(MO.getSymbolName());
    break;

  case MachineOperand::MO_JumpTableIndex:
  case MachineOperand::MO_ConstantPoolIndex:
  default:
    llvm_unreachable("<unknown operand type>");
  }
}

bool ZVMAsmPrinter::PrintAsmOperand(const MachineInstr *MI, unsigned OpNo,
                                    const char *ExtraCode, raw_ostream &O) {
  if (ExtraCode && ExtraCode[0])
    return AsmPrinter::PrintAsmOperand(MI, OpNo, ExtraCode, O);

  printOperand(MI, OpNo, O);
  return false;
}

bool ZVMAsmPrinter::PrintAsmMemoryOperand(const MachineInstr *MI,
                                          unsigned OpNum, const char *ExtraCode,
                                          raw_ostream &O) {
  assert(OpNum + 1 < MI->getNumOperands() && "Insufficient operands");
  const MachineOperand &BaseMO = MI->getOperand(OpNum);
  const MachineOperand &OffsetMO = MI->getOperand(OpNum + 1);
  assert(BaseMO.isReg() && "Unexpected base pointer for inline asm memory operand.");
  assert(OffsetMO.isImm() && "Unexpected offset for inline asm memory operand.");
  int Offset = OffsetMO.getImm();

  if (ExtraCode)
    return true; // Unknown modifier.

  if (Offset < 0)
    O << "(" << ZVMInstPrinter::getRegisterName(BaseMO.getReg()) << " - " << -Offset << ")";
  else
    O << "(" << ZVMInstPrinter::getRegisterName(BaseMO.getReg()) << " + " << Offset << ")";

  return false;
}

// static MCOperand LowerSymbolOperand(const MachineInstr *MI,
//                                     const MachineOperand &MO,
//                                     const MCSymbol *Symbol, AsmPrinter &AP) {
//   VEMCExpr::VariantKind Kind = (VEMCExpr::VariantKind)MO.getTargetFlags();

//   const MCSymbolRefExpr *MCSym = MCSymbolRefExpr::create(Symbol, AP.OutContext);
//   const VEMCExpr *expr = VEMCExpr::create(Kind, MCSym, AP.OutContext);
//   return MCOperand::createExpr(expr);
// }

static MCOperand LowerOperand(const MachineInstr *MI, const MachineOperand &MO) {
  switch (MO.getType()) {
  default:
    report_fatal_error("unsupported operand type");

  case MachineOperand::MO_Register:
    if (MO.isImplicit())
      break;
    return MCOperand::createReg(MO.getReg());

  // case MachineOperand::MO_ExternalSymbol:
  //   return LowerSymbolOperand(
  //       MI, MO, AP.GetExternalSymbolSymbol(MO.getSymbolName()), AP);
  // case MachineOperand::MO_GlobalAddress:
  //   return LowerSymbolOperand(MI, MO, AP.getSymbol(MO.getGlobal()), AP);
  case MachineOperand::MO_Immediate:
    return MCOperand::createImm(MO.getImm());

  // case MachineOperand::MO_MachineBasicBlock:
  //   return LowerSymbolOperand(MI, MO, MO.getMBB()->getSymbol(), AP);

  case MachineOperand::MO_RegisterMask:
    break;
  }
  return MCOperand();
}

static void LowerZVMMachineInstrToMCInst(const MachineInstr *MI, MCInst &OutMI) {
  OutMI.setOpcode(MI->getOpcode());

  for (unsigned i = 0, e = MI->getNumOperands(); i != e; ++i) {
    const MachineOperand &MO = MI->getOperand(i);
    MCOperand MCOp = LowerOperand(MI, MO);

    if (MCOp.isValid())
      OutMI.addOperand(MCOp);
  }
}


void ZVMAsmPrinter::emitInstruction(const MachineInstr *MI) {
  MCInst TmpInst;

  LowerZVMMachineInstrToMCInst(MI, TmpInst);

  EmitToStreamer(*OutStreamer, TmpInst);
}

void ZVMAsmPrinter::emitFunctionBodyStart() {

}

// Force static initialization.
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeZVMAsmPrinter() {
  RegisterAsmPrinter<ZVMAsmPrinter> X(getTheZVMTarget());
}