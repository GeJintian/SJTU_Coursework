`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/06/16 16:19:53
// Design Name: 
// Module Name: F_D_F
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

module F_D_F(x3, x2, x1, x0, Cloc);
output x3 = 0, x2 = 0, x1 = 0, x0 = 1;
input Cloc;
reg x3, x2, x1, x0;
wire f;

xor(f,x3,x0);
always @ (posedge Cloc)
begin

    x3 <= f;
    x2<=x3;
    x1<=x2;
    x0<=x1;
end


endmodule
