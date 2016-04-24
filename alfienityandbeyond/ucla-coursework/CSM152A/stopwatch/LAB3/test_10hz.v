`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   13:32:53 02/04/2016
// Design Name:   clock_10hz
// Module Name:   C:/Users/152/Desktop/Alfred_Maya_Lab3/LAB3/test_10hz.v
// Project Name:  LAB3
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: clock_10hz
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module test_10hz;

	// Inputs
	reg clk;
	reg reset;

	// Outputs
	wire clk_10hz;

	// Instantiate the Unit Under Test (UUT)
	clock_10hz uut (
		.clk(clk), 
		.reset(reset), 
		.clk_10hz(clk_10hz)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		reset = 1;
        #100;
        reset = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here

	end
    
    always #5 clk = ~clk;
      
endmodule

