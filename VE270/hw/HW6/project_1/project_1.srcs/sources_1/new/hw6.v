`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/07/02 14:28:58
// Design Name: 
// Module Name: universal
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
module Shift_reg(Q, Din, clock, Sl, Sh, L);
input   Din, clock, Sl, Sh, L;
output  Q;
reg Q;

always @ (posedge ~clock)begin
if(Sh == 1) Q<=Sl;
else if(L == 1) Q <= Din;
else Q <= Q;
end
endmodule



module universal(Sl, D, Q, Sh, L, CLK);
input   Sl, Sh, CLK, L;
input   [3:0]   D;
output  [3:0]   Q;

Shift_reg   Q3 (Q[3], D[3], CLK, Sl, Sh, L);
Shift_reg   Q2(Q[2], D[2], CLK, Q[3], Sh, L);
Shift_reg   Q1(Q[1], D[1], CLK, Q[2], Sh, L);
Shift_reg   Q0(Q[0], D[0], CLK, Q[1], Sh, L);
endmodule
