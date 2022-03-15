`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/09 18:59:43
// Design Name: 
// Module Name: SSD
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
module divider10_5 (clock,O);
  parameter N = 17;
  input 	clock;
  output    O;
  reg		[N-1:0] 	Q;
  reg   O;
  always @  (posedge clock) begin
    if(Q == 100000)  begin
      O <= 1;
      Q <= 0;
    end
    else begin
    Q <= Q + 1;
    O = 0;
    end
    end
/*        always @ (*)
    if(rst == 1) Q<=0;*/
endmodule 


module divider10_4 (clock,O);
  parameter N = 14;
  input 	clock;
  output    O;
  reg		[N-1:0] 	Q;
  reg   O;
  always @  (posedge clock) begin;
    if(Q == 10000)  begin
      O <= 1;
      Q <= 0;
    end
    else begin
    Q <= Q + 1;
    O = 0;
    end
    end
    /*always @ (*)
    if(rst == 1) Q<=0;*/
endmodule 

module SSD(clk, Pipe_go, O, anode1, anode2, anode3, anode4, Address);
input clk,Pipe_go;
input   [4:0]   Address;
output [6:0] O; 
output  anode1, anode2, anode3, anode4;
wire clk1, clk2, clkdivider, clka;
reg [6:0] O;
reg anode1 = 0, anode2 = 1, anode3=1,anode4=1;
wire    [31:0]  register;
wire    [3:0]   Q1,Q2,Q3,Q4;
integer i = 0;

divider10_4 d1 (clk, clkdivider);
divider10_4 d2 (clkdivider, clk1);//clk1 for 1
divider10_5 d3 (clkdivider, clk2);//clk2 for 10
divider10_5 d4 (clk, clka);//clka for anode

pipeline pip(Pipe_go, Address, register);

assign  Q1 = register[3:0];//for the first bit
assign  Q2 = register[7:4];//For second bit
assign  Q3 = register[11:8];
assign  Q4 = register[15:12];

always @ (posedge clka) begin
if (i == 4) i = 0;
i <= i + 1;
if(i == 0)begin
    anode1 = 0;
    anode2 = 1;
    anode3 = 1;
    anode4 = 1;
end
else if(i == 1)begin
    anode1 = 1;
    anode2 = 0;
    anode3 = 1;
    anode4 = 1;
end
else if(i == 2)begin
    anode1 = 1;
    anode2 = 1;
    anode3 = 0;
    anode4 = 1;
end
else if(i == 3)begin
    anode1 = 1;
    anode2 = 1;
    anode3 = 1;
    anode4 = 0;
end
if(anode1 == 0)
case (Q1)
        4'h0: O = 7'b0000001;//0
        4'h1: O = 7'b1001111;//1
        4'h2: O = 7'b0010010;//2
        4'h3: O = 7'b0000110;//3
        4'h4: O = 7'b1001100;//4
        4'h5: O = 7'b0100100;//5
        4'h6: O = 7'b0100000;//6
        4'h7: O = 7'b0001111;//7
        4'h8: O = 7'b0000000;//8
        4'h9: O = 7'b0000100;//9
        4'ha: O = 7'b0001000;//a
        4'hb: O = 7'b1100000;//b
        4'hc: O = 7'b0110001;//c
        4'hd: O = 7'b1000010;//d
        4'he: O = 7'b0110000;//e
        4'hf: O = 7'b0111000;//f
endcase
else if(anode2 == 0)
case (Q2)
        4'h0: O = 7'b0000001;//0
        4'h1: O = 7'b1001111;//1
        4'h2: O = 7'b0010010;//2
        4'h3: O = 7'b0000110;//3
        4'h4: O = 7'b1001100;//4
        4'h5: O = 7'b0100100;//5
        4'h6: O = 7'b0100000;//6
        4'h7: O = 7'b0001111;//7
        4'h8: O = 7'b0000000;//8
        4'h9: O = 7'b0000100;//9
        4'ha: O = 7'b0001000;//a
        4'hb: O = 7'b1100000;//b
        4'hc: O = 7'b0110001;//c
        4'hd: O = 7'b1000010;//d
        4'he: O = 7'b0110000;//e
        4'hf: O = 7'b0111000;//f
endcase
else if(anode3 == 0)
case (Q3)
        4'h0: O = 7'b0000001;//0
        4'h1: O = 7'b1001111;//1
        4'h2: O = 7'b0010010;//2
        4'h3: O = 7'b0000110;//3
        4'h4: O = 7'b1001100;//4
        4'h5: O = 7'b0100100;//5
        4'h6: O = 7'b0100000;//6
        4'h7: O = 7'b0001111;//7
        4'h8: O = 7'b0000000;//8
        4'h9: O = 7'b0000100;//9
        4'ha: O = 7'b0001000;//a
        4'hb: O = 7'b1100000;//b
        4'hc: O = 7'b0110001;//c
        4'hd: O = 7'b1000010;//d
        4'he: O = 7'b0110000;//e
        4'hf: O = 7'b0111000;//f
endcase
else if(anode4 == 0)
case (Q4)
        4'h0: O = 7'b0000001;//0
        4'h1: O = 7'b1001111;//1
        4'h2: O = 7'b0010010;//2
        4'h3: O = 7'b0000110;//3
        4'h4: O = 7'b1001100;//4
        4'h5: O = 7'b0100100;//5
        4'h6: O = 7'b0100000;//6
        4'h7: O = 7'b0001111;//7
        4'h8: O = 7'b0000000;//8
        4'h9: O = 7'b0000100;//9
        4'ha: O = 7'b0001000;//a
        4'hb: O = 7'b1100000;//b
        4'hc: O = 7'b0110001;//c
        4'hd: O = 7'b1000010;//d
        4'he: O = 7'b0110000;//e
        4'hf: O = 7'b0111000;//f
endcase
end

endmodule
