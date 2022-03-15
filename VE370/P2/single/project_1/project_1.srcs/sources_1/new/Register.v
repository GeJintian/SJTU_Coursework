`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/06/29 22:37:32
// Design Name: 
// Module Name: Register
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


module Register(
clk, Readregister1, Readregister2, Writeregister, Writedata, Readdata1, Readdata2, RegWrite
    );
    input   clk, RegWrite;
    input   [4:0]   Readregister1, Readregister2, Writeregister;
    input   [31:0]  Writedata;
    output  [31:0]  Readdata1, Readdata2;
    
    reg [31:0]  memory  [31:0];
    integer i;
    
    initial begin
        for (i = 0; i < 32; i = i + 1) begin
            memory[i] = 32'b0;
        end
     end
     assign Readdata1 = memory[Readregister1];
     assign Readdata2 = memory[Readregister2];
     
     always @ (Writedata) begin
        if(RegWrite == 1) memory[Writeregister] <= Writedata;
        memory[0] <= 32'b0;
     end
     
    
endmodule
