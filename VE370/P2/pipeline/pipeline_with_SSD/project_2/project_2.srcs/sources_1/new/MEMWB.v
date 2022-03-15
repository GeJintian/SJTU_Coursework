`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/08 14:36:54
// Design Name: 
// Module Name: MEMWB
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


module MEMWB(
MEM_RegWrite,MEM_MemtoReg,MEM_ReadData,MEM_ALUResult,MEM_WriteReg,WB_RegWrite,WB_MemtoReg,WB_ReadData,WB_ALUResult,
WB_WriteReg, clk
    );
    input MEM_RegWrite, MEM_MemtoReg, clk;
    input [31:0] MEM_ReadData, MEM_ALUResult;
    input [4:0] MEM_WriteReg;
    output reg WB_RegWrite, WB_MemtoReg;
    output reg [31:0] WB_ReadData, WB_ALUResult;
    output reg [4:0] WB_WriteReg;
    
    always @(posedge clk) begin
        WB_RegWrite <= MEM_RegWrite;
        WB_MemtoReg <= MEM_MemtoReg;
        WB_ReadData <= MEM_ReadData;
        WB_ALUResult <= MEM_ALUResult;
        WB_WriteReg <= MEM_WriteReg;
    end
endmodule
