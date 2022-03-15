`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/06/16 16:31:25
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
parameter half_period = 50;
wire x3, x2, x1, x0, f;
reg Cloc;

F_D_F UUT (x3, x2, x1, x0, Cloc);

initial begin
    #0  Cloc = 0;
end

always #half_period Cloc = ~Cloc;
initial #1000   $stop;
endmodule
