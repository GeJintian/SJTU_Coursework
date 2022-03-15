`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/08 14:28:02
// Design Name: 
// Module Name: pipeline
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


module pipeline(
clk
    );
    input   clk;
    
    wire    [31:0]  pcin, pcout, pcadd4, IF_instruct, ID_pc, ID_instruct, ID_data1, ID_data2, WB_ALUResult, 
                    ID_SignExt, EX_SignExt, Jump_pc, Branch_pc, pc_result1, EX_pc, EX_RegRt, EX_RegRs,
                    ALU1, ALU2,ALU21, MEM_ALUResult, WB_WriteData, EX_ALUResult, MEM_RegRt, MEM_ReadData,WB_ReadData;
    wire    PCWrite, IFIDWrite, IF_Flush, RegDst, Jump, BranchEq, BranchNe, MemRead, MemtoReg, MemWrite, ALUSrc, RegWrite, ID_Flush, EX_Flush, 
             hazard, WB_RegWrite, is_branch, EX_RegWrite, EX_BranchEq, EX_BranchNe, EX_MemRead, EX_MemWrite,
             EX_MemtoReg, EX_RegDst,EX_ALUSrc, EX_Jump, EX_Zero, MEM_RegWrite, MEM_BranchEq, MEM_BranchNEq, 
             MEM_MemRead, MEM_MemWrite, MEM_MemtoReg, MEM_Jump, MEM_Zero,  WB_MemtoReg;
    wire    [4:0]   ID_rs, ID_rt, ID_rd, WB_WriteReg,EX_Rs, EX_Rt, EX_Rd, EX_WriteReg,MEM_WriteReg;
    wire    [1:0]   ALUOp,EX_ALUOp, ForwardA, ForwardB;
    wire    [3:0]   ALUControl;

    
    //IF stage
    PC pc(clk, pcin, pcout, PCWrite);
    assign pcadd4 = pcout + 4;
    IM im(pcout, IF_instruct);
    
    //IFID
    IFID ifid(pcadd4, IF_instruct, ID_pc, ID_instruct, IFIDWrite, IF_Flush, clk);
    
    //ID stage
    Control ctrl(clk,ID_instruct[31:26], RegDst, Jump, BranchEq, BranchNe, MemRead, MemtoReg, ALUOp, MemWrite,
                    ALUSrc, RegWrite, IF_Flush, ID_Flush, EX_Flush, ID_data1, ID_data2, hazard);
                    
    assign  ID_rs = ID_instruct[25:21];
    assign  ID_rt = ID_instruct[20:16];
    assign  ID_rd = ID_instruct[15:11];
    Register register_file(clk, ID_rs, ID_rt, WB_WriteReg, WB_WriteData, ID_data1, ID_data2, WB_RegWrite);
    
    SignExtend signex(ID_instruct[15:0], ID_SignExt);
    
    assign  Branch_pc = ID_pc + (ID_SignExt<<2);
    assign  Jump_pc = {ID_pc[31:28], ID_instruct[25:0],2'b0};
    assign  pc_result1 = Jump? Jump_pc:Branch_pc;
    assign  is_branch = Jump||(BranchEq && (ID_data1 == ID_data2))||(BranchNe && !(ID_data1 == ID_data2));
    assign  pcin = is_branch ? pc_result1 : pcadd4;
    
    //IDEX
    IDEX idex(RegWrite,  MemRead, MemWrite, MemtoReg, RegDst, ALUOp,
        ALUSrc, Jump, ID_pc, ID_data1, ID_data2, ID_SignExt, ID_rs, ID_rt, ID_rd, EX_RegWrite, EX_MemRead, EX_MemWrite, EX_MemtoReg, EX_RegDst, EX_ALUOp, EX_ALUSrc, EX_Jump, EX_pc, EX_RegRs,
        EX_RegRt, EX_SignExt, EX_Rs, EX_Rt, EX_Rd,clk);
    
    //EX stage
    ALUcontrol aluctrl(EX_SignExt[5:0], EX_ALUOp, ALUControl);
    
    assign  ALU1 = ForwardA[1]?MEM_ALUResult:(ForwardA[0]?WB_WriteData:EX_RegRs);
    assign  ALU2 = ForwardB[1]?MEM_ALUResult:(ForwardB[0]?WB_WriteData:EX_RegRt);
    assign  ALU21 = EX_ALUSrc?EX_SignExt:ALU2;
    ALU alu(ALU1,ALU21,ALUControl,EX_ALUResult,EX_Zero);
    
    assign EX_WriteReg = EX_RegDst? EX_Rd:EX_Rt;
    
    //EXMEM
    EXMEM exmem(EX_RegWrite,    EX_MemRead,EX_MemWrite,EX_MemtoReg,EX_Jump,EX_Zero,
        EX_ALUResult,ALU2,EX_WriteReg,MEM_RegWrite,MEM_MemRead,MEM_MemWrite,
        MEM_MemtoReg,MEM_Jump,MEM_Zero,MEM_ALUResult,MEM_RegRt,    MEM_WriteReg,    clk);
        
    //MEM stage
    DataMem dm(clk, MEM_ALUResult, MEM_ReadData, MEM_RegRt, MEM_MemRead, MEM_MemWrite);
    
    //MEMWB
    MEMWB memwb(MEM_RegWrite,MEM_MemtoReg,MEM_ReadData,MEM_ALUResult,MEM_WriteReg,WB_RegWrite,WB_MemtoReg,WB_ReadData,WB_ALUResult,
        WB_WriteReg, clk);
    
    //WB stage
    assign WB_WriteData = WB_MemtoReg? WB_ReadData:WB_ALUResult;
    
    //Detection
    Detection Hazard(EX_MemRead, EX_Rt, ID_rs, ID_rt, hazard, IFIDWrite, PCWrite);
    
    //Forwarding
    forwarding forward(WB_RegWrite, WB_WriteReg, MEM_RegWrite, MEM_WriteReg, EX_Rs, EX_Rt, ForwardA, ForwardB);
endmodule
