`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/08 14:31:40
// Design Name: 
// Module Name: ALUcontrol
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


module ALUcontrol(
funct, ALUOp, ALUControl
    );
    input   [5:0]   funct;
    input  [1:0]   ALUOp;
    output  reg  [3:0]   ALUControl;
    always @ (funct or ALUOp) begin
        case (ALUOp)
            2'b00: ALUControl <= 4'b0010;
            2'b01: ALUControl <= 4'b0110;
            2'b10: begin
                case (funct)
                    6'b100000: ALUControl <= 4'b0010;
                    6'b100010: ALUControl <= 4'b0110;
                    6'b100100: ALUControl <= 4'b0000;
                    6'b100101: ALUControl <= 4'b0001;
                    6'b101010: ALUControl <= 4'b0111;
                    default:;
                endcase
            end
            default: ALUControl <= 4'b0000;
        endcase
    end
endmodule
