/***************************************************************/
/*                                                             */
/*   RISC-V RV32 Instruction Level Simulator                   */
/*                                                             */
/*   ECEN 4243                                                 */
/*   Oklahoma State University                                 */
/*                                                             */
/***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"

#ifndef _SIM_ISA_H_
#define _SIM_ISA_H_


// #define SIGNEXT(v, sb) ((v) | (((v) & (1 << (sb))) ? ~((1 << (sb))-1) : 0))
// #define SIGNEXT(v, sb) ((v) << (31 - (sb)) >> (31 - (sb)))
#define SIGNEXT(v,sb) ((((v >> (sb - 1)) == 0x1) ? (0xFFFFFFFF << sb) | v : v))

// int32_t SIGNEXT(int32_t v, int sb) {
//   int32_t result = (v << (32 - sb)) >> (32 - sb);
//   return result;
// }
// R instruction    R instruction   R instruction
int ADD (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] + CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SUB (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = CURRENT_STATE.REGS[Rs1] - CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SLL (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = CURRENT_STATE.REGS[Rs1] << CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SLT (int Rd, int Rs1, int Rs2, int Funct3) {
  if (CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2]) {
    NEXT_STATE.REGS[Rd] = CURRENT_STATE.REGS[Rs1];
  }else {
    NEXT_STATE.REGS[Rd] = CURRENT_STATE.REGS[Rs2];
  }
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SLTU (int Rd, int Rs1, int Rs2, int Funct3) {
  if (CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2]){
    NEXT_STATE.REGS[Rd] = CURRENT_STATE.REGS[Rs1];
  }else {
    NEXT_STATE.REGS[Rd] = CURRENT_STATE.REGS[Rs2];
  }
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int XOR (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = CURRENT_STATE.REGS[Rs1] ^ CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SRL (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = CURRENT_STATE.REGS[Rs1] >> CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SRA (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = CURRENT_STATE.REGS[Rs1] >>= CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int OR (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = CURRENT_STATE.REGS[Rs1] | CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int AND (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = CURRENT_STATE.REGS[Rs1] & CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}
// R instruction    R instruction   R instruction




// I Instructions   I Instructions    I Instructions
int ADDI (int Rd, int Rs1, int Imm, int Funct3) {
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm,12);
  NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int LB (int Rd, int Rs1, int Imm, int Funct3){
  uint32_t address = CURRENT_STATE.REGS[Rs1] + Imm;
  uint32_t word = mem_read_32(address);
  uint8_t byte;
  if (address & 0x3 == 0) {
    byte = word & 0xFF;
  } else if ((address & 0x3) == 1) {
    byte = (word >> 8) & 0xFF;
  } else if ((address & 0x3) == 2) {
    byte = (word >> 16) & 0xFF;
  } else {
    byte = (word >> 24) & 0xFF;
  }
  NEXT_STATE.REGS[Rd] = SIGNEXT(byte, 7);
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int LH (int Rd, int Rs1, int Imm, int Funct3){
  uint32_t address = CURRENT_STATE.REGS[Rs1] + Imm;
  uint32_t word = mem_read_32(address);
  uint16_t halfword;
  if (address & 0x2) {
    halfword = (word >> 16) & 0xffff;
  } else {
    halfword = word & 0xffff;
  }
  NEXT_STATE.REGS[Rd] = SIGNEXT(halfword, 15);
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int LW (int Rd, int Rs1, int Imm, int Funct3){
  uint32_t address = CURRENT_STATE.REGS[Rs1] + Imm;
  uint32_t word = mem_read_32(address);
  NEXT_STATE.REGS[Rd] = word;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int LBU (int Rd, int Rs1, int Imm, int Funct3){
  int cur = CURRENT_STATE.REGS[Rs1] & 0x7f;
  NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int LHU (int Rd, int Rs1, int Imm, int Funct3){
  int cur = CURRENT_STATE.REGS[Rs1] & 0x7fff;
  NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SLLI (int Rd, int Rs1, int Imm, int Funct3){
  int cur = CURRENT_STATE.REGS[Rs1] << Imm & 0x7fffffff;
  NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SLTI (int Rd, int Rs1, int Imm, int Funct3){
  int cur = (CURRENT_STATE.REGS[Rs1] < SIGNEXT(Imm, 12));
  NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SLTIU (int Rd, int Rs1, int Imm, int Funct3){
  int cur = (CURRENT_STATE.REGS[Rs1] < SIGNEXT(Imm, 12));
  NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int XORI (int Rd, int Rs1, int Imm, int Funct3){
  int cur = (CURRENT_STATE.REGS[Rs1] ^ SIGNEXT(Imm, 12));
  NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SRLI (int Rd, int Rs1, int Imm, int Funct3){
  int cur = CURRENT_STATE.REGS[Rs1] >> Imm & 0x7fffffff;
  NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SRAI (int Rd, int Rs1, int Imm, int Funct3){
  int cur = CURRENT_STATE.REGS[Rs1] >>= Imm & 0x7fffffff;
  NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int ORI (int Rd, int Rs1, int Imm, int Funct3){
  int cur = CURRENT_STATE.REGS[Rs1] | SIGNEXT(Imm, 12);
  NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int ANDI (int Rd, int Rs1, int Imm, int Funct3){
  int cur = CURRENT_STATE.REGS[Rs1] & SIGNEXT(Imm, 12);
  NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}
// I Instructions   I Instructions    I Instructions




// U Instruction    U Instruction   U Instruction
int AUIPC (int Rd, int Imm) {
  NEXT_STATE.REGS[Rd] = CURRENT_STATE.PC + Imm;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int LUI (int Rd, int Imm) {
  NEXT_STATE.REGS[Rd] = Imm;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}
// U Instruction    U Instruction   U Instruction




// S Instruction    S Instruction   S Instruction
int SB (int Rs1, int Rs2, int Imm, int Funct3){
  uint32_t address = CURRENT_STATE.REGS[Rs1] + Imm;
  uint32_t word = mem_read_32(address & ~0x3);
  uint8_t byte = CURRENT_STATE.REGS[Rs2] & 0x000000FF;
  if ((address & 0x3) == 0) {
    word = (word & 0xFFFFFF00) | byte;
  } else if ((address & 0x3) == 1) {
    word = (word & 0xFFFF00FF) | (byte << 8);
  } else if ((address & 0x3) == 2) {
    word = (word & 0xFF00FFFF) | (byte << 16);
  } else {
    word = (word & 0x00FFFFFF) | byte << 24;
  }
  mem_write_32(address & ~0x3, word);
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SH (int Rs1, int Rs2, int Imm, int Funct3) {
  uint32_t address = CURRENT_STATE.REGS[Rs1] + Imm;
  uint32_t word = mem_read_32(address & ~0x2);
  uint16_t halfword = CURRENT_STATE.REGS[Rs2] & 0x0000FFFF;
  if (address & 0x2) {
    word = (word & 0x0000FFFF) | (halfword << 16);
  } else {
    word = (word & 0xFFFF0000) | halfword;
  }
  mem_write_32(address & ~0x2, word);
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;

  return 0;
} 

int SW (int Rs1, int Rs2, int Imm, int Funct3) {
  uint32_t address = CURRENT_STATE.REGS[Rs1] + Imm;
  mem_write_32(address, CURRENT_STATE.REGS[Rs2]);
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
} 
// S Instruction    S Instruction   S Instruction




// B instructions   B instructions    B instructions
int BEQ (int Rs1, int Rs2, int Imm, int Funct3) {
  if (CURRENT_STATE.REGS[Rs1] == CURRENT_STATE.REGS[Rs2]) {
    NEXT_STATE.PC = (CURRENT_STATE.PC) + (SIGNEXT(Imm,13));
  } else {
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  }
  return 0;
} 

int BNE (int Rs1, int Rs2, int Imm, int Funct3) {
  int cur = 0;
  if (CURRENT_STATE.REGS[Rs1] != CURRENT_STATE.REGS[Rs2]) {
    NEXT_STATE.PC = (CURRENT_STATE.PC) + SIGNEXT(Imm,13);
  } else {
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  }
  return 0;
}

int BLT (int Rs1, int Rs2, int Imm, int Funct3) {
  if (CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2]) {
    NEXT_STATE.PC = (CURRENT_STATE.PC) + (SIGNEXT(Imm,13));
  } else {
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  }
  return 0;
}

int BGE (int Rs1, int Rs2, int Imm, int Funct3) {
  if (CURRENT_STATE.REGS[Rs1] >= CURRENT_STATE.REGS[Rs2]) {
    NEXT_STATE.PC = (CURRENT_STATE.PC) + (SIGNEXT(Imm,13));
  } else {
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  }
  return 0;
} 

int BLTU (int Rs1, int Rs2, int Imm, int Funct3) {
  if (CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2]) {
    NEXT_STATE.PC = (CURRENT_STATE.PC) + (SIGNEXT(Imm,13));
  } else {
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  }
  return 0;
} 

int BGEU (int Rs1, int Rs2, int Imm, int Funct3) {
  if (CURRENT_STATE.REGS[Rs1] >= CURRENT_STATE.REGS[Rs2]) {
    NEXT_STATE.PC = (CURRENT_STATE.PC) + (SIGNEXT(Imm,13));
  } else {
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  }
  return 0;
} 
// B instructions   B instructions    B instructions




// I instruction I instruction I instruction
int JALR (int Rd, int Rs1, int Imm) {
    NEXT_STATE.PC = CURRENT_STATE.REGS[Rs1] + (SIGNEXT(Imm,20));
    NEXT_STATE.REGS[Rd] = CURRENT_STATE.PC + 4;
    return 0;
} 
// I instruction I instruction I instruction




// J instruction J instruction J instruction
int JAL (int Rd, int imm) {
    NEXT_STATE.PC = CURRENT_STATE.REGS[Rs1] + (SIGNEXT(imm,20));
    NEXT_STATE.REGS[Rd] = CURRENT_STATE.PC + 4;
    return 0;
} 
// J instruction J instruction J instruction



// ECALL
int ECALL (char* i_){
  
  return 0;
} 

#endif
