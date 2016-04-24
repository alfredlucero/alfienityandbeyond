`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:20:09 02/08/2016 
// Design Name: 
// Module Name:    stopwatch 
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
module stopwatch(clk, btnR, btnS, sw, seg, an 
    );
    input clk;
    input btnR, btnS;
    input [7:0] sw; // sw[0] = adj, sw[1] = sel
    output [7:0] seg;
    output [3:0] an;
    reg [3:0] seg_number;
    reg [1:0] an_number;
    
    wire clk_1hz; // increment the time
	wire clk_2hz; // adjust mode
	//wire clk_10hz; // blink mode
    wire clk_50hz; // blink mode
    wire clk_500hz; // outputting 7seg display
    wire clk_750hz; // debouncer
	 
    reg [26:0] counter;
    reg [3:0] ones_seconds;
    reg [3:0] tens_seconds;
    reg [3:0] ones_minutes;
    reg [3:0] tens_minutes;
    integer an_toggle;
    integer an_index;
	integer pauseOn;
     
    
    initial begin
        ones_seconds = 0;
        tens_seconds = 0;
        ones_minutes = 0;
        tens_minutes = 0;
        an_toggle = 0;
        an_index = 0;
		pauseOn = 0;
    end
	 
	 /*
	 clock_10hz clock_10 (
		.clk(clk),
		.clk_10hz(clk_10hz)
	);
	 */
    clock_2hz clock_2 (
		.clk(clk),
		.clk_2hz(clk_2hz)
	);
    
    clock_1hz clock_1 (
		.clk(clk), 
		.clk_1hz(clk_1hz)
	);
    
     clock_50hz clock_50 (
        .clk(clk),
        .clk_50hz(clk_50hz)
    );
	 
	 clk_500hz clock_500 (
        .clk(clk),
        .clk_500hz(clk_500hz)
    );
    
    
	 clock_750hz clock_750 (
        .clk(clk),
        .clk_750hz(clk_750hz)
    );
    
    display7 segmentDisplay (
            .clk(clk), 
            .seg_number(seg_number), 
            .an_number(an_number), 
            .seg(seg), 
            .an(an), 
            .btnR(btnR), 
            .btnS(btnS), 
            .sw(sw)
    );
   
    
    always @ (posedge clk)
    begin
        if (btnR) // reset
        begin
			ones_seconds <= 0;
			tens_seconds <= 0;
			ones_minutes <= 0;
			tens_minutes <= 0;
		end
        
        if (clk_1hz && sw[0] == 0) // increment time
        begin
				if (pauseOn == 0) // pause
				begin
					ones_seconds <= ones_seconds + 1;
					if (ones_seconds == 4'b1001)
					begin
						 ones_seconds <= 0; 
						 tens_seconds <= tens_seconds + 1;
						 if (tens_seconds == 4'b0101)
						 begin
							  tens_seconds <= 0;
							  ones_minutes <= ones_minutes + 1;
							  if (ones_minutes == 4'b1001)
							  begin
									ones_minutes <= 0;
									tens_minutes <= tens_minutes + 1;
									if (tens_minutes == 4'b0101)
									begin
										 tens_minutes <= 0;
									end
							  end
						 end
					 end
				 end
				//$display("%d%d%d%d", tens_minutes, ones_minutes, tens_seconds, ones_seconds); 
        end
        else if (clk_2hz && sw[0] == 1)
        begin
            if (sw[1] == 0) // sel:minutes
            begin
                ones_minutes <= ones_minutes + 1;
				if (ones_minutes == 4'b1001)
				begin
					ones_minutes <= 0;
					tens_minutes <= tens_minutes + 1;
					if (tens_minutes == 4'b0101)
					begin
						tens_minutes <= 0;
					end
				end
            end
            else // sel:seconds
            begin
                ones_seconds <= ones_seconds + 1;
				if (ones_seconds == 4'b1001)
				begin
					ones_seconds <= 0; 
					tens_seconds <= tens_seconds + 1;
					if (tens_seconds == 4'b0101)
						tens_seconds <= 0;     
                end
            end
        end
        if (clk_500hz && sw[0] == 0) // output display
        begin
            an_index <= an_toggle % 4;
            case(an_index)
                0:
                begin
                    seg_number <= tens_minutes;
                    an_number <= an_index;
                end
                1:
                begin
                    seg_number <= ones_minutes;
                    an_number <= an_index;
                end
                2:
                begin
                    seg_number <= tens_seconds;
                    an_number <= an_index;
                end
                3:
                begin
                    seg_number <= ones_seconds;
                    an_number <= an_index;                  
                end
                default:
                begin
                    seg_number <= 0;
                    an_number <= 0;
                end
            endcase
            an_toggle <= an_toggle + 1;
        end
        else if (clk_50hz && sw[0] == 1) // blink mode
        begin
            an_index <= an_toggle % 4;
            case(an_index)
                0:
                begin
                    seg_number <= tens_minutes;
                    an_number <= an_index;
                end
                1:
                begin
                    seg_number <= ones_minutes;
                    an_number <= an_index;
                end
                2:
                begin
                    seg_number <= tens_seconds;
                    an_number <= an_index;
                end
                3:
                begin
                    seg_number <= ones_seconds;
                    an_number <= an_index;                  
                end
                default:
                begin
                    seg_number <= 0;
                    an_number <= 0;
                end
            endcase
            an_toggle <= an_toggle + 1;
        end
		  
      if (clk_750hz) // debouncer
		begin
            if(btnS && pauseOn == 0) begin
                pauseOn <= 1;
			end
			else if (btnS == 1 && pauseOn == 1)
				pauseOn <= 0;
		end
       
    end
    
    
    

endmodule
