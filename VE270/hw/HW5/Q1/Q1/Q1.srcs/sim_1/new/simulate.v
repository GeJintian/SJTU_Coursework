`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/06/16 14:06:35
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
wire [31:0] F;
reg [31:0]  A,B;
reg sel;
top UUT (F, A, B, sel);

initial begin
    #0 A = 8; B = 10; sel = 0;
    #200    sel = 1;
    #200    B = 15;
    #200    A=20;
    #200    sel = 0;
    #200    A = 3;
    #200    B = 5;
    #300    sel = 1;
end

initial #2000   $stop;
endmodule
