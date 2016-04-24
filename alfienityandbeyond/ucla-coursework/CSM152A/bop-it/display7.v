`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:49:49 03/02/2016 
// Design Name: 
// Module Name:    display7 
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
module display7(clk, seg_number, an_number, seg, an, btnU
    );
    
    input clk, btnU;
    output reg [7:0] seg;
    output reg [3:0] an;
    
    input wire [3:0] seg_number;
    input wire [1:0] an_number;
    
    always @ (*)
    begin 
        case(seg_number)
            4'h0: seg = 8'b11000000;
            4'h1: seg = 8'b11111001;
            4'h2: seg = 8'b10100100;
            4'h3: seg = 8'b10110000;
            4'h4: seg = 8'b10011001;
            4'h5: seg = 8'b10010010;
            4'h6: seg = 8'b10000010;
            4'h7: seg = 8'b11111000;
            4'h8: seg = 8'b10000000;
            4'h9: seg = 8'b10010000;
            default: seg = 8'b00000000;
        endcase
        case(an_number)
            2'b00: an = 4'b0111;
            2'b01:
            begin
            an = 4'b1011;
            seg[7] = 0;
            end
            2'b10: an = 4'b1101;
            2'b11: an = 4'b1110;
            default: an = 4'b0000;
        endcase
     end 


endmodule