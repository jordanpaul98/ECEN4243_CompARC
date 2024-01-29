// ECEN 4243 LAB0 regfile default case test
module stimulus ();

   logic  clock;
   logic we3;
   logic [4:0] ra1;
   logic [4:0] ra2;
   logic [4:0] wa3;
   logic [31:0] wd3;
   logic [31:0] rd1;
   logic [31:0] rd2;

   
   integer handle3;
   integer desc3;
   
   // Instantiate DUT
   regfile dut (clock, we3, ra1, ra2, wa3, wd3, rd1, rd2);

   // Setup the clock to toggle every 1 time units 
   initial 
     begin	
	clock = 1'b1;
	forever #5 clock = ~clock;
     end

   initial
     begin
	// Gives output file name
	handle3 = $fopen("reg_test.out");
	// Tells when to finish simulation
	#5000 $finish;		
     end

   always 
     begin
	desc3 = handle3;
	
	#5 $fdisplay(desc3, "%b | %b %b %b | %h || %h %h", 
		     we3, ra1, ra2, wa3, wd3, rd1, rd2);
     end   
   
   initial 
     begin      
	#0  we3 = 1'b0;
        #10 we3 = 1'b1;
	#0  ra1 = 5'b00000;
	#0 ra2 = 5'b00000;
	#0 wa3 = 5'b00000;
	#0 wd3 = 32'b11111111111111111111111111111111;

	#20 ra1 = 5'b00001;
	#0 ra2 = 5'b00000;
	#0 wa3 = 5'b00000;
	#0 wd3 = 32'b11111111111111111111111111111111;

	#20  ra1 = 5'b00001;
	#0 ra2 = 5'b00000;
	#0 wa3 = 5'b00001;
	#0 wd3 = 32'b11111111111111111111111111111111;	

	#20  ra1 = 5'b00000;
	#0 ra2 = 5'b00001;
	#0 wa3 = 5'b00001;
	#0 wd3 = 32'b11111111111111111111111111111111;

	#20  ra1 = 5'b00001;
	#0 ra2 = 5'b00001;
	#0 wa3 = 5'b00001;
	#0 wd3 = 32'b11111111111111111111111111111111;

	#0  ra1 = 5'b00001;
	#0 ra2 = 5'b00000;
	#0 wa3 = 5'b00001;
	#0 wd3 = 32'b10101010101010101010101010101010;
     end

endmodule // regfile_tb
