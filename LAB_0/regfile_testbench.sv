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
	
   logic [5:0] count, errors;
   logic [31:0] rd1_expect, rd2_expect;
   
   logic cycle2, break_test;
   
   
   
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
		count = 0; errors = 0;
		we3 = 1'b1; // set write enable high
		
		cycle2 = 0; break_test = 0; // start cycle at 0 and lower the break flag
     end

   
always @(posedge clock)
	begin
		// Only need to add new case, will default break the test
		// once all the cases seqeuntly tested
		case (count) 
			0: 		 begin
					// read addr 1, read addr2, write addr, write data
					// read data 1 expected, read data 2 expected
				#1; {ra1, ra2, wa3, wd3} = {5'd0, 5'd0, 5'd0, 32'h00000000};
					{rd1_expect, rd2_expect} = {32'h00000000, 32'h00000000}; end
					
			1: 		 begin
				#1; {ra1, ra2, wa3, wd3} = {5'd0, 5'd0, 5'd0, 32'hffffffff};
					{rd1_expect, rd2_expect} = {32'h00000000, 32'h00000000}; end
			
			2: 		 begin
				#1; {ra1, ra2, wa3, wd3} = {5'd1, 5'd0, 5'd1, 32'hffffffff};
					{rd1_expect, rd2_expect} = {32'hffffffff, 32'h00000000}; end
			
			3: 		 begin
				#1; {ra1, ra2, wa3, wd3} = {5'd0, 5'd1, 5'd1, 32'hffffffff};
					{rd1_expect, rd2_expect} = {32'h00000000, 32'hffffffff}; end
					
			4: 		 begin
				#1; {ra1, ra2, wa3, wd3} = {5'd1, 5'd1, 5'd1, 32'hffffffff};
					{rd1_expect, rd2_expect} = {32'hffffffff, 32'hffffffff}; end
					
			5: 		 begin
				#1; {ra1, ra2, wa3, wd3} = {5'd1, 5'd1, 5'd1, 32'haaaaaaaa};
					{rd1_expect, rd2_expect} = {32'haaaaaaaa, 32'haaaaaaaa}; end
					
			default: begin break_test = 1; end // raise the break flag if there are no more cases
		endcase
	end

always @(negedge clock)
	begin
		if (break_test) begin // check see if break flag was raised. if so stop the test
			$display("Test Complete: %d errors found", errors);
			$stop; // stop the testbench
		end
		if (cycle2) begin // capture only after two clock cycles
			if (rd1 !== rd1_expect | rd2 !== rd2_expect) begin
				// check if read data 1 matches that of read data 1 expected: same for 2
				$display("ERROR: Read Address did not match expected case: %d", count);
				errors = errors + 1;
			end
			count = count + 1;
		end
		cycle2 = ~cycle2; // toggle the cycle
	end
		

endmodule // regfile_tb
