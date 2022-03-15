`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/06/16 15:58:47
// Design Name: 
// Module Name: simulate
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module simulate;
parameter half_period = 50;
wire [3:0]  O;
reg [3:0]   I;
reg CLK, reset;

four_D_f UUT (O, I, CLK, reset);

initial begin
    #0  I = 13; CLK = 0; reset = 1;
    #100    I = 10;
    #100    reset = 0;
    #200    I = 4;
    #100    reset = 1;
    #300    reset = 0;
    #100    I = 6;
    end
    
    always #half_period CLK = ~CLK;
    
    initial #1000   $stop;
    
endmodule
