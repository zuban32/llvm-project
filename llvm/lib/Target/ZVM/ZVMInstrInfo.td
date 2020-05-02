include "ZVMInstrFormats.td"

def ADD : InstZVM <0, (outs GPRegs:$dst), (ins GPRegs:$src1, GPRegs:$src2),
                 "add $dst <- $src1, $src2">;