`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/08 14:32:22
// Design Name: 
// Module Name: DataMem
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


module DataMem(
clk, Address, ReadData, WriteData, MemRead, MemWrite
    );
    input   [31:0]  Address, WriteData;
    input   MemRead, MemWrite,clk;
    output  [31:0]  ReadData;
    integer     i;
    reg     [31:0]  memory  [9:0];
    wire    [31:0]  address;
    
    assign address = Address >> 2;
    
    initial begin
        for (i = 0; i < 10; i = i + 1)
            memory[i] = 32'b0;
    end
    
    always @ (negedge clk) begin
        if (MemWrite == 1) begin
            memory[address] = WriteData;
        end
    end
    assign ReadData = (MemRead == 1) ? memory[address] : 32'b0;
endmodule
