`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   12:55:59 02/08/2016
// Design Name:   display7
// Module Name:   C:/Users/152/Desktop/Alfred_Maya_Lab3/LAB3/tb_7seg.v
// Project Name:  LAB3
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: display7
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module tb_7seg;

	// Inputs
	reg clk;
	reg [3:0] seg_number;
	reg [1:0] an_number;
	reg btnR;
	reg btnS;
	reg [7:0] sw;

	// Outputs
	wire [7:0] seg;
	wire [3:0] an;

	// Instantiate the Unit Under Test (UUT)
	display7 uut (
		.clk(clk), 
		.seg_number(seg_number), 
		.an_number(an_number), 
		.seg(seg), 
		.an(an), 
		.btnR(btnR), 
		.btnS(btnS), 
		.sw(sw)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		seg_number = 0;
		an_number = 0;
		btnR = 0;
		btnS = 0;
		sw = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here
        seg_number = 8;
        an_number = 0;
        
	end
      
      always #5 clk = ~clk;
     
endmodule

