`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:32:35 02/09/2016 
// Design Name: 
// Module Name:    clk_500hz 
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
module clk_500hz(clk, clk_500hz
    );
	input clk;
    output clk_500hz;
    
    reg clk_500hz;
    
    reg [17:0] counter;
	 
	 initial begin
		counter = 0;
	 end
    
    always @ (posedge clk)
        begin
            if (counter == 18'b110000110101000000)
            begin
                counter <= 0;
                clk_500hz <= 1;
            end
            else
            begin
                clk_500hz <= 0;
                counter <= counter + 1;
            end    
        end

endmodule
