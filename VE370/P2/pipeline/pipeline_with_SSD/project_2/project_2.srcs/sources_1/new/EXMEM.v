`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/08 14:36:38
// Design Name: 
// Module Name: EXMEM
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


module EXMEM(
EX_RegWrite,    EX_MemRead,EX_MemWrite,EX_MemtoReg,EX_Jump,EX_Zero,EX_ALUResult,
EX_RegRt,EX_WriteReg,MEM_RegWrite,MEM_MemRead,MEM_MemWrite,MEM_MemtoReg,MEM_Jump,
MEM_Zero,MEM_ALUResult,MEM_RegRt,    MEM_WriteReg,    clk
    );
    input   EX_RegWrite,  EX_MemRead, EX_MemWrite, EX_MemtoReg, EX_Jump, clk, EX_Zero;
    input [31:0]  EX_ALUResult, EX_RegRt ;
    input   [4:0]   EX_WriteReg;
    output reg MEM_RegWrite,  MEM_MemRead, MEM_MemWrite, MEM_MemtoReg, MEM_Jump, MEM_Zero;
    output reg [31:0]  MEM_ALUResult, MEM_RegRt;
    output reg [4:0] MEM_WriteReg;
    
    always @ (posedge clk) begin
        MEM_RegWrite <= EX_RegWrite;
        MEM_MemRead <= EX_MemRead;
        MEM_MemWrite <= EX_MemWrite;
        MEM_MemtoReg <= EX_MemtoReg;
        MEM_Jump <= EX_Jump;
        MEM_Zero <= EX_Zero;
        MEM_ALUResult <= EX_ALUResult;
        MEM_RegRt <= EX_RegRt;
        MEM_WriteReg <= EX_WriteReg;
    end
endmodule
