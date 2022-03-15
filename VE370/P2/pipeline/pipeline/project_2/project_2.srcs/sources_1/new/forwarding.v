`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/09 00:08:56
// Design Name: 
// Module Name: forwarding
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


module forwarding(
WB_RegWrite, WB_WriteReg, MEM_RegWrite, MEM_WriteReg, EX_Rs, EX_Rt, ForwardA, ForwardB
    );
    input   WB_RegWrite, MEM_RegWrite;
    input   [4:0]   WB_WriteReg, MEM_WriteReg, EX_Rs, EX_Rt;
    output  reg [1:0]   ForwardA, ForwardB;
    
    initial begin
        ForwardA = 2'b00;
        ForwardB = 2'b00;
    end
    
    always @ (*) begin
        if (WB_RegWrite && (WB_WriteReg != 0) && (WB_WriteReg == EX_Rs) &&
         !(MEM_RegWrite && (MEM_WriteReg != 0) && (MEM_WriteReg == EX_Rs))) ForwardA = 2'b01;
        else if (MEM_RegWrite && (MEM_WriteReg != 0) && (MEM_WriteReg == EX_Rs)) ForwardA = 2'b10;
        else ForwardA = 2'b00;
        
        if (WB_RegWrite && (WB_WriteReg != 0) && (WB_WriteReg == EX_Rt) &&
        !(MEM_RegWrite && (MEM_WriteReg != 0) && (MEM_WriteReg == EX_Rt))) ForwardB = 2'b01;
        else if (MEM_RegWrite && (MEM_WriteReg != 0) && (MEM_WriteReg == EX_Rt)) ForwardB = 2'b10;
        else ForwardB = 2'b00;
    end
endmodule
