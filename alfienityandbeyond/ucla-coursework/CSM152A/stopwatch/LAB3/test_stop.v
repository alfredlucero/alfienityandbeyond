`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   13:36:08 02/08/2016
// Design Name:   stopwatch
// Module Name:   C:/Users/152/Desktop/Alfred_Maya_Lab3/LAB3/test_stop.v
// Project Name:  LAB3
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: stopwatch
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module test_stop;

	// Inputs
	reg clk;
	reg btnR;
	reg btnS;
	reg [7:0] sw;

	// Outputs
	wire [7:0] seg;
	wire [3:0] an;

	// Instantiate the Unit Under Test (UUT)
	stopwatch uut (
		.clk(clk), 
		.btnR(btnR), 
		.btnS(btnS), 
		.sw(sw), 
		.seg(seg), 
		.an(an)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		btnR = 0;
		btnS = 0;
		sw = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here

	end
    
    always #5 clk = ~clk;
      
endmodule

