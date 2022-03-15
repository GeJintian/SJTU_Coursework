`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/06/17 20:53:22
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
reg clear, set, clk, cnt;

f_b_counter UUT (o, clear, set, clk, cnt);

initial begin
    #0  clk = 0; cnt = 1; set = 0; clear = 0;
    #100    set = 1;
    #100    set = 0;
    #100    clear = 1; cnt = 0;
    #100    clear = 0;
    #100    cnt = 1;
    #100    cnt = 0;
    #100    cnt = 1;
    end
    
    always  #half_period clk = ~clk;
    initial #1000   $stop;
endmodule
