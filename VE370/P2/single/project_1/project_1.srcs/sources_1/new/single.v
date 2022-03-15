`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/06/29 21:59:01
// Design Name: 
// Module Name: single
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
module single(
clk
    );
    input   clk;
    wire    [31:0]  pcin, pcout, instruction;
    wire    [4:0]   Readregister1, Readregister2, Writeregister;
    wire    [5:0]   Ctrlins;
    wire    [31:0]  Readdata1, Readdata2, Writedata, extendoutput, rt, ALUresult, memRead;
    wire    RegDst, Jump, MemRead, MemtoReg, MemWrite, ALUSrc, RegWrite, zero, BranchEq, BranchNe;
    wire    [1:0]   ALUOp;
    wire    [15:0]  extendinput;
    wire    [5:0]   funct;
    wire    [3:0]   ALUcode;

    
    //wire for pc address
    wire    [31:0]  pcadd, pcjump, pcbranch, signshift, pcmux;
    wire    isbranch;
    
    PC pc(clk, pcin, pcout);
    
    IM im(pcout, instruction);
    
    //For control
    assign  Ctrlins = instruction[31:26];
    Control crtl(clk,Ctrlins, RegDst, Jump, BranchEq, BranchNe, MemRead, MemtoReg, ALUOp, MemWrite, ALUSrc, RegWrite);
    
    //For register
    assign  Readregister1 = instruction[25:21];
    assign  Readregister2 = instruction[20:16];
    assign  Writeregister = (RegDst == 0) ? instruction[20:16] : instruction[15:11];
    Register register_file(clk, Readregister1, Readregister2, Writeregister, Writedata, Readdata1, Readdata2, RegWrite);
    
    //For signextend
    assign  extendinput = instruction[15:0];
    SignExtend signex(extendinput, extendoutput);
    
    //For alu control
    assign  funct = instruction[5:0];
    ALUcontrol aluctrl(funct, ALUOp, ALUcode);
    
    //For alu
    assign  rt = (ALUSrc == 0) ? Readdata2 : extendoutput;
    ALU alu(Readdata1, rt, ALUcode, ALUresult, zero);
    
    //For data memory
    DataMem dm(clk, ALUresult, memRead, Readdata2, MemRead, MemWrite);
    
    assign  Writedata = (MemtoReg == 1) ? memRead : ALUresult;
    
    //For pc address
    assign  isbranch = (BranchEq & zero) | (BranchNe & ~zero);
    assign  pcadd = pcout + 4;
    assign  signshift = extendoutput << 2;
    assign  pcbranch = pcadd + signshift;
    assign  pcjump = {pcadd[31:28], instruction[25:0], 2'b00};
    assign  pcmux = (isbranch == 0)? pcadd : pcbranch;
    assign  pcin = (Jump == 1)? pcjump : pcmux;
    
    
    
endmodule
