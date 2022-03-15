`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/07/02 14:48:07
// Design Name: 
// Module Name: test
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


module test;
parameter half_period = 50;
wire [3:0] Q;
reg [3:0] D;
reg clk, load, si, sh;

universal UUT (si, D, Q, sh, load, clk);

initial begin
    #0  clk = 0;  D = 4'b0011; load = 0;  si = 1;  sh = 0;
    #100    load = 1;
    #100    sh = 1; load = 0;
    #100    si = 2;
    #100    sh = 0; load = 1;
    #100    D = 4'b0110;
    #100    load = 0;
    #100    D = 4'b1100;
    end
    
    always #half_period clk = ~clk;
    
    initial #1000 $stop;
endmodule
