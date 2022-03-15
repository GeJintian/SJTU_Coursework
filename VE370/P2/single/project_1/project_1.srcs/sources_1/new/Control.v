`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/06/29 22:38:45
// Design Name: 
// Module Name: Control
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


module Control(
clk,instruction, RegDst, Jump, BranchEq, BranchNe, MemRead, MemtoReg, ALUOp, MemWrite, ALUSrc, RegWrite
    );
    input   clk;
    input   [5:0]   instruction;
    output  reg  RegDst, Jump, BranchEq, MemRead, MemtoReg, MemWrite, ALUSrc, RegWrite, BranchNe;
    output  reg  [1:0]   ALUOp;
    //We need to support add, addi, sub, and, andi, or, slt, lw, sw, beq, bne, j
    //add, sub, and, or, slt are R-types. The others need to be considered separately.
    //They are: addi, andi, lw, sw, beq, bne, j
    

    always @ (instruction) begin
        case (instruction)
            6'b000000: begin//R-type
                RegDst = 1;
                Jump = 0;
                BranchEq = 0;
                BranchNe = 0;
                MemRead = 0;
                MemtoReg = 0;
                MemWrite = 0;
                MemWrite = 0;
                ALUSrc = 0;
                RegWrite = 1;
                ALUOp = 2'b10;
                end
            6'b001000: begin//addi
                RegDst = 0;
                Jump = 0;
                BranchEq = 0;
                BranchNe = 0;
                MemRead = 0;
                MemtoReg = 0;
                MemWrite = 0;
                MemWrite = 0;
                ALUSrc = 1;
                RegWrite = 1;
                ALUOp = 2'b00;
            end
            6'b001100: begin//andi
                RegDst = 0;
                Jump = 0;
                BranchEq = 0;
                BranchNe = 0;
                MemRead = 0;
                MemtoReg = 0;
                MemWrite = 0;
                ALUSrc = 1;
                RegWrite = 1;
                ALUOp = 2'b11;
            end
            6'b100011: begin//lw
                RegDst = 0;
                Jump = 0;
                BranchEq = 0;
                BranchNe = 0;
                MemRead = 1;
                MemtoReg = 1;
                MemWrite = 0;
                ALUSrc = 1;
                RegWrite = 1;
                ALUOp = 2'b00;
            end
            6'b101011: begin//sw
                RegDst = 0;
                Jump = 0;
                BranchEq = 0;
                BranchNe = 0;
                MemRead = 0;
                MemtoReg = 0;
                MemWrite = 1;
                ALUSrc = 1;
                RegWrite = 0;
                ALUOp = 2'b00;
            end
            6'b000100: begin//beq
                RegDst = 0;
                Jump = 0;
                BranchEq = 1;
                BranchNe = 0;
                MemRead = 0;
                MemtoReg = 0;
                MemWrite = 0;
                ALUSrc = 0;
                RegWrite = 0;
                ALUOp = 2'b01;
            end
            6'b000101: begin//bne
                RegDst = 0;
                Jump = 0;
                BranchNe = 1;
                BranchEq = 0;
                MemRead = 0;
                MemtoReg = 0;
                MemWrite = 0;
                ALUSrc = 0;
                RegWrite = 0;
                ALUOp = 2'b01;
            end
            6'b000010: begin//j
                RegDst = 0;
                Jump = 1;
                BranchEq = 0;
                BranchNe = 0;
                MemRead = 0;
                MemtoReg = 0;
                MemWrite = 0;
                ALUSrc = 0;
                RegWrite = 0;
                ALUOp = 2'b00;
            end      
            default: begin
                RegDst = 0;
                Jump = 0;
                BranchEq = 0;
                BranchNe = 0;
                MemRead = 0;
                MemtoReg = 0;
                MemWrite = 0;
                ALUSrc = 0;
                RegWrite = 0;
                ALUOp = 2'b00;           
            end                                          
        endcase
    end
endmodule
