`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:08:31 02/10/2016 
// Design Name: 
// Module Name:    clock_50hz 
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
module clock_50hz(clk, clk_50hz
    );
    input clk;
    output clk_50hz;
    
    reg clk_50hz;
    
    reg [20:0] counter;
	 
	 initial begin
		counter = 0;
	 end
    
    always @ (posedge clk)
        begin
            if (counter == 21'b111101000010010000000)
            begin
                counter <= 0;
                clk_50hz <= 1;
            end
            else
            begin
                clk_50hz <= 0;
                counter <= counter + 1;
            end    
        end
    

endmodule
