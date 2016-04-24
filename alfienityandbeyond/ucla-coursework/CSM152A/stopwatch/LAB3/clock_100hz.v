`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:19:24 02/04/2016 
// Design Name: 
// Module Name:    clock_100hz 
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
module clock_100hz(clk, clk_100hz
    );
    
    input clk;
    output clk_100hz;
    
    reg clk_100hz;
    
    reg [19:0] counter;
    initial begin
        counter = 0;
    end
    
    
    always @ (posedge clk)
    if (counter == 20'b11110100001001000000)
    begin
        counter <= 0;
        clk_100hz <= 1;
    end
    else
    begin
        clk_100hz <= 0;
        counter <= counter + 1;
    end
 
        

endmodule
