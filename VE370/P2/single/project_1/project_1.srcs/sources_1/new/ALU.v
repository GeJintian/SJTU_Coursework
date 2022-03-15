`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/06/29 22:36:09
// Design Name: 
// Module Name: ALU
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

module ALU(
rs,rt,control,result,zero
    );
    input   [31:0]  rs, rt;
    input   [3:0]   control;
    output  zero;
    output  reg [31:0]  result;
    
    always @ (rs or rt or control) begin
    case (control)
                4'b0010: result <= rs + rt;//ADD
                4'b0110: result <= rs - rt;//SUB
                4'b0000: result <= rs & rt;//AND
                4'b0001: result <= rs | rt;//OR
                4'b0111: result <= (rs<rt) ? 1 : 0;//SLT
                4'b1100: result <= ~(rs|rt);//NOR
                default: result <= 0;
    endcase
    end
    assign zero = (result == 0);
endmodule
