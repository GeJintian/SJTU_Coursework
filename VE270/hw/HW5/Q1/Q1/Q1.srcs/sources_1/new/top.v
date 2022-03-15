`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/06/16 13:48:03
// Design Name: 
// Module Name: top
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


module top(F, A, B, sel);
input   [31:0]  A, B;
input   sel;
output  [31:0]  F;
reg [31:0]  F;

always  @(A, B, sel)    begin
    case    (sel)
        1'b0:   F = A;
        1'b1:   F = B;
        default F = 0;
    endcase
end
endmodule
