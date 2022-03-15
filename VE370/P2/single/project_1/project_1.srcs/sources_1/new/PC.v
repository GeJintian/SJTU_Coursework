`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/03 16:31:14
// Design Name: 
// Module Name: PC
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


module PC(
clk, pcin, pcout
    );
    input clk;
    input   [31:0] pcin;
    output   reg [31:0] pcout;
    initial begin
        pcout = 32'b0;
    end
    always @ (posedge clk) begin
        pcout <= pcin;
    end
endmodule
