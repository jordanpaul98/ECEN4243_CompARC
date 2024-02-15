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
// #include "shell.c"
#include "isa.h"


char *byte_to_binary(int x) {

  static char b[9];
  b[0] = '\0';

  int z;
  for (z = 128; z > 0; z >>= 1) {
    strcat(b, ((x & z) == z) ? "1" : "0");
  }

  return b;
}

char *byte_to_binary32(int x) {

  static char b[33];
  b[0] = '\0';

  unsigned int z;
  for (z = 2147483648; z > 0; z >>= 1) {
    strcat(b, ((x & z) == z) ? "1" : "0");
  }

  return b;
}

int bchar_to_int(char* rsa) {

  int i = 0;
  int result = 0;
  int t = 0;
  while(rsa[i] != '\0'){ i++; }
  while(i>0){
      --i;
      result += (rsa[i] - '0')<<t;
      // printf("%d\n", result);
      t++;
    }
  return result;
}

int r_process(char* i_) {
  char d_opcode[8]; d_opcode[7] = '\0'; // Opcode variable + null pointer
  for (int i = 0; i < 7; i++) {         // 7 bits for opcode
    d_opcode[i] = i_[31-6+i];           // assignment
  }

  char rd[6]; rd[5] = '\0';             // Rd variable
  for(int i = 0; i < 5; i++) {
    rd[i] = i_[31-11+i];                // assigning bits 11-7 to 0-4
  }
  int Rd = bchar_to_int(rd);            // convert rd to int

  char funct3[4]; funct3[3] = '\0';     // Funct3 variable
  for(int i = 0; i < 3; i++) {
    funct3[i] = i_[31-14+i];            // assigning bits 14-12 to 0-2
  }
  int Funct3 = bchar_to_int(funct3);    // convert funct3 to int

  char rs1[6]; rs1[5] = '\0';		        // Rs1 variable
  for(int i = 0; i < 5; i++) {
    rs1[i] = i_[31-19+i];               // assigning bits 19-15 to 0-4
  }  
  int Rs1 = bchar_to_int(rs1);          // convert rs1 to int

  char rs2[6]; rs2[5] = '\0';           // Rs2 variable
  for(int i = 0; i < 5; i++) {
    rs2[i] = i_[31-24+i];               // assigning bits 24-20 to 0-4
  }
  int Rs2 = bchar_to_int(rs2);		      // convert rs2 to int

  char funct7[8]; funct7[7] = '\0';     // Funct7 variable
  for(int i = 0; i < 7; i++){
    funct7[i] = i_[31-31+i];            // assigning bits 31-25 to 0-6
  }
  int Funct7 = bchar_to_int(funct7);    // convert funct7 to int
  
  printf ("Opcode = %s\n Rs1 = %d\n Rs2 = %d\n Rd = %d\n Funct3 = %d\n\n", d_opcode, Rs1, Rs2, Rd, Funct3);

  if(!strcmp(d_opcode,"0110011")) {
    ADD(Rd, Rs1, Rs2, Funct3);
    switch(Funct3){
      case 0x0:
        ((Funct7 & 0x20) == 0x20) ? SUB(Rd, Rs1, Rs2, Funct3) : ADD(Rd, Rs1, Rs2, Funct3);
        break;
      case 0x1:
        SLL(Rd, Rs1, Rs2, Funct3);
        break;
      case 0x2:
        SLT(Rd, Rs1, Rs2, Funct3);
        break;
      case 0x3:
        SLTU(Rd, Rs1, Rs2, Funct3);
        break;
      case 0x4:
        XOR(Rd, Rs1, Rs2, Funct3);
        break;
      case 0x5:
        ((Funct7 & 0x20) == 0x20) ? SRA(Rd, Rs1, Rs2, Funct3) : SRL(Rd, Rs1, Rs2, Funct3);
        break;
      case 0x6:
        OR(Rd, Rs1, Rs2, Funct3);
        break;
      case 0x7:
        AND(Rd, Rs1, Rs2, Funct3);
        break;
    }
  }
  return 1;	
}

int i_process(char* i_) {
  char d_opcode[8]; d_opcode[7] = '\0'; // Opcode variable + null pointer
  for (int i = 0; i < 7; i++) {         // 7 bits for opcode
    d_opcode[i] = i_[31-6+i];           // assignment
  }

  char rd[6]; rd[5] = '\0';             // Rd variable
  for (int i = 0; i < 5; i++) {
    rd[i] = i_[31-11+i];                // assigning bits 11-7 to 0-4
  }
  int Rd = bchar_to_int(rd);            // convert rd to int

  char funct3[4]; funct3[3] = '\0';     // Funct3 variable
  for(int i = 0; i < 3; i++) {
    funct3[i] = i_[31-14+i];            // assigning bits 14-12 to 0-2
  }
  int Funct3 = bchar_to_int(funct3);    // convert funct3 to int

  char rs1[6]; rs1[5] = '\0';           // Rs1 variable
  for (int i = 0; i < 5; i++) {
    rs1[i] = i_[31-19+i];               // assigning bits 19-15 to 0-4
  }
  int Rs1 = bchar_to_int(rs1);          // convert rs1 to int

  char imm[13]; imm[12] = '\0';         // Imm variable
  for(int i = 0; i < 12; i++) {
    imm[i] = i_[31-31+i];               // assigning bits 31-20 to 0-11
  }
  int Imm = bchar_to_int(imm);          // convert imm to int

  printf ("Opcode = %s\n Rs1 = %d\n Imm = %d\n Rd = %d\n Funct3 = %d\n\n", d_opcode, Rs1, Imm, Rd, Funct3);

  if(!strcmp(d_opcode,"0000011")) {
    switch(Funct3){
      case 0x0:
          LB  (Rd, Rs1, Imm, Funct3);
          break;
      case 0x1:
          LH  (Rd, Rs1, Imm, Funct3);
          break;
      case 0x2:
          LW  (Rd, Rs1, Imm, Funct3);
          break;
      case 0x4:
          LBU (Rd, Rs1, Imm, Funct3);
          break;
      case 0x5:
          LHU (Rd, Rs1, Imm, Funct3);
          break;
    }
    return 0;
  }else if(!strcmp(d_opcode, "0010011")){
    switch(Funct3){
      case 0x0: 
          ADDI  (Rd, Rs1, Imm, Funct3);
          break;
      case 0x1:
          SLLI  (Rd, Rs1, Imm, Funct3);
          break;
      case 0x2: 
          SLTI  (Rd, Rs1, Imm, Funct3);
          break;
      case 0x3:
          SLTIU (Rd, Rs1, Imm, Funct3);
          break;
      case 0x4:
          XORI  (Rd, Rs1, Imm, Funct3);
          break;
      case 0x5:
          // funct7 000000* for SRLI, 010000* for SRAI
          ((Imm & 0x400) == 0x400) ? SRAI(Rd, Rs1, Imm, Funct3) : SRLI(Rd, Rs1, Imm, Funct3);
          break;
      case 0x6:
          ORI   (Rd, Rs1, Imm, Funct3);
          break;
      case 0x7:
          ANDI  (Rd, Rs1, Imm, Funct3);
          break;
    }
  } else if (!strcmp(d_opcode, "1100111")) {
    JALR  (Rd, Rs1, Imm);
  }
  return 1;	
}

// This function execute B type instruction 
int b_process(char* i_) {
  char d_opcode[8]; d_opcode[7] = '\0'; // Opcode variable + null pointer
  for (int i = 0; i < 7; i++) {         // 7 bits for opcode
    d_opcode[i] = i_[31-6+i];           // assignment
  }
  
  char funct3[4]; funct3[3] = '\0';     // Funct3 variable
  for(int i = 0; i < 3; i++) {
    funct3[i] = i_[31-14+i];            // assigning bits 14-12 to 0-2
  }
  int Funct3 = bchar_to_int(funct3);    // convert funct3 to int

  char rs1[6]; rs1[5] = '\0';           // Rs1 variable
  for(int i = 0; i < 5; i++) {
    rs1[i] = i_[31-19+i];               // assigning bits 19-15 to 0-4
  }
  int Rs1 = bchar_to_int(rs1);          // convert rs1 to int

  char rs2[6]; rs2[5] = '\0';		        // Rs2 variable
  for(int i = 0; i < 5; i++) {
    rs2[i] = i_[31-24+i];               // assigning bits 24-20 to 0-4
  }
  int Rs2 = bchar_to_int(rs2);          // convert rs2 to int   

  char imm[14]; imm[13] = '\0';         // Imm variable
  imm[12] = '0';                        // Assign trailing 0
  imm[0] = i_[31-31];                   // Assign bit 31 to 0
  for (int i = 0; i < 6; i++) {         
    imm[2+i] = i_[31-30+i];             // Assigning bits 30-25 to 2-7
  } 
  for (int i = 0; i < 4; i++) {
    imm[8+i] = i_[31-11+i];             // Assigning bits 11-8 to 8-11
  }
  imm[1] = i_[31-7];                    // Assign bit 7 to 1
  int Imm = bchar_to_int(imm);          // convert imm to int

  printf("Opcode = %s\n Rs1 = %d\n Rs2 = %d\n Imm = %d\n Funct3 = %d\n\n", d_opcode, Rs1, Rs2, Imm, Funct3);

  if(!strcmp(d_opcode,"1100011")) {
    switch(Funct3){
      case 0x0:
        BEQ(Rs1, Rs2, Imm, Funct3);
        break;
      case 0x1:
        BNE(Rs1, Rs2, Imm, Funct3);
        break;
      case 0x4:
        BLT(Rs1, Rs2, Imm, Funct3);
        break;
      case 0x5:
        BGE(Rs1, Rs2, Imm, Funct3);
        break;
      case 0x6:
        BLTU(Rs1, Rs2, Imm, Funct3);
        break;
      case 0x7:
        BGEU(Rs1, Rs2, Imm, Funct3);
        break;
    }
  }	    
  return 1;
}

// This function executes S type instructions
int s_process(char* i_) {
  char d_opcode[8]; d_opcode[7] = '\0'; // Opcode variable + null pointer
  for (int i = 0; i < 7; i++) {         // 7 bits for opcode
    d_opcode[i] = i_[31-6+i];           // assignment
  }

  char funct3[4]; funct3[3] = '\0';     // Funct3 variable
  for(int i = 0; i < 3; i++) {
    funct3[i] = i_[31-14+i];            // assigning bits 14-12 to 0-2
  }
  int Funct3 = bchar_to_int(funct3);    // convert funct3 to int

  char rs1[6]; rs1[5] = '\0';           // Rs1 variable
  for(int i = 0; i < 5; i++) {
    rs1[i] = i_[31-19+i];               // assigning bits 19-15 to 0-4
  }
  int Rs1 = bchar_to_int(rs1);          // convert rs1 to int

  char rs2[6]; rs2[5] = '\0';		        // Rs2 variable
  for(int i = 0; i < 5; i++) {
    rs2[i] = i_[31-24+i];               // assigning bits 24-20 to 0-4
  }
  int Rs2 = bchar_to_int(rs2);          // convert rs2 to int

  char imm[13]; imm[12] = '\0';         // Imm variable
  for (int i = 0; i < 5; i++) {  
    imm[7+i] = i_[31-11+i];             // assigning bits 11-7 to 7-11
  }
  for (int i = 0; i < 7; i++) {  
    imm[i] = i_[31-31+i];               // assigning bits 31-25 to 0-6
  }
  int Imm = bchar_to_int(imm);          // convert imm to int
  
  printf("Opcode = %s\n Rs1 = %d\n Rs2 = %d\n Imm = %d\n Funct3 = %d\n\n", d_opcode, Rs1, Rs2, Imm, Funct3);

  if(!strcmp(d_opcode,"0100011")) {
    switch(Funct3){
      case 0x0:
        SB(Rs1, Rs2, Imm, Funct3);
        break;
      case 0x1:
        SH(Rs1, Rs2, Imm, Funct3);
        break;
      case 0x4:
        SW(Rs1, Rs2, Imm, Funct3);
        break;
    }
  }	    
  return 1;
}

// This function executes J type instructions
int j_process(char* i_) {
  char d_opcode[8]; d_opcode[7] = '\0'; // Opcode variable + null pointer
  for (int i = 0; i < 7; i++) {         // 7 bits for opcode
    d_opcode[i] = i_[31-6+i];           // assignment
  }
   
  char rd[6]; rd[5] = '\0';             // Rd variable
  for(int i = 0; i < 5; i++) {          // Assigning bits to rd
    rd[i] = i_[31-11+i];
  }
  int Rd = bchar_to_int(rd);            // Convert rd to int

  char imm[22]; imm[21] = '\0';         // Imm variable
  imm[20] = '0';                        // Assign trailing 0
  imm[0] = i_[31-12-20+1];              // Assign bit 31 to 0
  for (int i = 0; i < 10; i++) {        
    imm[10+i] = i_[31-12-19+1+i];       // Assigning bits 30-21 to 10-19
  }
  imm[9] = i_[31-12-9+1];               // Assign bit 20 to 9
  for (int i = 0; i < 8; i++) {         
    imm[1+i] = i_[31-12-8+i];           // Assigning bits 19-12 to 1-8
  }
  int Imm = bchar_to_int(imm);          // Convert imm to int

  printf ("Opcode = %s\n Imm = %d\n Rd = %d\n\n", d_opcode, Imm, Rd);

  if(!strcmp(d_opcode,"1101111")) {
    JAL(Rd, Imm);
  }
  return 1;
}

// This function executes U type instructions
int u_process(char* i_) {
  char d_opcode[8]; d_opcode[7] = '\0'; // Opcode variable + null pointer
  for (int i = 0; i < 7; i++) {         // 7 bits for opcode
    d_opcode[i] = i_[31-6+i];           // assignment
  } 
   
  char rd[6]; rd[5] = '\0';             // Rd variable
  for(int i = 0; i < 5; i++) {          // Assigning bits to rd
    rd[i] = i_[31-11+i];
  }
  int Rd = bchar_to_int(rd);            // Convert rd to int

  char imm[33]; imm[32] = '\0';         // Imm variable
  for (int i = 0; i < 20; i++) {        // Assigning bits to imm
    imm[i] = i_[i];
  }
  for (int i = 0; i < 12; i++) {        // Assigning trailing 0s to imm
    imm[31 - 11 + i] = '0';
  }
  int Imm = bchar_to_int(imm);          // Convert imm to int
  
  printf ("Opcode = %s\n Imm = %d\n Rd = %d\n\n", d_opcode, Imm, Rd);
  
  if(!strcmp(d_opcode,"0010111")) {
    AUIPC(Rd, Imm);
  } else if (!strcmp(d_opcode,"0110111")) {
    LUI(Rd, Imm);
  }
  return 1;
}

int interruption_process(char* i_) {
  ECALL(i_);
  RUN_BIT = 0;
  return 0;
}

// This function decode the instruction and update 
// CPU_State (NEXT_STATE)
int decode_and_execute(char* i_) {
  if(((i_[25] == '0') && (i_[26] == '0') &&
     (i_[27] == '1') && (i_[28] == '0') &&
     (i_[29] == '0') && (i_[30] == '1') && 
     (i_[31] == '1')) || ((i_[25] == '1') &&
     (i_[26] == '1') && (i_[27] == '0') &&
     (i_[28] == '0') && (i_[29] == '1') &&
     (i_[30] == '1') && (i_[31] == '1'))) {
    printf("- This is an I Type Instruction. \n");
    i_process(i_);
  } else if((i_[25] == '0') && (i_[26] == '1') &&
     (i_[27] == '1') && (i_[28] == '0') &&
     (i_[29] == '0') && (i_[30] == '1') && (i_[31] == '1')) {
    printf("- This is an R Type Instruction. \n");
    r_process(i_);
  } else if((i_[25] == '1') && (i_[26] == '1') &&
     (i_[27] == '0') && (i_[28] == '0') &&
     (i_[29] == '0') && (i_[30] == '1') && (i_[31] == '1')) {
    printf("- This is a B Type Instruction. \n");
    b_process(i_);
  } else if((i_[25] == '0') && (i_[26] == '1') &&
     (i_[27] == '0') && (i_[28] == '0') &&
     (i_[29] == '0') && (i_[30] == '1') && (i_[31] == '1')) {
    printf("- This is a S Type Instruction. \n");
    s_process(i_);
  } else if((i_[25] == '1') && (i_[26] == '1') &&
     (i_[27] == '0') && (i_[28] == '1') &&
     (i_[29] == '1') && (i_[30] == '1') && (i_[31] == '1')) {
    printf("- This is a J Type Instruction. \n");
    j_process(i_);
  } else if(((i_[25] == '0') && (i_[26] == '0') &&
     (i_[27] == '1') && (i_[28] == '0') &&
     (i_[29] == '1') && (i_[30] == '1') && 
     (i_[31] == '1')) || ((i_[25] == '0') && 
     (i_[26] == '1') && (i_[27] == '1') &&
     (i_[28] == '0') && (i_[29] == '1') &&
     (i_[30] == '1') && (i_[31] == '1'))){
    printf("- This is a U Type Instruction. \n");
    u_process(i_);
  } else if((i_[25] == '1') && (i_[26] == '1') &&
     (i_[27] == '1') && (i_[28] == '0') &&
     (i_[29] == '0') && (i_[30] == '1') && (i_[31] == '1')) {
    printf("- This is a Software Interruption Instruction. \n");
    interruption_process(i_);
  } else {
    printf("- This is an Invalid Instruction. \n");
    printf("Opcode = %s\n", i_);
  }
  return 0;
}

unsigned int OPCODE (unsigned int i_word) { return ((i_word<<27)>>27); }

// execute one instruction here. You should use CURRENT_STATE and modify
// values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
// access memory.
void process_instruction() {
  unsigned int inst_word = mem_read_32(CURRENT_STATE.PC);
  char *inst = byte_to_binary32(inst_word);
  printf("The instruction is: %x \n", inst_word);
  // printf("33222222222211111111110000000000\n");  // What is the point of these
  // printf("10987654321098765432109876543210\n");  // lines of code?
  printf("---------------------------------------------------\n");
  printf("%s \n", inst_word);
  printf("\n");
  decode_and_execute(inst);
}
