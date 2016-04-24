`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:47:28 03/02/2016 
// Design Name: 
// Module Name:    randomNumber 
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
module randomNumber #(parameter BITS = 5)(
    input clk,
    output reg [4:0] data
    );
    
   reg [4:0] data_next;
   
   initial begin
    data = 5'h1f;
   end
   
   always @* begin
    data_next[4] = data[4]^data[1];
    data_next[3] = data[3]^data[0];
    data_next[2] = data[2]^data_next[4];
    data_next[1] = data[1]^data_next[3];
    data_next[0] = data[0]^data_next[2];
   end
   
   always @(posedge clk) begin
    /*if(!rst_n)
        data <= 5'h1f;
    else*/
        data <= data_next;
   end



endmodule
