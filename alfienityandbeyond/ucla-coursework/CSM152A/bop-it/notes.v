`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:10:09 03/02/2016 
// Design Name: 
// Module Name:    notes 
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
module notes(clk, speaker, signal
    );
    
    input clk;
    input [1:0] signal;
    output reg speaker;
    reg [3:0] seg_number;
    reg [1:0] an_number;
    reg [16:0] counter;
  
    always @(posedge clk)
    begin
        // NO SOUND
        if (signal == 2'b00)
        begin
            counter <= 0;
            speaker <= 0;
        end // BOP SIGNAL
        else if (signal == 2'b01)
        begin
            if(counter==28408) counter <= 0; else counter <= counter+1;
            speaker <= counter[14];
        end
        else // MISS SIGNAL
        begin
            if(counter==113634) counter <= 0; else counter <= counter+1;
            speaker <= counter[16];
        end
    end
    
    
endmodule
