class OperZVM<bits<8> V>: Operand<i8> {
    bits<2> Kind = V{7-6};
    bits<6> Val = V{5-0};
}

class InstZVM<bits<6> Opc, dag outs, dag ins, string asmstr, list<dag> pattern=[]>: Instruction {
    field bits<32> Inst;
    let Size = 4;

    // bits<6> Op;
    bits<4> W;
    bits<6> rd;
    bits<8> rs1;
    bits<8> rs2;

    let Inst{31-26} = Opc;
    let Inst{25-22} = W;
    let Inst{21-16} = rd;
    
    let Namespace = "ZVM";

    dag OutOperandList = outs;
    dag InOperandList = ins;
    let AsmString = asmstr;
    let Pattern = pattern;
}

class Pseudo<dag outs, dag ins, string asmstr, list<dag> pattern>
  : InstZVM<-1, outs, ins, asmstr, pattern> {
  let Inst{31-0} = 0;
  let isPseudo = 1;
}