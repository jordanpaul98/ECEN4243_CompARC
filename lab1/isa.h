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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

//
// MACRO: Check sign bit (sb) of (v) to see if negative
//   if no, just give number
//   if yes, sign extend (e.g., 0x80_0000 -> 0xFF80_0000)
//
#define SIGNEXT(v, sb) ((v) | (((v) & (1 << (sb))) ? ~((1 << (sb))-1) : 0))

int ADD (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] + CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int ADDI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm,12);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

int BNE (int Rs1, int Rs2, int Imm, int Funct3) {

  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] != CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC - 4) + (SIGNEXT(Imm,12));
  return 0;

}

// I Instructions   I Instructions    I Instructions
// I Instructions   I Instructions    I Instructions
int LB (int Rd, int Rs1, int Imm, int Funct3){
  int cur = CURRENT_STATE.REGS[Rs1];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int LH (int Rd, int Rs1, int Imm, int Funct3){
  int cur = CURRENT_STATE.REGS[Rs1];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int LW (int Rd, int Rs1, int Imm, int Funct3){
  int cur = CURRENT_STATE.REGS[Rs1];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int LBU (int Rd, int Rs1, int Imm, int Funct3){
  int cur = CURRENT_STATE.REGS[Rs1] & 0x7f;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int LHU (int Rd, int Rs1, int Imm, int Funct3){
  int cur = CURRENT_STATE.REGS[Rs1] & 0x7fff;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int SLLI (int Rd, int Rs1, int Imm, int Funct3){
  int cur = CURRENT_STATE.REGS[Rs1] << Imm & 0x7fffffff;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int SLTI (int Rd, int Rs1, int Imm, int Funct3){
  int cur = (CURRENT_STATE.REGS[Rs1] < SIGNEXT(Imm, 12));
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int SLTIU (int Rd, int Rs1, int Imm, int Funct3){
  int cur = (CURRENT_STATE.REGS[Rs1] < SIGNEXT(Imm, 12));
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int XORI (int Rd, int Rs1, int Imm, int Funct3){
  int cur = (CURRENT_STATE.REGS[Rs1] ^ SIGNEXT(Imm, 12));
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int SRLI (int Rd, int Rs1, int Imm, int Funct3){
  int cur = CURRENT_STATE.REGS[Rs1] >> Imm & 0x7fffffff;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int SRAI (int Rd, int Rs1, int Imm, int Funct3){
  int cur = CURRENT_STATE.REGS[Rs1] >>= Imm & 0x7fffffff;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int ORI (int Rd, int Rs1, int Imm, int Funct3){
  int cur = CURRENT_STATE.REGS[Rs1] | SIGNEXT(Imm, 12);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int ANDI (int Rd, int Rs1, int Imm, int Funct3){
  int cur = CURRENT_STATE.REGS[Rs1] & SIGNEXT(Imm, 12);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

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
int SUB (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = CURRENT_STATE.REGS[Rs1] - CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int SLL (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = CURRENT_STATE.REGS[Rs1] << CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int SLT (int Rd, int Rs1, int Rs2, int Funct3) {
  if (CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2]) {
      NEXT_STATE.REGS[Rd] = CURRENT_STATE.REGS[Rs1];
  }else {
      NEXT_STATE.REGS[Rd] = CURRENT_STATE.REGS[Rs2];
  }
  return 0;
}

int SLTU (int Rd, int Rs1, int Rs2, int Funct3) {
  if (CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2]){
    NEXT_STATE.REGS[Rd] = CURRENT_STATE.REGS[Rs1];
  }else {
    NEXT_STATE.REGS[Rd] = CURRENT_STATE.REGS[Rs2];
  }
  return 0;
}

int XOR (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = CURRENT_STATE.REGS[Rs1] ^ CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int SRL (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = CURRENT_STATE.REGS[Rs1] >> CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int SRA (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = CURRENT_STATE.REGS[Rs1] >>= CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int OR (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = CURRENT_STATE.REGS[Rs1] | CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int AND (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = CURRENT_STATE.REGS[Rs1] & CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

// B instructions   B instructions    B instructions
// B instructions   B instructions    B instructions
int BEQ (int Rs1, int Rs2, int Imm, int Funct3) {
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] == CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC - 4) + (SIGNEXT(Imm,13));
  return 0;
}
int BLT (int Rs1, int Rs2, int Imm, int Funct3) {
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC - 4) + (SIGNEXT(Imm,13));
  return 0;
}
int BGE (int Rs1, int Rs2, int Imm, int Funct3) {
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] >= CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC - 4) + (SIGNEXT(Imm,13));
  return 0;
}
int BLTU (int Rs1, int Rs2, int Imm, int Funct3) {
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC - 4) + (SIGNEXT(Imm,13));
  return 0;
}
int BGEU (int Rs1, int Rs2, int Imm, int Funct3) {
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] >= CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC - 4) + (SIGNEXT(Imm,13));
  return 0;
}

// I instruction
int JALR (int Rd, int Rs1, int Imm);

// J instruction
int JAL (int Rd, int imm);

int ECALL (char* i_){return 0;}

#endif
