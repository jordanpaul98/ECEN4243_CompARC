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

#define BLOCK_ZERO_WRITE 1

// #define SIGNEXT(v, sb) ((v) | (((v) & (1 << (sb))) ? ~((1 << (sb))-1) : 0))
// #define SIGNEXT(v, sb) ((v) << (31 - (sb)) >> (31 - (sb)))
#define SIGNEXT(v,sb) ((((v >> (sb - 1)) == 0x1) ? (0xFFFFFFFF << sb) | v : v))

// int32_t SIGNEXT(int32_t v, int sb) {
//   int32_t result = (v << (32 - sb)) >> (32 - sb);
//   return result;
// }
// R instruction    R instruction   R instruction
int ADD (int Rd, int Rs1, int Rs2, int Funct3) {
  printf("ADD: Rd[%i]  Rs1[%i] = %i,  Rs2[%i] = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], Rs2, CURRENT_STATE.REGS[Rs2]);
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] + CURRENT_STATE.REGS[Rs2];
  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SUB (int Rd, int Rs1, int Rs2, int Funct3) {
  printf("SUB: Rd[%i]  Rs1[%i] = %i,  Rs2[%i] = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], Rs2, CURRENT_STATE.REGS[Rs2]);
  int cur = CURRENT_STATE.REGS[Rs1] - CURRENT_STATE.REGS[Rs2];
  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SLL (int Rd, int Rs1, int Rs2, int Funct3) {
  printf("SLL: Rd[%i]  Rs1[%i] = %i,  Rs2[%i] = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], Rs2, CURRENT_STATE.REGS[Rs2]);
  int cur = CURRENT_STATE.REGS[Rs1] << CURRENT_STATE.REGS[Rs2];
  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SLT (int Rd, int Rs1, int Rs2, int Funct3) {
  printf("SLT: Rd[%i]  Rs1[%i] = %i,  Rs2[%i] = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], Rs2, CURRENT_STATE.REGS[Rs2]);
  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = ((int)CURRENT_STATE.REGS[Rs1] < (int)CURRENT_STATE.REGS[Rs2]) ? 1 : 0;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SLTU (int Rd, int Rs1, int Rs2, int Funct3) {
  printf("SLTU: Rd[%i]  Rs1[%i] = %i,  Rs2[%i] = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], Rs2, CURRENT_STATE.REGS[Rs2]);
  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = (CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2]) ? 1 : 0;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int XOR (int Rd, int Rs1, int Rs2, int Funct3) {
  printf("XOR: Rd[%i]  Rs1[%i] = %i,  Rs2[%i] = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], Rs2, CURRENT_STATE.REGS[Rs2]);
  int cur = CURRENT_STATE.REGS[Rs1] ^ CURRENT_STATE.REGS[Rs2];
  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SRL (int Rd, int Rs1, int Rs2, int Funct3) {
  printf("SRL: Rd[%i]  Rs1[%i] = %i,  Rs2[%i] = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], Rs2, CURRENT_STATE.REGS[Rs2]);
  int cur = CURRENT_STATE.REGS[Rs1] >> CURRENT_STATE.REGS[Rs2];
  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SRA (int Rd, int Rs1, int Rs2, int Funct3) {
  printf("SRA: Rd[%i]  Rs1[%i] = %i,  Rs2[%i] = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], Rs2, CURRENT_STATE.REGS[Rs2]);
  int shift = CURRENT_STATE.REGS[Rs2] & 0x0000003f;
  int reg = CURRENT_STATE.REGS[Rs1];
  int cur = reg >> shift;
  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int OR (int Rd, int Rs1, int Rs2, int Funct3) {
  printf("OR: Rd[%i]  Rs1[%i] = %i,  Rs2[%i] = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], Rs2, CURRENT_STATE.REGS[Rs2]);
  int cur = CURRENT_STATE.REGS[Rs1] | CURRENT_STATE.REGS[Rs2];
  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int AND (int Rd, int Rs1, int Rs2, int Funct3) {
  printf("AND: Rd[%i]  Rs1[%i] = %i,  Rs2[%i] = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], Rs2, CURRENT_STATE.REGS[Rs2]);
  int cur = CURRENT_STATE.REGS[Rs1] & CURRENT_STATE.REGS[Rs2];
  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}
// R instruction    R instruction   R instruction




// I Instructions   I Instructions    I Instructions
int ADDI (int Rd, int Rs1, int Imm, int Funct3) {
  printf("ADDI: Rd[%i]  Rs1[%i] = %i,  Imm = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], Imm);
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm,12);
  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

/*
int LB (int Rd, int Rs1, int Imm, int Funct3){
  printf("LB: Rd[%i]  Rs1[%i] = %i   imm = %i", Rd, Rs1, CURRENT_STATE.REGS[Rs1], SIGNEXT(Imm, 12));
  uint32_t address = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm, 12);
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
  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = SIGNEXT(byte, 7);
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}*/

int LB (int Rd, int Rs1, int Imm, int Funct3){
  printf("LB: Rd[%i]  Rs1[%i] = %i   imm = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], SIGNEXT(Imm, 12));
  uint32_t address = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm, 12);
  uint32_t word = mem_read_32(address);
  uint8_t byte = word & 0xFF;

  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = SIGNEXT(byte, 8);
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int LH (int Rd, int Rs1, int Imm, int Funct3){
  printf("LH: Rd[%i]  Rs1[%i] = %i   imm = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], SIGNEXT(Imm, 12));
  uint32_t address = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm, 12);
  uint32_t word = mem_read_32(address);
  uint16_t halfword = word & 0xffff;;

  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = SIGNEXT(halfword, 16);
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int LW (int Rd, int Rs1, int Imm, int Funct3){
  printf("LH: Rd[%i]  Rs1[%i] = %i   imm = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], SIGNEXT(Imm, 12));
  uint32_t address = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm, 12);
  uint32_t word = mem_read_32(address);
  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = word;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int LBU (int Rd, int Rs1, int Imm, int Funct3){
  printf("LBU: Rd[%i]  Rs1[%i] = %i   imm = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], SIGNEXT(Imm, 12));
  uint32_t address = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm, 12);
  uint32_t word = mem_read_32(address);
  uint8_t byte = word & 0xFF;

  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = byte & 0x000000FF;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int LHU (int Rd, int Rs1, int Imm, int Funct3){
  printf("LHU: Rd[%i]  Rs1[%i] = %i   imm = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], SIGNEXT(Imm, 12));
  uint32_t address = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm, 12);
  uint32_t word = mem_read_32(address);
  uint16_t halfword = word & 0xffff;;

  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = word & 0x0000FFFF;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SLLI (int Rd, int Rs1, int Imm, int Funct3){
  printf("SLLI: Rd[%i]  Rs1[%i] = %i,  Imm = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], Imm);
  int cur = CURRENT_STATE.REGS[Rs1] << (SIGNEXT(Imm, 12) & 0x3F);
  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SLTI (int Rd, int Rs1, int Imm, int Funct3){
  printf("SLTI: Rd[%i]  Rs1[%i] = %i,  Imm = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], SIGNEXT(Imm, 12));
  int reg = CURRENT_STATE.REGS[Rs1];
  int imm_new = SIGNEXT(Imm, 12);
  int cur = (reg < imm_new) ? 1 : 0;
  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SLTIU (int Rd, int Rs1, int Imm, int Funct3){
  printf("SLTIU: Rd[%i]  Rs1[%i] = %i,  Imm = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], Imm);
  int cur = (CURRENT_STATE.REGS[Rs1] < SIGNEXT(Imm, 12)) ? 1 : 0;
  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int XORI (int Rd, int Rs1, int Imm, int Funct3){
  printf("XORI: Rd[%i]  Rs1[%i] = %i,  Imm = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], Imm);
  int cur = (CURRENT_STATE.REGS[Rs1] ^ SIGNEXT(Imm, 12));
  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SRLI (int Rd, int Rs1, int Imm, int Funct3){
  printf("SRLI: Rd[%i]  Rs1[%i] = %i,  Imm = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], Imm);
  int cur = CURRENT_STATE.REGS[Rs1] >> (Imm & 0x0000003F);
  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SRAI (int Rd, int Rs1, int Imm, int Funct3){
  printf("SRAI: Rd[%i]  Rs1[%i] = %i,  Imm = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], Imm);
  int reg = CURRENT_STATE.REGS[Rs1];
  int cur = reg >> (Imm & 0x0000003F);

  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int ORI (int Rd, int Rs1, int Imm, int Funct3){
  printf("ORI: Rd[%i]  Rs1[%i] = %i,  Imm = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], Imm);
  int cur = CURRENT_STATE.REGS[Rs1] | SIGNEXT(Imm, 12);
  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int ANDI (int Rd, int Rs1, int Imm, int Funct3){
  printf("ANDI: Rd[%i]  Rs1[%i] = %i,  Imm = %i\n", Rd, Rs1, CURRENT_STATE.REGS[Rs1], Imm);
  int cur = CURRENT_STATE.REGS[Rs1] & SIGNEXT(Imm, 12);
  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}
// I Instructions   I Instructions    I Instructions




// U Instruction    U Instruction   U Instruction
int AUIPC (int Rd, int Imm) {
  printf("AUIPC: Rd[%i], Imm = %i\n", Rd, Imm);
  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = CURRENT_STATE.PC + (Imm << 12);
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int LUI (int Rd, int Imm) {
  printf("LUI: Rd[%i], Imm = %i\n", Rd, Imm);
  if (Rd != 0 || !(BLOCK_ZERO_WRITE))
    NEXT_STATE.REGS[Rd] = (Imm << 12);
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}
// U Instruction    U Instruction   U Instruction




// S Instruction    S Instruction   S Instruction
/*
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
}*/

int SB (int Rs1, int Rs2, int Imm, int Funct3){
  printf("SB: Rs1[%i] = %i,  Rs2[%i] = %i   imm = %i\n", Rs1,
         CURRENT_STATE.REGS[Rs1], Rs2, CURRENT_STATE.REGS[Rs2], SIGNEXT(Imm, 12));
  uint32_t address = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm, 12);
  uint32_t word = mem_read_32(address);
  uint8_t byte = CURRENT_STATE.REGS[Rs2] & 0x000000FF;
  word = (word & 0xFFFFFF00) | byte;

  mem_write_32(address, word);
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
}

int SH (int Rs1, int Rs2, int Imm, int Funct3) {
  printf("SH: Rs1[%i] = %i,  Rs2[%i] = %i   imm = %i\n", Rs1,
         CURRENT_STATE.REGS[Rs1], Rs2, CURRENT_STATE.REGS[Rs2], SIGNEXT(Imm, 12));
  uint32_t address = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm, 12);
  uint32_t word = mem_read_32(address);
  uint16_t half = CURRENT_STATE.REGS[Rs2] & 0x0000FFFF;
  word = (word & 0xFFFF0000) | half;

  mem_write_32(address, word);
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
} 

int SW (int Rs1, int Rs2, int Imm, int Funct3) {
  printf("SW: Rs1[%i] = %i,  Rs2[%i] = %i   imm = %i\n", Rs1,
         CURRENT_STATE.REGS[Rs1], Rs2, CURRENT_STATE.REGS[Rs2], SIGNEXT(Imm, 12));

  uint32_t address = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm, 12);
  uint32_t word = mem_read_32(address);
  word = CURRENT_STATE.REGS[Rs2] & 0xFFFFFFFF;
  word = (word & 0xFFFFFFFF) | word;

  mem_write_32(address, word);
  NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  return 0;
} 
// S Instruction    S Instruction   S Instruction




// B instructions   B instructions    B instructions
int BEQ (int Rs1, int Rs2, int Imm, int Funct3) {
  printf("BEQ: Rs1[%i] = %i,  Rs2[%i] = %i\n", Rs1, CURRENT_STATE.REGS[Rs1], Rs2, CURRENT_STATE.REGS[Rs2]);
  if (CURRENT_STATE.REGS[Rs1] == CURRENT_STATE.REGS[Rs2]) {
    NEXT_STATE.PC = (CURRENT_STATE.PC) + (SIGNEXT(Imm,13));
  } else {
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  }
  return 0;
} 

int BNE (int Rs1, int Rs2, int Imm, int Funct3) {
  printf("BNE: Rs1[%i] = %i,  Rs2[%i] = %i\n", Rs1, CURRENT_STATE.REGS[Rs1], Rs2, CURRENT_STATE.REGS[Rs2]);
  int cur = 0;
  if (CURRENT_STATE.REGS[Rs1] != CURRENT_STATE.REGS[Rs2]) {
    NEXT_STATE.PC = (CURRENT_STATE.PC) + SIGNEXT(Imm,13);
  } else {
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  }
  return 0;
}

int BLT (int Rs1, int Rs2, int Imm, int Funct3) {
  printf("BLT: Rs1[%i] = %i,  Rs2[%i] = %i\n", Rs1, CURRENT_STATE.REGS[Rs1], Rs2, CURRENT_STATE.REGS[Rs2]);
  int reg1 = CURRENT_STATE.REGS[Rs1];
  int reg2 = CURRENT_STATE.REGS[Rs2];
  if (reg1 < reg2) {
    NEXT_STATE.PC = (CURRENT_STATE.PC) + (SIGNEXT(Imm,13));
  } else {
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  }
  return 0;
}

int BGE (int Rs1, int Rs2, int Imm, int Funct3) {
  printf("BGE: Rs1[%i] = %i,  Rs2[%i] = %i\n", Rs1, CURRENT_STATE.REGS[Rs1], Rs2, CURRENT_STATE.REGS[Rs2]);
  int reg1 = CURRENT_STATE.REGS[Rs1];
  int reg2 = CURRENT_STATE.REGS[Rs2];
  if (reg1 >= reg2) {
    NEXT_STATE.PC = (CURRENT_STATE.PC) + (SIGNEXT(Imm,13));
  } else {
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  }
  return 0;
} 

int BLTU (int Rs1, int Rs2, int Imm, int Funct3) {
  printf("BLTU: Rs1[%i] = %i,  Rs2[%i] = %i\n", Rs1, CURRENT_STATE.REGS[Rs1], Rs2, CURRENT_STATE.REGS[Rs2]);
  if (CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2]) {
    NEXT_STATE.PC = (CURRENT_STATE.PC) + (SIGNEXT(Imm,13));
  } else {
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
  }
  return 0;
} 

int BGEU (int Rs1, int Rs2, int Imm, int Funct3) {
  printf("BGEU: Rs1[%i] = %i,  Rs2[%i] = %i\n", Rs1, CURRENT_STATE.REGS[Rs1], Rs2, CURRENT_STATE.REGS[Rs2]);
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
    NEXT_STATE.PC = CURRENT_STATE.REGS[Rs1] + (SIGNEXT(Imm,21));
    NEXT_STATE.REGS[Rd] = CURRENT_STATE.PC + 4;
    return 0;
} 
// I instruction I instruction I instruction



// J instruction J instruction J instruction
int JAL (int Rd, int imm) {
    NEXT_STATE.PC = CURRENT_STATE.PC + (SIGNEXT(imm,21));
    NEXT_STATE.REGS[Rd] = CURRENT_STATE.PC + 4;
    return 0;
} 
// J instruction J instruction J instruction



// ECALL
int ECALL (char* i_){
  
  return 0;
} 

#endif
