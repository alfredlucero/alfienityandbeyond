`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   13:21:22 02/01/2016
// Design Name:   stopwatch
// Module Name:   C:/Users/152/Desktop/Alfred_Maya_Lab3/LAB3/teststopwatch.v
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

module teststopwatch;

	// Inputs
	reg RsRx;
	reg [1:0] sw;
	reg btnS;
	reg btnR;
	reg clk;


	// Outputs
	wire RsTx;

	// Instantiate the Unit Under Test (UUT)
	stopwatch uut (
		.RsTx(RsTx), 
		.RsRx(RsRx), 
		.sw(sw), 
		.btnS(btnS), 
		.btnR(btnR), 
		.clk(clk)
	);

	initial begin
		// Initialize Inputs
		RsRx = 0;
		sw = 0;
		btnS = 0;
		btnR = 1;
		clk = 0;
        #1000; btnR = 0;
        #1500000;
        
		// Add stimulus here
        

	end
    
    always #5 clk = ~clk;
      
endmodule

