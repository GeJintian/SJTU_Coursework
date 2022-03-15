`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/08 14:38:24
// Design Name: 
// Module Name: Detection
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


module Detection(
EX_MemRead, EX_rt, ID_rs, ID_rt, hazard, IFIDWrite, PCWrite
    );
    input   EX_MemRead;
    input   [4:0]   EX_rt, ID_rs, ID_rt;
    output  reg hazard, IFIDWrite, PCWrite;
    
    initial begin
        hazard = 0;
        IFIDWrite = 1;
        PCWrite = 1;
    end
    always @ (*) begin
        if (EX_MemRead && ((EX_rt == ID_rs)||(EX_rt == ID_rt))) begin
            hazard = 1;
            IFIDWrite = 0;
            PCWrite = 0;
        end
        else begin
            hazard = 0;
            IFIDWrite = 1;
            PCWrite = 1;        
        end
    end
endmodule
