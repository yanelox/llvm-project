//===----------------------------------------------------------------------===//
//  Describe instructions format
//
//  CPU INSTRUCTION FORMATS
//
//  FF FF FF FF
//        ^^ ^^ - r2_imm - second source reg / imm
//      ^       - r1     - first source reg
//     ^        - rd     - dest reg
//  ^^          - opcode - instr code
//
//===----------------------------------------------------------------------===//

class MyArchInst<bits<8> op, dag outs, dag ins, string asmstr, list<dag> pattern>: Instruction
{
  let Namespace = "MyArch";
  let DecoderNamespace = "MyArch";
  let Size = 4;

  field bits<32> Inst;

  bits<8> opcode = op;
  bits<4>  rd = 0;
  bits<4>  r1 = 0;
  bits<16> r2_imm = 0;

  let Inst{31-24} = opcode;
  let Inst{23-20} = rd;
  let Inst{19-16} = r1;
  let Inst{15-0}  = r2_imm;

  let OutOperandList = outs;
  let InOperandList  = ins;
  let AsmString   = asmstr;
  let Pattern     = pattern;

}

class MyArchPseudoInst<dag outs, dag ins, string asmstr, list<dag> pattern>
: MyArchInst<0, outs, ins, asmstr, pattern> {
  let isPseudo = 1;
  let isCodeGenOnly = 1;
}