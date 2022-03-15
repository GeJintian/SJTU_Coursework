`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/06/16 22:35:08
// Design Name: 
// Module Name: LAB4
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


module LAB4(clk, reset, Q, up, Q1);
input clk, reset, up;
output  [3:0]   Q;
output  [6:0]   Q1;
reg [3:0]   Q;
reg [6:0]   Q1;


always @ (posedge reset or posedge clk)
    if (reset == 1'b1) Q <= 0;
    else if (up == 1'b1)   Q <= Q + 1;
    else if (up == 1'b0)   Q <= Q-1;
    always @ (*)begin
    case (Q)
        4'b0000: Q1 = 7'b0000001;//
        4'b0001: Q1 = 7'b1001111;//1
        4'b0010: Q1 = 7'b0010010;//2
        4'b0011: Q1 = 7'b0000110;//3
        4'b0100: Q1 = 7'b1001100;//4
        4'b0101: Q1 = 7'b0100100;//5
        4'b0110: Q1 = 7'b0100000;//6
        4'b0111: Q1 = 7'b0001111;//7
        4'b1000: Q1 = 7'b0000000;//8
        4'b1001: Q1 = 7'b0000100;//9
        4'b1010: Q1 = 7'b0001000;//A
        4'b1011: Q1 = 7'b1100000;//b
        4'b1100: Q1 = 7'b0110001;//C
        4'b1101: Q1 = 7'b1000010;//d
        4'b1110: Q1 = 7'b0110000;//E
        4'b1111: Q1 = 7'b0111000;//F
    endcase
    end
endmodule
