`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:04:48 03/02/2016 
// Design Name: 
// Module Name:    gamepad 
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
module gamepad(clk, btnR, btnD, btnL, btnU, btnS, sw, seg, an, led, speaker 
    );
    input clk;
    input btnR, btnS, btnD, btnU, btnL;
    input [7:0] sw;
    output reg [7:0] led;
    output [7:0] seg;
    output [3:0] an;
    output reg speaker;
    reg [3:0] seg_number;
    reg [1:0] an_number;
    
    wire clk_1hz; // increment the time
    wire clk_500hz; // outputting 7seg display
    wire [4:0] randomBop; // random command
    
    reg [7:0] ledCode;
    reg [3:0] bopCode; 
    reg [3:0] ones_seconds;
    reg [3:0] tens_seconds;
    reg [3:0] ones_score;
    reg [3:0] tens_score;
    integer an_toggle;
    integer an_index;
    integer gameOn;
    integer command_type;
    integer command_number;
    integer roundWon;
    integer roundDelay;
    
    initial begin
        ones_seconds = 0;
        tens_seconds = 0;
        command_type = 10;
        command_number = 8;
        an_toggle = 0;
        an_index = 0;
        ones_score = 0;
        tens_score = 0;
        bopCode = 0;
        ledCode = 0;
        gameOn = 1;
        roundWon = 0;
        roundDelay = 0;
        
    end
    
   
    
    randomNumber randomNum (
        .clk(clk),
        .data(randomBop)
    );
    
    clock_1hz clock_1 (
		.clk(clk), 
		.clk_1hz(clk_1hz)
	);
    
    clock_500hz clock_500 (
        .clk(clk),
        .clk_500hz(clk_500hz)
    );
    
    display7 segmentDisplay (
            .clk(clk), 
            .seg_number(seg_number), 
            .an_number(an_number), 
            .seg(seg), 
            .an(an), 
            .btnU(btnU) 
    );
    
    always @ (posedge clk)
    begin
        if (btnS)
        begin
            roundWon <= 0;
            roundDelay <= 0;
            gameOn <= 1;
            ones_score <= 0;
            tens_score <= 0;
            ones_seconds <= 0;
            tens_seconds <= 0;
            bopCode <= randomBop % 12;
        end
        
        if (!roundWon)
        begin
        case(bopCode)
            0:
            begin // S0
                if (sw[0])
                begin
                    roundWon <= 1;
                end
                else if(sw[7:0] || btnU || btnL || btnD || btnR)
                begin
                    gameOn <= 0;
                end
            end
            1:
            begin // S1
                if (sw[1])
                begin
                    roundWon <= 1;
                end
                else if(sw[7:0] || btnU || btnL || btnD || btnR)
                begin
                    gameOn <= 0;
                end
            end
            2:
            begin // S2
                if (sw[2])
                begin
                    roundWon <= 1;
                end
                else if(sw[7:0] || btnU || btnL || btnD || btnR)
                begin
                    gameOn <= 0;
                end
            end
            3:
            begin // S3
                if (sw[3])
                begin
                    roundWon <= 1;
                end
                else if(sw[7:0] || btnU || btnL || btnD || btnR)
                begin
                    gameOn <= 0;
                end
            end
            4:
            begin // S4
                if (sw[4])
                begin
                    roundWon <= 1;
                end
                else if(sw[7:0] || btnU || btnL || btnD || btnR)
                begin
                    gameOn <= 0;
                end
            end
            5:
            begin // S5
                if (sw[5])
                begin
                    roundWon <= 1;
                end
                else if(sw[7:0] || btnU || btnL || btnD || btnR)
                begin
                    gameOn <= 0;
                end
            end
            6:
            begin // S6
                if (sw[6])
                begin
                    roundWon <= 1;
                end
                else if(sw[7:0] || btnU || btnL || btnD || btnR)
                begin
                    gameOn <= 0;
                end
            end
            7:
            begin // S7
                if (sw[7])
                begin
                    roundWon <= 1;
                end
                else if(sw[7:0] || btnU || btnL || btnD || btnR)
                begin
                    gameOn <= 0;
                end
            end
            8:
            begin // B0
                if (btnU)
                begin
                    roundWon <= 1;
                end
                else if(sw[7:0] || btnU || btnL || btnD || btnR)
                begin
                    gameOn <= 0;
                end
            end
            9:
            begin // B1
                if (btnR)
                begin
                    roundWon <= 1;
                end
                else if(sw[7:0] || btnU || btnL || btnD || btnR)
                begin
                    gameOn <= 0;
                end
            end
            10:
            begin // B2
                if (btnD)
                begin
                    roundWon <= 1;
                end
                else if(sw[7:0] || btnU || btnL || btnD || btnR)
                begin
                    gameOn <= 0;
                end
            end
            11:
            begin // B3
                if (btnL)
                begin
                    roundWon <= 1;
                end
                else if(sw[7:0] || btnU || btnL || btnD || btnR)
                begin
                    gameOn <= 0;
                end
            end
        endcase
        end
        
        if (clk_1hz && gameOn)
        begin
            if (roundWon)
            begin
                if (roundDelay == 3)
                begin
                    roundWon <= 0;
                    roundDelay <= 0;
                    bopCode <= randomBop % 12;
                    
                    if (ones_score == 4'b1001)
                    begin
                       ones_score <= 0; 
                       tens_score <= tens_score + 1;
                    end
                    else
                    begin
                       ones_score <= ones_score + 1;
                    end
                end
                else
                begin
                    roundDelay <= roundDelay + 1;
                end
                
                   ones_seconds <= 0;
                   tens_seconds <= 0;
            end
            else
            begin 
                ones_seconds <= ones_seconds + 1;
                if (ones_seconds == 4'b1001)
                begin
                    ones_seconds <= 0; 
                    tens_seconds <= tens_seconds + 1;
                end
            end
        end
        if (tens_seconds == 4'b0001)
        begin
            ones_seconds <= 0;
            tens_seconds <= 0;
            gameOn <= 0;
        end
        
        if (clk_500hz && gameOn) // output timer
        begin
            an_index <= an_toggle % 4;
            case(an_index)
                0:
                begin
                    if (bopCode > 4'b0111) // > 7, Buttons
                    begin
                        seg_number <= 4'b1000;
                        ledCode <= 8'b00000000;
                        led [7:0] <= ledCode [7:0];
                    end
                    else // <= 7, Switches
                    begin
                        seg_number <= 4'b0101;
                        ledCode <= 8'b00000001 << (bopCode % 8);
                        led [7:0] <= ledCode [7:0];
                    end
                    an_number <= an_index;
                end
                1:
                begin
                    seg_number <= bopCode % 8; 
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
        else if (clk_500hz && !gameOn)
        begin
            an_index <= an_toggle % 4;
            case(an_index)
                0:
                begin
                    seg_number <= 0;
                    an_number <= an_index;
                end
                1:
                begin
                    seg_number <= 0;
                    an_number <= an_index;
                end
                2:
                begin
                    seg_number <= tens_score;
                    an_number <= an_index;
                end
                3:
                begin
                    seg_number <= ones_score;
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
    end

endmodule
