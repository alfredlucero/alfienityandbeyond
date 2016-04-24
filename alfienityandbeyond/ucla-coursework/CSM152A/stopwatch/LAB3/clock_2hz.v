`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:57:14 02/04/2016 
// Design Name: 
// Module Name:    clock_2hz 
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
module clock_2hz(clk, clk_2hz
    );
    
    input clk;
    output clk_2hz;
    
    reg clk_2hz;
    
    reg [25:0] counter;
	 
	 initial begin
		counter = 0;
	 end
    
    always @ (posedge clk)
        begin
            if (counter == 26'b10111110101111000010000000)
            begin
                counter <= 0;
                clk_2hz <= 1;
            end
            else
            begin
                clk_2hz <= 0;
                counter <= counter + 1;
            end    
        end
        


endmodule
