`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/06/17 21:17:13
// Design Name: 
// Module Name: F_c
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


module F_c(upper, o, clear, set, clk, cnt);
input   clear, set, clk, cnt;
output  [3:0]   o;
output  upper;
reg [3:0]   o = 0;
reg upper;

always  @   (posedge    clk)
begin
    if (clear == 1) o <= 4'b0000;
    if (set == 1)   o <= 4'b1111;
    if (cnt == 1)   o <= o + 1;
end
always @ (*)
    upper = o[3];
endmodule
