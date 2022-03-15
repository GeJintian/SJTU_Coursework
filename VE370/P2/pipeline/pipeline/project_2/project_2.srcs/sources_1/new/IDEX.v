`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/08 14:36:17
// Design Name: 
// Module Name: IDEX
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


module IDEX(
ID_RegWrite,  ID_MemRead, ID_MemWrite, ID_MemtoReg, ID_RegDst, ID_ALUOp,
ID_ALUSrc, ID_Jump, ID_pc, ID_RegRs, ID_RegRt, ID_SignExt, ID_Rs, ID_Rt, ID_Rd, EX_RegWrite,  EX_MemRead, EX_MemWrite, EX_MemtoReg, EX_RegDst, EX_ALUOp, EX_ALUSrc, EX_Jump, EX_pc, EX_RegRs,
EX_RegRt, EX_SignExt, EX_Rs, EX_Rt, EX_Rd,clk
    );
    input   ID_RegWrite,  ID_MemRead, ID_MemWrite, ID_MemtoReg, ID_RegDst, ID_ALUSrc, ID_Jump, clk;
    input   [1:0]   ID_ALUOp;
    input   [31:0] ID_pc, ID_RegRs, ID_RegRt, ID_SignExt;
    input [4:0] ID_Rs, ID_Rt, ID_Rd;
    output  reg EX_RegWrite,  EX_MemRead, EX_MemWrite, EX_MemtoReg, EX_RegDst, EX_ALUSrc, EX_Jump;
    output  reg [1:0]   EX_ALUOp;
    output  reg [31:0]  EX_pc, EX_RegRs, EX_RegRt, EX_SignExt;
    output  reg [4:0]   EX_Rs, EX_Rt, EX_Rd;
    
    always @ (posedge clk) begin
        EX_RegWrite <= ID_RegWrite;

        EX_MemRead <= ID_MemRead;
        EX_MemWrite <= ID_MemWrite;
        EX_MemtoReg <= ID_MemtoReg;
        EX_RegDst <= ID_RegDst;
        EX_ALUSrc <= ID_ALUSrc;
        EX_Jump <= ID_Jump;
        EX_ALUOp <= ID_ALUOp;
        EX_pc <= ID_pc;
        EX_RegRs <= ID_RegRs;
        EX_RegRt <= ID_RegRt;
        EX_SignExt <= ID_SignExt;
        EX_Rs <= ID_Rs;
        EX_Rt <= ID_Rt;
        EX_Rd <= ID_Rd;
    end
endmodule
