// riscvsingle.sv

// RISC-V single-cycle processor
// From Section 7.6 of Digital Design & Computer Architecture
// 27 April 2020
// David_Harris@hmc.edu 
// Sarah.Harris@unlv.edu

// run 210
// Expect simulator to print "Simulation succeeded"
// when the value 25 (0x19) is written to address 100 (0x64)

//   Instruction  opcode    funct3    funct7
//   add          0110011   000       0000000
//   sub          0110011   000       0100000
//   and          0110011   111       0000000
//   or           0110011   110       0000000
//   slt          0110011   010       0000000
//   addi         0010011   000       immediate
//   andi         0010011   111       immediate
//   ori          0010011   110       immediate
//   slti         0010011   010       immediate
//   beq          1100011   000       immediate
//   lw	          0000011   010       immediate
//   sw           0100011   010       immediate
//   jal          1101111   immediate immediate

// Add the following to the code:
//  Instruction   opcode    funct3    funct7      Done?
//  auipc         0010111   imm       immediate   Done
//  bge           1100011   101       immediate   Done
//  bgeu          1100011   111       immediate   Done
//  blt           1100011   100       immediate   Done
//  bltu          1100011   110       immediate   Done
//  bne           1100011   001       immediate   Done 
//  jalr          1100111   000       immediate
//  lb            0000011   000       immediate
//  lbu           0000011   100       immediate
//  lh            0000011   001       immediate
//  lhu           0000011   101       immediate
//  lui           0110111   imm       immediate
//  sb            0100011   000       immediate
//  sh            0100011   001       immediate
//  sll           0110011   001       0000000     Done
//  slli          0010011   001       000000*     Done
//  sltiu         0010011   011       immediate   Done
//  sltu          0110011   011       0000000     Done
//  sra           0110011   101       0100000     Done
//  srai          0010011   101       010000**    Done
//  srl           0110011   101       0000000     Done
//  srli          0010011   101       000000*     Done
//  xor           0110011   100       0000000     Done
//  xori          0010011   100       immediate   Done


module testbench();

   logic        clk;
   logic        reset;

   logic [31:0] WriteData;
   logic [31:0] DataAdr;
   logic        MemWrite;

   // instantiate device to be tested
   top dut(clk, reset, WriteData, DataAdr, MemWrite);

   initial
     begin
	string memfilename;
        // memfilename = {"riscvtest/riscvtest.memfile"};
	    // memfilename = {"riscvtest/fib.memfile"};
		
		// memfilename = {"testing/add.memfile"};	 // - passed	- still works
		// memfilename = {"testing/addi.memfile"};   // - passed	- still works
		// memfilename = {"testing/and.memfile"};	 // - passed	- still works
		// memfilename = {"testing/andi.memfile"};	 // - passed	- still works
		// memfilename = {"testing/auipc.memfile"};	 // - unsure ??
		// memfilename = {"testing/beq.memfile"};	 // - passed	- still works
		// memfilename = {"testing/bge.memfile"};	 // - passed	- still works
		// memfilename = {"testing/bgeu.memfile"};	 // - passed - created a 33 bit carried, sub b from a and checked the 33rd bit for carried
		// memfilename = {"testing/blt.memfile"};	 // - passed	- still works
		// memfilename = {"testing/bltu.memfile"};	 // - passed	- still works
		// memfilename = {"testing/bne.memfile"};	 // - passed	- still works
		// memfilename = {"testing/jal.memfile"};	 // - passed	- worked after implement srcAmux -> RegA mux PC
		// memfilename = {"testing/jalr.memfile"};	 // - passed	- JALR is I-type 
		// memfilename = {"testing/lb.memfile"};	 // - confirmed with sb
		// memfilename = {"testing/lbu.memfile"};	 // - passed
		// memfilename = {"testing/lh.memfile"};	 // - confirmed with sh
		// memfilename = {"testing/lhu.memfile"};	 // - passed
		// memfilename = {"testing/lui.memfile"};	 // - passed - needs srai (fixed) works
		// memfilename = {"testing/lw.memfile"};	 // - okay		- confirmed with sw.memfile
		// memfilename = {"testing/or.memfile"};	 // - passed	- works
		// memfilename = {"testing/ori.memfile"};	 // - passed
		// memfilename = {"testing/sb.memfile"};	 // - passed - see note for sh
		// memfilename = {"testing/sh.memfile"};	 // - passed: -> NOTE: imem and dmem are only local to that module
		// memfilename = {"testing/sll.memfile"};	 // - passed - had to add unsigned to b and make it 5 bits
		 memfilename = {"testing/slli.memfile"};	 // - passed
		// memfilename = {"testing/slt.memfile"};	 // - passed	- works
		// memfilename = {"testing/slti.memfile"};	 // - passed	- works
		// memfilename = {"testing/sltiu.memfile"};	 // - passed	- works
		// memfilename = {"testing/sltu.memfile"};	 // - passed	- works
		// memfilename = {"testing/sra.memfile"};	 // - passed - had to make a signed - b only 5 bits
		// memfilename = {"testing/srai.memfile"};	 // - passed - had to redo aludec default 3'b101 to if funct7b5
		// memfilename = {"testing/srl.memfile"};	 // - passed  - had to add unsigned to b and make it  5 bits
		// memfilename = {"testing/srli.memfile"};	 // - passed	- works
		// memfilename = {"testing/sub.memfile"};	 // - passed	- works
		// memfilename = {"testing/sw.memfile"};	 // - passed	
		// memfilename = {"testing/xor.memfile"};	 // - passed	- works
		// memfilename = {"testing/xori.memfile"};	 // - passed	- works
		// memfilename = {"testing/ecall.memfile"};	 // - works
		
        $readmemh(memfilename, dut.imem.RAM);
		$readmemh(memfilename, dut.dmem.RAM);
     end

   
   // initialize test
   initial
     begin
	reset <= 1; # 22; reset <= 0;
     end

   // generate clock to sequence tests
   always
     begin
	clk <= 1; # 5; clk <= 0; # 5;
     end

   // check results
   always @(negedge clk)
     begin
		if(MemWrite) begin
			   //if(DataAdr === 100 & WriteData === 25) begin
				//  $display("Simulation succeeded");
				//  $stop;
			   //end else if (DataAdr !== 96) begin
				//  $display("Simulation failed");
				//  $stop;
			   //end
		end
     end
endmodule // testbench

// ==========================================================================================
//
//	top		top		top		top		top		top		top		top		top		top		top								
//
// ==========================================================================================

module top (input  logic        clk, reset,
	    output logic [31:0] WriteData, DataAdr,
	    output logic 	MemWrite);
   
   logic [31:0] 		PC, Instr, ReadData;
   
   // instantiate processor and memories
   riscvsingle rv32single (clk,
						   reset,
						   PC,
						   Instr,
						   MemWrite,
						   DataAdr,
						   WriteData,
						   ReadData);
						   
   imem imem (PC, Instr);
   // dont know if i should do this but passing funct3 to dmen, similiar to Wally
   dmem dmem (clk, MemWrite, DataAdr, WriteData, Instr[14:12], ReadData);
   
endmodule // top

// ==========================================================================================
//
//	riscvsingle		riscvsingle		riscvsingle		riscvsingle		riscvsingle		
//
// ==========================================================================================

module riscvsingle (input  logic  		clk, reset,
				    output logic [31:0] PC,
		            input  logic [31:0] Instr,
		            output logic 		MemWrite,
					output logic [31:0] ALUResult, WriteData,
					input  logic [31:0] ReadData);
   
   logic 			    RegWrite, Jump;
   logic [1:0]          ALUSrc;
   logic				Zero, Negative, Carry, Overflow;
   logic [1:0] 			ResultSrc;
   logic [2:0]          ImmSrc;
   logic [3:0] 		    ALUControl;
   
   controller c (Instr[6:0], Instr[14:12], Instr[30],
				 Zero, Negative, Carry, Overflow,
				 ResultSrc, MemWrite, PCSrc,
				 ALUSrc, RegWrite, Jump,
				 ImmSrc, ALUControl);
		 
   datapath dp (clk, reset, ResultSrc, PCSrc, Jump,
				ALUSrc, RegWrite,
				ImmSrc, ALUControl,
				Zero, Negative, Carry, Overflow,
				PC,  Instr,
				ALUResult, WriteData, ReadData);
   
endmodule // riscvsingle

// ==========================================================================================
//
//	controller		controller		controller		controller		controller		controller		
//
// ==========================================================================================

module controller (input  logic [6:0] op,
		   input  logic [2:0] 	funct3,
		   input  logic       	funct7b5,
		   input  logic       	Zero, Negative, Carry, Overflow,
		   output logic [1:0] 	ResultSrc,
		   output logic       	MemWrite,
		   output logic       	PCSrc,
		   output  logic [1:0]  ALUSrc,
		   output logic       	RegWrite, Jump,
		   output logic [2:0] 	ImmSrc,
		   output logic [3:0] 	ALUControl);
   
   logic [1:0] 			  ALUOp;
   logic 			      Branch, BranchTaken;
   
   maindec md (op, ResultSrc, MemWrite, Branch,
	       ALUSrc, RegWrite, Jump, ImmSrc, ALUOp);
   aludec ad (op[5], funct3, funct7b5, ALUOp, ALUControl);
   
   
   // lecture 13 slide 17
   // Text.07 pg 14
   always_comb
	   case (funct3)
			3'b000:  assign BranchTaken = Zero; 					// beq =
			3'b001:  assign BranchTaken = Zero; 					// bne !=
			3'b100:  assign BranchTaken = (Negative ^ Overflow);  	// blt <
			3'b101:  assign BranchTaken = (Negative ^ Overflow);   	// bge >=
			3'b110:  assign BranchTaken = Carry; 					// bltu < unsigned
			3'b111:  assign BranchTaken = Carry; 				   	// bgeu >= unsigned
			default: assign BranchTaken = Zero;
	endcase

   assign PCSrc = Branch & (BranchTaken ^ funct3[0]) | Jump;
   
endmodule // controller

// ==========================================================================================
//
//	maindec		maindec		maindec		maindec		maindec		maindec		maindec		
//
// ==========================================================================================

module maindec (input  logic [6:0] op,
		output logic [1:0] ResultSrc,
		output logic 	   MemWrite,
		output logic 	   Branch,
		output logic [1:0]  ALUSrc,
		output logic 	   RegWrite, Jump,
		output logic [2:0] ImmSrc,
		output logic [1:0] ALUOp);
   
   logic [12:0] 		   controls;
   
   assign {RegWrite, ImmSrc, ALUSrc, MemWrite,
	   ResultSrc, Branch, ALUOp, Jump} = controls;
   
   always_comb
     case(op)
       // RegWrite_ImmSrc_ALUSrc_MemWrite_ResultSrc_Branch_ALUOp_Jump
       //    x    _  xxx _  x   _    x   _    xx   _   x  _  xx _  x
       7'b0000011: controls = 13'b1_000_01_0_01_0_00_0; // load
       7'b0100011: controls = 13'b0_001_01_1_00_0_00_0; // save
       7'b0110011: controls = 13'b1_xxx_00_0_00_0_10_0; // R–type
       7'b1100011: controls = 13'b0_010_00_0_00_1_01_0; // B-Type
       7'b0010011: controls = 13'b1_000_01_0_00_0_10_0; // I–type ALU
       7'b1101111: controls = 13'b1_011_xx_0_10_0_xx_1; // Jal      lec 10 slide 29
       7'b1100111: controls = 13'b1_000_01_0_10_0_00_1; // jalr    need to find path from SrcA to PC 
       7'b0010111: controls = 13'b1_100_11_0_00_0_00_0; // auipc    
       7'b0110111: controls = 13'b1_100_01_0_00_0_11_0; // lui      

       default: controls = 13'bx_xxx_x_x_xx_x_xx_x; // ???
     endcase // case (op)
   
endmodule // maindec

// ==========================================================================================
//
//	aludec		aludec		aludec		aludec		aludec		aludec		aludec		
//
// ==========================================================================================

module aludec (input  logic     opb5,
	       input  logic [2:0]   funct3,
	       input  logic 	    funct7b5,
	       input  logic [1:0]   ALUOp,
	       output logic [3:0]   ALUControl);
   
   logic 			  RtypeSub;
   
   assign RtypeSub = funct7b5 & opb5; // TRUE for R–type subtract


   always_comb
     case(ALUOp)
       2'b00: ALUControl = 4'b0000; // addition
      //  2'b01: ALUControl = 4'b0001; // subtraction
       2'b01: if (funct3 == 3'b000 || funct3 == 3'b001) // used full funct 3 for clarity code - jordan
                  ALUControl = 4'b1011; // subtraction beq/bne
              else if (funct3 == 3'b100 || funct3 == 3'b101) // used full funct 3 for clarity code - jordan
                  ALUControl = 4'b1101; // subtraction blt/bge
              else 
                  ALUControl = 4'b1111; // subtraction bltu/bgeu
	   2'b11:   // LUI
			  ALUControl = 4'b1110;
       default: case(funct3) // R–type or I–type ALU
		    3'b000: if (RtypeSub)
		                 ALUControl = 4'b0001; // sub
		            else
		                 ALUControl = 4'b0000; // add, addi
		    3'b010:   if (!RtypeSub) // I type set les than
						  ALUControl = 4'b0101; // slt, slti
					  else
						  if (!funct7b5)
							 ALUControl = 4'b0101; // slt
						  else
							 ALUControl = 4'b1010; // sgt
		    3'b110:   ALUControl = 4'b0011; // or, ori
		    3'b111:   ALUControl = 4'b0010; // and, andi
            3'b100:   ALUControl = 4'b0100; // xor, xori
            3'b101: if (funct7b5)   
                         ALUControl = 4'b0111; // sra, srai
                    else
                         ALUControl = 4'b0110; // srl, srli
            3'b001:   ALUControl = 4'b1000; // sll, slli
            3'b011:   if (!RtypeSub) // I type
						ALUControl = 4'b1001; // sltiu
					  else // R type
						if (!funct7b5)
							ALUControl = 4'b1001; // sltu
						else
							ALUControl = 4'b1100;
		    default:  ALUControl = 4'bxxxx; // ???
		   endcase // case (funct3)       
     endcase // case (ALUOp)
   
endmodule // aludec

// ==========================================================================================
//
//	datapath	datapath	datapath	datapath	datapath	datapath	datapath			
//
// ==========================================================================================

module datapath (input  logic        clk, reset,
		 input  logic [1:0]  ResultSrc,
		 input  logic 	     PCSrc, Jump,
	     input  logic [1:0]  ALUSrc,
		 input  logic 	     RegWrite,
		 input  logic [2:0]  ImmSrc,
		 input  logic [3:0]  ALUControl,
		 output logic 	     Zero, Negative, Carry, Overflow,
		 output logic [31:0] PC,
		 input  logic [31:0] Instr,
		 output logic [31:0] ALUResult, WriteData,
		 input  logic [31:0] ReadData);
   
   logic [31:0] 		     PCNext, PCPlus4, PCTarget, PCAdr;
   logic [31:0] 		     ImmExt;
   logic [31:0] 		     SrcA, SrcB, RegOutA;
   logic [31:0] 		     Result;
   
   // next PC logic
   flopr #(32) pcreg (clk, reset, PCNext, PC);
   adder  pcadd4 (PC, 32'd4, PCPlus4);
   adder  pcaddbranch (PC, ImmExt, PCTarget);
   //mux2 #(32)  pcmux (PCPlus4, PCTarget, PCSrc, PCNext);
   
   // register file logic
   regfile  rf (clk, RegWrite, Instr[19:15], Instr[24:20],
	       Instr[11:7], Result, RegOutA, WriteData);
   extend  ext (Instr[31:7], ImmSrc, ImmExt);
   
   // ALU logic
   mux2 #(32)  srcamux (RegOutA, PC, ALUSrc[1], SrcA);		// mux for A input
   mux2 #(32)  srcbmux (WriteData, ImmExt, ALUSrc[0], SrcB); // mux for B input
   
   alu  alu (SrcA, SrcB, ALUControl, ALUResult, Zero, Negative, Carry, Overflow);
   
   mux3 #(32) resultmux (ALUResult, ReadData, PCPlus4, ResultSrc, Result);
   
   mux2 #(32)  pxAddrMux (PCTarget, ALUResult, (Jump & (ALUSrc === 2'b01)), PCAdr);
   // update PCNext
   mux2 #(32)  pcmux (PCPlus4, PCAdr, PCSrc, PCNext);

endmodule // datapath

// ==========================================================================================
//
//	adder		adder		adder		adder		adder		adder		adder					
//
// ==========================================================================================

module adder (input  logic [31:0] a, b,
	      output logic [31:0] y);
   
   assign y = a + b;
   
endmodule


// ==========================================================================================
//
//	extend		extend		extend		extend		extend		extend		extend						
//
// ==========================================================================================


module extend (input  logic [31:7] instr,
	       input  logic [2:0]  immsrc,
	       output logic [31:0] immext);
   
   always_comb
     case(immsrc)
       // I−type
       3'b000:  immext = {{20{instr[31]}}, instr[31:20]};
       // S−type (stores)
       3'b001:  immext = {{20{instr[31]}}, instr[31:25], instr[11:7]};
       // B−type (branches)
       3'b010:  immext = {{20{instr[31]}}, instr[7], instr[30:25], instr[11:8], 1'b0};       
       // J−type (jal)
       3'b011:  immext = {{12{instr[31]}}, instr[19:12], instr[20], instr[30:21], 1'b0};
       // U−type (lui, auipc)
       3'b100: immext = {instr[31:12], 12'b0};
       default: immext = 32'bx; // undefined
     endcase // case (immsrc)
   
endmodule // extend

// ==========================================================================================
//
//	flopr		flopr		flopr		flopr		flopr		flopr		flopr						
//
// ==========================================================================================

module flopr #(parameter WIDTH = 8)
   (input  logic             clk, reset,
    input logic [WIDTH-1:0]  d,
    output logic [WIDTH-1:0] q);
   
   always_ff @(posedge clk, posedge reset)
     if (reset) q <= 0;
     else  q <= d;
   
endmodule // flopr


module flopenr #(parameter WIDTH = 8)
   (input  logic             clk, reset, en,
    input logic [WIDTH-1:0]  d,
    output logic [WIDTH-1:0] q);
   
   always_ff @(posedge clk, posedge reset)
     if (reset)  q <= 0;
     else if (en) q <= d;
   
endmodule // flopenr

// ==========================================================================================
//
//	mux			mux			mux			mux			mux			mux			mux			mux							
//
// ==========================================================================================

module mux2 #(parameter WIDTH = 8)
   (input  logic [WIDTH-1:0] d0, d1,
    input logic 	     s,
    output logic [WIDTH-1:0] y);
   
  assign y = s ? d1 : d0;
   
endmodule // mux2



module mux3 #(parameter WIDTH = 8)
   (input  logic [WIDTH-1:0] d0, d1, d2,
    input logic [1:0] 	     s,
    output logic [WIDTH-1:0] y);
   
  assign y = s[1] ? d2 : (s[0] ? d1 : d0);
   
endmodule // mux3

// ==========================================================================================
//
//	memory		memory		memory		memory		memory		memory		memory									
//
// ==========================================================================================

module imem (input  logic [31:0] a,
	     output logic [31:0] rd);
   
   // changed RAM to 1024x4 byts of memory to test previous test files
   logic [31:0] 		 RAM[2047:0];
   
   assign rd = RAM[a[31:2]]; // word aligned
   
endmodule // imem


module dmem (input  logic        clk, we,
	     input  logic [31:0] a, wd,
		 input  logic [2:0]  funct3,
	     output logic [31:0] rd);
   
   logic [31:0] 		 RAM[2047:0];
   logic [31:0] 		 mask, extend_mask, data;
   
   logic [1:0] alignment;
   logic signBit;
   
   assign alignment = a[1:0];
   assign data      = RAM[a[31:2]];
   assign signBit   = data[8 * alignment + ((funct3 == 3'b001) ? 15 : ((funct3 == 3'b000) ? 7 : 31))];
   
   always_comb
	case(funct3)
		3'b010:  assign mask = 32'hFFFFFFFF; // load word
		3'b000:  assign mask = 32'h000000FF << (8 * alignment); // load byte
				 //assign extend_mask = {{24{signBit}}, {8'hFF}};
		3'b100:  assign mask = 32'h000000FF << (8 * alignment); // load unsigned byte
				 //assign extend_mask = {{24{signBit}}, {8'hFF}};
		3'b001:  assign mask = 32'h0000FFFF << (8 * alignment); // load half
				 //assign extend_mask = {{16{signBit}}, {16'hFFFF}};
		3'b101:  assign mask = 32'h0000FFFF << (8 * alignment); // load unsigned half
				 //assign extend_mask = {{16{signBit}}, {16'hFFFF}};
		default: assign mask = 32'hFFFFFFFF;
				 //assign extend_mask = 32'hFFFFFFFF;
	endcase
	
   always_comb
	case(funct3)
		3'b000: assign extend_mask = {{24{signBit}}, {8'h00}};
		//3'b100: assign extend_mask = {{24{1'b0}}, {8'h00}};
		3'b001: assign extend_mask = {{16{signBit}}, {16'h0000}};
		//3'b101: assign extend_mask = {{16{1'b0}}, {16'h0000}};
		default: assign extend_mask = 32'h00000000;
	endcase
   
   assign rd = ((data & mask) >> (8 * alignment)) | extend_mask; // word aligned
   
   always_ff @(posedge clk)
     if (we) RAM[a[31:2]] <= ((wd << (8 * alignment)) & mask) | (data & (~mask));
   
endmodule // dmem

// ==========================================================================================
//
//	ALU		ALU		ALU		ALU		ALU		ALU		ALU		ALU		ALU		ALU		ALU											
//
// ==========================================================================================

module alu (input  logic [31:0] a, b,
            input  logic [3:0] 	alucontrol,
            output logic [31:0] result,
            output logic 	zero, negative, carry, overflow);

   logic [31:0] 	       condinvb, sum, xorOut, sltuOut;
   logic [32:0]			   carried;
   logic 		       Cout;
   logic 		       isAddSub;       // true when is add or subtract operation


   assign condinvb = alucontrol[0] ? ~b : b;
   assign sum = a + condinvb + alucontrol[0];
   assign isAddSub = ~alucontrol[2] & ~alucontrol[1] |
                     ~alucontrol[1] & alucontrol[0];   
   assign xorOut = a ^ b;
   assign sltuOut = unsigned'(a) < unsigned'(b);

   always_comb
     case (alucontrol)
       4'b0000:  result = sum;         // add
       4'b0001:  result = sum;         // subtract
       4'b0010:  result = a & b;       // and
       4'b0011:  result = a | b;       // or
       4'b0101:  result = sum[31] ^ overflow; // slt 
       4'b0110:  result = a >> unsigned'(b[4:0]);      // srl  
       4'b0111:  result = $signed(a) >>> unsigned'(b[4:0]);     // sra
       4'b0100:  result = xorOut;      // xor  
       4'b1000:  result = a << unsigned'(b[4:0]);      // sll
       4'b1001:  result = sltuOut;     // sltu
       4'b1011:  result = sum;         // beq, bne
       4'b1101:  result = sum;         // blt, bge
       4'b1111:  result = sum;         // bltu, bgeu
	   4'b1110:  result = b;		   // LUI
	   4'b1010:  result = ~(sum[31] ^ overflow); // sgt
	   4'b1100:  result = ~sltuOut;    // sgtu
       default:  result = 32'bx;
     endcase

   //case (alucontrol) 
   //  4'b1011: assign zero = (result == 32'b0);
   //  4'b1101: assign zero = (result < 32'b0);
   //  4'b1111: assign unsigned'(condinvb) = alucontrol[0] ? unsigned'~(b) : unsigned'(b);
   //           assign temp_sum = unsigned'(a) + unsigned'(condinvb) + alucontrol[0]; // added a temp_sum just to ensure sum isn't modified
   //           assign zero = (temp_sum < 32'b0);
   //endcasew

   // overflow
   assign overflow = ~(alucontrol[0] ^ a[31] ^ b[31]) & (a[31] ^ sum[31]) & isAddSub;
   // negative
   assign negative = sum[31];
   // Cout  -- lec13 slide 14. the ALU only does addition. add a + b and see if sum < less than either a or b. if so then it carried
   assign carried = a - b;
   assign carry = carried[32];
   // zero
   assign zero = (result == 32'b0);
   //assign temp_zero = (result == 32'b0);
   
   // lec 13 slide 17
   //assign BGE =  (negative ^ overflow);
   //assign BGEU = ~temp_zero & carry;
   //assign BLT =  ~(negative ^ overflow);
   //assign BLTU = ~carry;
    
   // forward through to Controller->PCsrc
   //assign zero = zero | (BGE | BGEU | BLT | BLTU);
   //always_comb
   //case (alucontrol)
   //    4'b1011: assign zero = (result == 32'b0);
   //    4'b1101: assign zero = BGE;
   //    4'b1111: assign zero = BLTU | BGEU;
   //   default: assign zero = (result == 32'b0);
   //endcase

   
endmodule // alu

// ==========================================================================================
//
//	Regfile		Regfile		Regfile		Regfile		Regfile		Regfile		Regfile													
//
// ==========================================================================================

module regfile (input  logic        clk, 
		input  logic 	    we3, 
		input  logic [4:0]  a1, a2, a3, 
		input  logic [31:0] wd3, 
		output logic [31:0] rd1, rd2);

   logic [31:0] 		    rf[31:0];

   // three ported register file
   // read two ports combinationally (A1/RD1, A2/RD2)
   // write third port on rising edge of clock (A3/WD3/WE3)
   // register 0 hardwired to 0

   always_ff @(posedge clk)
     if (we3) rf[a3] <= wd3;	

   assign rd1 = (a1 != 0) ? rf[a1] : 0;
   assign rd2 = (a2 != 0) ? rf[a2] : 0;
   
endmodule // regfile
