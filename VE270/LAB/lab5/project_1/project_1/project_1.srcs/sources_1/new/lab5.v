`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/06/24 19:44:33
// Design Name: 
// Module Name: lab5
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
module counter1(clk, Q, rst);//count1
input clk, rst;
output  [3:0]   Q;
reg [3:0]   Q;
always @ (posedge clk or posedge rst) begin
    if(rst == 1) Q<=0;
    else if (Q == 4'b1001) Q <= 0;
    else Q <= Q+1;
    end

endmodule


module counter2(clk, Q, rst);//count10
input clk, rst;
output   [2:0]   Q;
reg [2:0]   Q;
always @ (posedge clk or posedge rst)
    if (rst == 1) Q<=0;
    else if (Q == 3'b101) Q <= 0;
    else Q <= Q+1;
endmodule

module divider10_5 (clock,O, rst);
  parameter N = 17;
  input 	clock ,rst;
  output    O;
  reg		[N-1:0] 	Q;
  reg   O;
  always @  (posedge clock or posedge rst) begin
    if(rst == 1) begin
    Q<=0;
    O = 0;
    end
    else if(Q == 100000)  begin
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


module divider10_4 (clock,O,rst);
  parameter N = 14;
  input 	clock, rst;
  output    O;
  reg		[N-1:0] 	Q;
  reg   O;
  always @  (posedge clock or posedge rst) begin;
    if(rst == 1) begin
    Q<=0;
    O = 0;
    end
    else if(Q == 10000)  begin
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


/*module divider10_3 (clock,O);
  parameter N = 10;
  input 	clock;
  output    O;
  reg		[N-1:0] 	Q;
  reg   O;
  always @  (posedge clock) begin
    if (O == 1'b1) Q <= 0;
    else Q <= Q + 1;
    if  (Q == 1000)    O <= 1;
    else    O <= 0;
    end
endmodule */




module lab5(clk, O,anode1, anode2, anode3, anode4, rst);
input clk,rst;
output [6:0] O; 
output  anode1, anode2, anode3, anode4;
wire clk1, clk2, clkdivider, clka;
reg [6:0] O;
reg anode1 = 0, anode2 = 1;
wire [3:0] Q1;
wire [2:0] Q2;

divider10_4 d1 (clk, clkdivider,rst);
divider10_4 d2 (clkdivider, clk1,rst);//clk1 for 1
divider10_5 d3 (clkdivider, clk2,rst);//clk2 for 10
divider10_5 d4 (clk, clka,rst);//clka for anode
counter1 c1 (clk1, Q1, rst);
counter2 c2 (clk2,Q2, rst);

always @ (posedge clka) begin
anode1 <= ~anode1;
anode2 <= ~anode2;
if(anode2 == 0)
case (Q1)
        4'b0000: O = 7'b0000001;//0
        4'b0001: O = 7'b1001111;//1
        4'b0010: O = 7'b0010010;//2
        4'b0011: O = 7'b0000110;//3
        4'b0100: O = 7'b1001100;//4
        4'b0101: O = 7'b0100100;//5
        4'b0110: O = 7'b0100000;//6
        4'b0111: O = 7'b0001111;//7
        4'b1000: O = 7'b0000000;//8
        4'b1001: O = 7'b0000100;//9
endcase
else if(anode1 == 0)
case (Q2)
        4'b000: O = 7'b0000001;//0
        4'b001: O = 7'b1001111;//1
        4'b010: O = 7'b0010010;//2
        4'b011: O = 7'b0000110;//3
        4'b100: O = 7'b1001100;//4
        4'b101: O = 7'b0100100;//5
endcase
end
assign anode3 = 1;
assign anode4 = 1;
endmodule
