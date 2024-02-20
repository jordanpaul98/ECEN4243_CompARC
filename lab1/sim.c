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

#define ADD_INSTRUCTION     0
#define ADDI_INSTRUCTION    1
#define AND_INSTRUCTION     2
#define ANDI_INSTRUCTION    3
#define AUIPC_INSTRUCTION   4
#define BEQ_INSTRUCTION     5
#define BGE_INSTRUCTION     6
#define BGEU_INSTRUCTION    7
#define BLT_INSTRUCTION     8
#define BLTU_INSTRUCTION    9
#define BNE_INSTRUCTION     10
#define JAL_INSTRUCTION     11
#define JALR_INSTRUCTION    12
#define LB_INSTRUCTION      13
#define LBU_INSTRUCTION     14
#define LH_INSTRUCTION      15
#define LHU_INSTRUCTION     16
#define LUI_INSTRUCTION     17
#define LW_INSTRUCTION      18
#define OR_INSTRUCTION      19
#define ORI_INSTRUCTION     20
#define SB_INSTRUCTION      21
#define SH_INSTRUCTION      22
#define SLL_INSTRUCTION     23
#define SLLI_INSTRUCTION    24
#define SLT_INSTRUCTION     25
#define SLTI_INSTRUCTION    26
#define SLTIU_INSTRUCTION   27
#define SLTU_INSTRUCTION    28
#define SRA_INSTRUCTION     29
#define SRAI_INSTRUCTION    30
#define SRL_INSTRUCTION     31
#define SRLI_INSTRUCTION    32
#define SUB_INSTRUCTION     33
#define SW_INSTRUCTION      34
#define XOR_INSTRUCTION     35
#define XORI_INSTRUCTION    36
#define ECALL_INSTRUCTION   37

const char* instructions_names[38] = {
  "ADD",  "ADDI", "AND",  "ANDI",  "AUIPC", "BEQ",
  "BGE",  "BGEU", "BLT",  "BLTU",  "BNE",   "JAL",
  "JALR", "LB",   "LBU",  "LH",    "LHU",   "LUI",
  "LW",   "OR",   "ORI",  "SB",    "SH",    "SLL",
  "SLLI", "SLT",  "SLTI", "SLTIU", "SLTU",  "SRA", 
  "SRAI", "SRL",  "SRLI", "SUB",   "SW",    "XOR", 
  "XORI", "ECALL"
  };

int instruction_calls[100];
int total_instruction_calls = 0;

void recordInstruction(int callType){
  instruction_calls[callType]++;
  total_instruction_calls++;
}

void clearRecordedCalls(){
  for (int i = 0; i < 100; i++) { instruction_calls[i] = 0; }
  total_instruction_calls = 0;
}

void printInstructionCallStats(){
  if (total_instruction_calls == 0){
    printf("\n\nNo instructions recorded\n\n");
  }else{
    printf("\n\nRecorded Calls: %i Instruction calls performed\n", total_instruction_calls);
    for (int i = 0; i < 38; i++){
      if (instruction_calls[i] == 0) continue;
      double percentage = 100 * instruction_calls[i] / (double)total_instruction_calls;
      printf("[%s] calls: %i ... %.2f%%\n", instructions_names[i], instruction_calls[i], percentage);
    }
  }
  printf("\n");
}

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

  if (Rd == 0) { printf("Warning: Writing to Zero Register\n"); }

  if(!strcmp(d_opcode,"0110011")) {
    switch(Funct3){
      case 0x0:
        if ((Funct7 & 0x20) == 0x20){
          SUB(Rd, Rs1, Rs2, Funct3);
          recordInstruction(ADD_INSTRUCTION);
        }else{
          ADD(Rd, Rs1, Rs2, Funct3);
          recordInstruction(SUB_INSTRUCTION);
        }
        break;
      case 0x1:
        SLL(Rd, Rs1, Rs2, Funct3);
        recordInstruction(SLL_INSTRUCTION);
        break;
      case 0x2:
        SLT(Rd, Rs1, Rs2, Funct3);
        recordInstruction(SLT_INSTRUCTION);
        break;
      case 0x3:
        SLTU(Rd, Rs1, Rs2, Funct3);
        recordInstruction(SLTU_INSTRUCTION);
        break;
      case 0x4:
        XOR(Rd, Rs1, Rs2, Funct3);
        recordInstruction(XOR_INSTRUCTION);
        break;
      case 0x5:
        if ((Funct7 & 0x20) == 0x20) {
          SRA(Rd, Rs1, Rs2, Funct3);
          recordInstruction(SRA_INSTRUCTION);
        } else {
          SRL(Rd, Rs1, Rs2, Funct3);
          recordInstruction(SRL_INSTRUCTION);
        }
        break;
      case 0x6:
        OR(Rd, Rs1, Rs2, Funct3);
        recordInstruction(OR_INSTRUCTION);
        break;
      case 0x7:
        AND(Rd, Rs1, Rs2, Funct3);
        recordInstruction(AND_INSTRUCTION);
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

  if (Rd == 0) { printf("Warning: Writing to Zero Register\n"); }

  if(!strcmp(d_opcode,"0000011")) {
    switch(Funct3){
      case 0x0:
          LB  (Rd, Rs1, Imm, Funct3);
          recordInstruction(LB_INSTRUCTION);
          break;
      case 0x1:
          LH  (Rd, Rs1, Imm, Funct3);
          recordInstruction(LH_INSTRUCTION);
          break;
      case 0x2:
          LW  (Rd, Rs1, Imm, Funct3);
          recordInstruction(LW_INSTRUCTION);
          break;
      case 0x4:
          LBU (Rd, Rs1, Imm, Funct3);
          recordInstruction(LBU_INSTRUCTION);
          break;
      case 0x5:
          LHU (Rd, Rs1, Imm, Funct3);
          recordInstruction(LHU_INSTRUCTION);
          break;
    }
    return 0;
  }else if(!strcmp(d_opcode, "0010011")){
    switch(Funct3){
      case 0x0: 
          ADDI  (Rd, Rs1, Imm, Funct3);
          recordInstruction(ADDI_INSTRUCTION);
          break;
      case 0x1:
          SLLI  (Rd, Rs1, Imm, Funct3);
          recordInstruction(SLLI_INSTRUCTION);
          break;
      case 0x2: 
          SLTI  (Rd, Rs1, Imm, Funct3);
          recordInstruction(SLTI_INSTRUCTION);
          break;
      case 0x3:
          SLTIU (Rd, Rs1, Imm, Funct3);
          recordInstruction(SLTIU_INSTRUCTION);
          break;
      case 0x4:
          XORI  (Rd, Rs1, Imm, Funct3);
          recordInstruction(XORI_INSTRUCTION);
          break;
      case 0x5:
          // funct7 000000* for SRLI, 010000* for SRAI
          if ((Imm & 0x400) == 0x400){
            SRAI(Rd, Rs1, Imm, Funct3);
            recordInstruction(SRAI_INSTRUCTION);
          } else {
            SRLI(Rd, Rs1, Imm, Funct3);
            recordInstruction(SRLI_INSTRUCTION);
          }
          break;
      case 0x6:
          ORI   (Rd, Rs1, Imm, Funct3);
          recordInstruction(ORI_INSTRUCTION);
          break;
      case 0x7:
          ANDI  (Rd, Rs1, Imm, Funct3);
          recordInstruction(ANDI_INSTRUCTION);
          break;
    }
  } else if (!strcmp(d_opcode, "1100111")) {
    JALR  (Rd, Rs1, Imm);
    recordInstruction(JALR_INSTRUCTION);
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

// 31 30 29 28 27 26 25 11 10 9  8  7  - bit position
// 0  1  2  3  4  5  6  20 21 22 23 24 - array position
// 12 10 9  8  7  6  5  4  3  2  1  11 - imm position
// 0  2  3  4  5  6  7  8  9  10 11 1  - imm array position

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
        recordInstruction(BEQ_INSTRUCTION);
        break;
      case 0x1:
        BNE(Rs1, Rs2, Imm, Funct3);
        recordInstruction(BNE_INSTRUCTION);
        break;
      case 0x4:
        BLT(Rs1, Rs2, Imm, Funct3);
        recordInstruction(BLT_INSTRUCTION);
        break;
      case 0x5:
        BGE(Rs1, Rs2, Imm, Funct3);
        recordInstruction(BGE_INSTRUCTION);
        break;
      case 0x6:
        BLTU(Rs1, Rs2, Imm, Funct3);
        recordInstruction(BLTU_INSTRUCTION);
        break;
      case 0x7:
        BGEU(Rs1, Rs2, Imm, Funct3);
        recordInstruction(BGEU_INSTRUCTION);
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
        recordInstruction(SB_INSTRUCTION);
        break;
      case 0x1:
        SH(Rs1, Rs2, Imm, Funct3);
        recordInstruction(SH_INSTRUCTION);
        break;
      case 0x2:
        SW(Rs1, Rs2, Imm, Funct3);
        recordInstruction(SW_INSTRUCTION);
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
    recordInstruction(JAL_INSTRUCTION);
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

  char imm[21]; imm[20] = '\0';         // Imm variable
  for (int i = 0; i < 20; i++) {        // Assigning bits to imm
    imm[i] = i_[31 - 31 + i];
  }
  int Imm = bchar_to_int(imm);          // Convert imm to int
  
  printf ("Opcode = %s\n Imm = %d\n Rd = %d\n\n", d_opcode, Imm, Rd);

  if (Rd == 0) { printf("Warning: Writing to Zero Register\n"); }
  
  if(!strcmp(d_opcode,"0010111")) {
    AUIPC(Rd, Imm);
    recordInstruction(AUIPC_INSTRUCTION);
  } else if (!strcmp(d_opcode,"0110111")) {
    LUI(Rd, Imm);
    recordInstruction(LUI_INSTRUCTION);
  }
  return 1;
}

int interruption_process(char* i_) {
  ECALL(i_);
  RUN_BIT = 0;
  recordInstruction(ECALL_INSTRUCTION);
  return 0;
}

// This function decode the instruction and update 
// CPU_State (NEXT_STATE)
int decode_and_execute(char* i_) {
    if(((i_[25] == '0') && (i_[26] == '0') && (i_[27] == '1') && (i_[28] == '0') && (i_[29] == '0') && (i_[30] == '1') && (i_[31] == '1')) || 
       ((i_[25] == '1') && (i_[26] == '1') && (i_[27] == '0') && (i_[28] == '0') && (i_[29] == '1') && (i_[30] == '1') && (i_[31] == '1')) ||
       ((i_[25] == '0') && (i_[26] == '0') && (i_[27] == '0') && (i_[28] == '0') && (i_[29] == '0') && (i_[30] == '1') && (i_[31] == '1'))) {
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
  } else if(((i_[25] == '1') && (i_[26] == '1') &&
     (i_[27] == '1') && (i_[28] == '0') &&
     (i_[29] == '0') && (i_[30] == '1') && 
     (i_[31] == '1'))) {
    printf("- This is a Software Interruption Instruction. \n");
    interruption_process(i_);
  } else {
    printf("- This is an Invalid Instruction. \n");
    printf("Opcode = %s\n", i_);
    exit(1);
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
  //printf("%x \n", inst_word);
  printf("\n");
  decode_and_execute(inst);
}
