`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/06/17 21:21:23
// Design Name: 
// Module Name: s
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


module s;
parameter half_period = 50;
wire    [3:0]   o;
wire    upper;
reg clear, set, clk, cnt;

F_c UUT (upper, o, clear, set, clk, cnt);

initial begin
    #0  clk = 0; cnt = 1; clear = 0; set = 0;
    end
    
    always     #half_period clk = ~clk;
    initial #1500   $stop;
endmodule
