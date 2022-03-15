`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/06/29 22:39:12
// Design Name: 
// Module Name: SignExtend
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


module SignExtend(
Input,Output
    );
    input   [15:0]  Input;
    output  reg [31:0]  Output;
    always @ (Input) begin
        if  (Input[15] == 1)    Output <= {16'b1,Input};
        else    Output <= {16'b0,Input};
    end
endmodule
