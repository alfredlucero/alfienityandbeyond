`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:30:07 02/04/2016 
// Design Name: 
// Module Name:    clock_10hz 
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
module clock_10hz(clk, clk_10hz
    );
    
    input clk;
    output clk_10hz;
    
    reg clk_10hz;
    
    reg [23:0] counter;
	 
	 initial begin
		counter = 0;
	 end
    
    always @ (posedge clk)
        begin
            if (counter == 24'b100110001001011010000000)
            begin
                counter <= 0;
                clk_10hz <= 1;
            end
            else
            begin
                clk_10hz <= 0;
                counter <= counter + 1;
            end    
        end
        


endmodule
