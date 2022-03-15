`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/06/16 15:30:05
// Design Name: 
// Module Name: four_D_f
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
module D_f(q, i, clk, reset);
input   i, clk, reset;
output  q;

reg q;

always @ (posedge clk)
begin
    if (reset == 1) q <= 0;
    else q <= i;
end
endmodule



module four_D_f(O, I, CLK, reset);
input [3:0] I;
input   CLK, reset;
output [3:0]    O;

D_f D3 (O[3], I[3], CLK, reset);
D_f D2 (O[2], I[2], CLK, reset);
D_f D1 (O[1], I[1], CLK, reset);
D_f D0 (O[0], I[0], CLK, reset);

endmodule
