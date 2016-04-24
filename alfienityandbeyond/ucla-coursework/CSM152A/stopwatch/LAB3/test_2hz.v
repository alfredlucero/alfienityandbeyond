`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   13:14:06 02/04/2016
// Design Name:   clock_2hz
// Module Name:   C:/Users/152/Desktop/Alfred_Maya_Lab3/LAB3/test_2hz.v
// Project Name:  LAB3
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: clock_2hz
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module test_2hz;

	// Inputs
	reg clk;
	reg reset;

	// Outputs
	wire clk_2hz;

	// Instantiate the Unit Under Test (UUT)
	clock_2hz uut (
		.clk(clk), 
		.reset(reset), 
		.clk_2hz(clk_2hz)
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

