`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:47:07 02/10/2016 
// Design Name: 
// Module Name:    clock_750hz 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module clock_750hz(clk, clk_750hz
    );
    input clk;
    output clk_750hz;
    
    reg clk_750hz;
    
    reg [17:0] counter;
	 
	 initial begin
		counter = 0;
	 end
    
    always @ (posedge clk)
        begin
            if (counter == 18'b100000100011010101)
            begin
                counter <= 0;
                clk_750hz <= 1;
            end
            else
            begin
                clk_750hz <= 0;
                counter <= counter + 1;
            end    
        end

endmodule
