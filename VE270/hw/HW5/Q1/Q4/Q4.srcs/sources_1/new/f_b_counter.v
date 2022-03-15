`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/06/17 20:53:06
// Design Name: 
// Module Name: f_b_counter
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


module f_b_counter(o, clear, set, clk, cnt);
input   clear, set, clk, cnt;
output  [3:0]   o;
reg [3:0]   o = 0;

always  @   (posedge    clk)
begin
    if (clear == 1) o <= 4'b0000;
    if (set == 1)   o <= 4'b1111;
    if (cnt == 1)   o <= o - 1;
end

endmodule
