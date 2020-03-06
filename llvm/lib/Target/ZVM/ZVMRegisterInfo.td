class ZVMReg<bits<16> Enc, string n> : Register<n> {
  let HWEncoding = Enc;
  let Namespace = "ZVM";
}

foreach i = 0-15 in {
	def R#i: ZVMReg<i, "r"#i>;
}

def SP: ZVMReg<16, "sp">;

def GPRegs : RegisterClass<"ZVM", [i64], 64, (sequence "R%u", 0, 15)>;