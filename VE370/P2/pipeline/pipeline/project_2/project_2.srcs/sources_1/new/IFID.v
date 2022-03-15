`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/08 14:36:08
// Design Name: 
// Module Name: IFID
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


module IFID(
pcin, instructin, pcout, instructout, IFIDWrite, flush, clk
    );
    input   [31:0]  pcin, instructin;
    output  reg [31:0]  pcout, instructout;
    input   IFIDWrite, flush, clk;
    
    always @ (posedge clk) begin
        if (IFIDWrite == 1) begin
            pcout <= pcin;
            instructout <= instructin;
        end
        else if (flush == 1) begin
            pcout <= 32'b0;
            instructout <= 32'b0;
        end
        else begin
            pcout <= pcout;
            instructout <= instructout;
        end
    end
endmodule
