// ECEN 4243 Lab 0 regfile testbench



module stimulus();

   logic  clock;
   logic we3;
   logic [4:0] ra1;
   logic [4:0] ra2;
   logic [4:0] wa3;
   logic [31:0] wd3;
   logic [31:0] rd1;
   logic [31:0] rd2;
	
   logic [31:0] count, errors;
   logic [31:0] rd1_expect, rd2_expect;
   
   logic cycle2, break_test;

   logic [111:0] testvectors[10000:0];
   
   
   
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
		$readmemb("regfile.tv", testvectors);
		count = 0; errors = 0;
		we3 = 1'b1; // set write enable high
		
		cycle2 = 0; break_test = 0; // start cycle at 0 and lower the break flag
     end

   
always @(posedge clock)
	begin
		// Only need to add new case, will default break the test
		// once all the cases seqeuntly tested

		#1; {ra1, ra2, wa3, wd3, rd1_expect, rd2_expect} = testvectors[count];
		
	end

always @(negedge clock)
	begin
		if (cycle2) begin // capture only after two clock cycles
			if (rd1 !== rd1_expect | rd2 !== rd2_expect) begin
				// check if read data 1 matches that of read data 1 expected: same for 2
				$display("ERROR: Read Address did not match expected case: %d", count);
				errors = errors + 1;
			end
			count = count + 1;
			
			if (testvectors[count] === 'bx) begin
				$display("%d tests completed with %d errors", count, errors);
				$stop;
			end
		end
		cycle2 = ~cycle2; // toggle the cycle
	end
		

endmodule // regfile_tb

