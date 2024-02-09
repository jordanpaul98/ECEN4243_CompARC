/***************************************************************/
/*                                                             */
/*   RISC-V RV32 Instruction Level Simulator                   */
/*                                                             */
/*   ECEN 4243                                                 */
/*   Oklahoma State University                                 */
/*                                                             */
/***************************************************************/

#ifndef _SIM_ISA_H_
#define _SIM_ISA_H_

#include "shell.h"

//
// MACRO: Check sign bit (sb) of (v) to see if negative
//   if no, just give number
//   if yes, sign extend (e.g., 0x80_0000 -> 0xFF80_0000)
//
#define SIGNEXT(v, sb) ((v) | (((v) & (1 << (sb))) ? ~((1 << (sb))-1) : 0))

int ADD (int Rd, int Rs1, int Rs2, int Funct3);

int ADDI (int Rd, int Rs1, int Imm, int Funct3);

int BNE (int Rs1, int Rs2, int Imm, int Funct3);

// I Instructions   I Instructions    I Instructions
// I Instructions   I Instructions    I Instructions
int LB (int Rd, int Rs1, int Imm, int Funct3);

int LH (int Rd, int Rs1, int Imm, int Funct3);

int LW (int Rd, int Rs1, int Imm, int Funct3);

int LBU (int Rd, int Rs1, int Imm, int Funct3);

int LHU (int Rd, int Rs1, int Imm, int Funct3);

int SLLI (int Rd, int Rs1, int Imm, int Funct3);

int SLTI (int Rd, int Rs1, int Imm, int Funct3);

int SLTIU (int Rd, int Rs1, int Imm, int Funct3);

int XORI (int Rd, int Rs1, int Imm, int Funct3);

int SRLI (int Rd, int Rs1, int Imm, int Funct3);

int SRAI (int Rd, int Rs1, int Imm, int Funct3);

int ORI (int Rd, int Rs1, int Imm, int Funct3);

int ANDI (int Rd, int Rs1, int Imm, int Funct3);

// U Instruction    U Instruction   U Instruction
// U Instruction    U Instruction   U Instruction
int AUIPC (int Rd, int Imm);
int LUI (int Rd, int Imm);

// S Instruction    S Instruction   S Instruction
// S Instruction    S Instruction   S Instruction
int SB (int Rs1, int Rs2, int Imm, int Funct3){
  int effAddr = 0;
  effAddr = CURRENT_STATE.REGS[Rs1] + SIGNEXT(imm, 12);
  int mask = 0x3;
  int offset = effAddr & mask;
  int allignAddr = effAddr & ~mask;
  int wordReadData = mem_read_32(allignAddr);
  int writeData = CURRENT_STATE.REGS[Rs2] & 0xFF;
  writeData = writeData << 8 * offset;
  NEXT_STATE.REGS[Rd] = cur;
  mem_write_32(effAddr, CURRENT_STATE.REGS[Rs2];
  return 0;
}
int SH (int Rs1, int Rs2, int Imm, int Funct3);
int SW (int Rs1, int Rs2, int Imm, int Funct3);

// R instruction    R instruction   R instruction
// R instruction    R instruction   R instruction
int SUB (int Rd, int Rs1, int Rs2, int Funct3);

int SLL (int Rd, int Rs1, int Rs2, int Funct3);

int SLT (int Rd, int Rs1, int Rs2, int Funct3);

int SLTU (int Rd, int Rs1, int Rs2, int Funct3);

int XOR (int Rd, int Rs1, int Rs2, int Funct3);

int SRL (int Rd, int Rs1, int Rs2, int Funct3);

int SRA (int Rd, int Rs1, int Rs2, int Funct3);

int OR (int Rd, int Rs1, int Rs2, int Funct3);

int AND (int Rd, int Rs1, int Rs2, int Funct3);

// B instructions   B instructions    B instructions
// B instructions   B instructions    B instructions
int BEQ (int Rs1, int Rs2, int Imm, int Funct3);
int BLT (int Rs1, int Rs2, int Imm, int Funct3);
int BGE (int Rs1, int Rs2, int Imm, int Funct3);
int BLTU (int Rs1, int Rs2, int Imm, int Funct3);
int BGEU (int Rs1, int Rs2, int Imm, int Funct3);

// I instruction
int JALR (int Rd, int Rs1, int Imm);

// J instruction
int JAL (int Rd, int imm);

int ECALL (char* i_);

#endif
