`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:42:07 02/04/2016 
// Design Name: 
// Module Name:    clock_1hz 
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
module clock_1hz(clk, clk_1hz
    );
    input clk;
    output clk_1hz;
    
    reg clk_1hz;
    
    reg [26:0] counter;
    initial begin 
        counter = 0;
    end
    
    always @ (posedge clk)
        if (counter == 27'b101111101011110000100000000)
            begin
                counter <= 0;
                clk_1hz <= 1;
            end
        else
            begin
                clk_1hz <= 0;
                counter <= counter + 1;
            end    
endmodule


