`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/07/22 14:24:44
// Design Name: 
// Module Name: lab7
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


module lab7(number,clk, rst,to_start, equal, O, anode1, anode2, anode3, anode4, overflow,add,roller,endroll, reset);
input clk, rst,equal, to_start;
input   [3:0]   number;
output anode1, anode2, anode3, anode4, overflow, add,roller,endroll, reset;
output [6:0]   O;
wire    clk10_4,clk10_8;
wire    [3:0] code1, code2, code3, code4;
wire    [4:0]   sum;
divider10_4 d1(clk,clk10_4,rst); 
divider10_4 d2(clk10_4,clk10_8,rst);

FSM fsm(clk10_4, endroll, rst, to_start,roller,add,reset);
adder ad(add,equal, number, sum, overflow,rst);
roll ro(clk10_8,roller,code1, code2, code3, code4, endroll);
lab5 l(clk, O,anode1, anode2, anode3, anode4, rst, code1, code2, code3, code4, sum, add, roller);



endmodule

//SSD module from lab5
module lab5(clk, O,anode1, anode2, anode3, anode4, rst, code1, code2, code3, code4, sum, add, roller);
input clk,rst, add, roller;
input   [3:0]   code1, code2, code3, code4, sum;
output [6:0] O; 
output  anode1, anode2, anode3, anode4;
wire clk1, clk2, clkdivider, clka;
reg [6:0] O;
reg anode1 = 0, anode2 = 1, anode3 = 1, anode4 = 1;
reg [1:0]   count = 2'b00;



divider10_5 d4 (clk, clka,rst);//clka for anode


always @ (posedge clka) begin
if(count == 2'b11) count <= 2'b00;
else count <= count + 1;
case(count)
2'b00:begin
          anode1 = 0;
          anode2 = 1;
          anode3 = 1;
          anode4 = 1;
       end
2'b01:begin
          anode1 = 1;
          anode2 = 0;
          anode3 = 1;
          anode4 = 1;
       end
2'b10:begin
          anode1 = 1;
          anode2 = 1;
          anode3 = 0;
          anode4 = 1;
       end
2'b11:begin
          anode1 = 1;
          anode2 = 1;
          anode3 = 1;
          anode4 = 0;
       end
endcase
if(roller == 1) begin
if(anode1 == 0)
case (code1)
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
else if(anode2 == 0)
case (code2)
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
else if(anode3 == 0)
case (code3)
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
else if(anode4 == 0)
case (code4)
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
end
else if(add == 1)begin
if(anode1 == 0)
case (sum[3])
        1'b1: O = 7'b1111110;//-
        1'b0: O = 7'b1111111;//none
endcase
else if(anode2 == 0)begin
    if(sum[3] == 0)begin//positive
    case (sum[2:0])
        3'b000: O = 7'b0000001;//0
        3'b001: O = 7'b1001111;//1
        3'b010: O = 7'b0010010;//2
        3'b011: O = 7'b0000110;//3
        3'b100: O = 7'b1001100;//4
        3'b101: O = 7'b0100100;//5
        3'b110: O = 7'b0100000;//6
        3'b111: O = 7'b0001111;//7
endcase
    end
    else begin//negative
        case (sum[2:0])
        3'b111: O = 7'b1001111;//1
        3'b110: O = 7'b0010010;//2
        3'b101: O = 7'b0000110;//3
        3'b100: O = 7'b1001100;//4
        3'b011: O = 7'b0100100;//5
        3'b010: O = 7'b0100000;//6
        3'b001: O = 7'b0001111;//7
        3'b000: O = 7'b0000000;//8
endcase
    end
end
else if(anode3 == 0)
O = 7'b1111111;
else if(anode4 == 0)
O = 7'b1111111;
end
else O = 7'b1111111;
end

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
//10^4 divider
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
endmodule 

//module for roll
module roll(clk,start,code1, code2, code3, code4, endroll);
    input clk, start;
    output reg [3:0]   code1;
    output reg [3:0]   code2;
    output reg [3:0]   code3;
    output reg [3:0]   code4;
    output reg endroll = 0;
    reg [47:0]  studentnumber = {4'b0101, 4'b0001, 4'b0111, 4'b0000, 4'b0010, 4'b0001, 4'b1001, 4'b0001, 4'b0001, 4'b0001, 4'b0100, 4'b0010};
    always@(posedge clk)begin
    if(start == 1 & endroll == 0)begin
    code1 <= studentnumber[47:44];
    code2 <= studentnumber[43:40];
    code3 <= studentnumber[39:36];
    code4 <= studentnumber[35:32];
    studentnumber[47:4] <= studentnumber[43:0];
    studentnumber[3:0] <= studentnumber[47:44];
    if(code3 == 4'b0100) endroll <=1;
    end
    end
endmodule

//module for adder
module adder(add,equal, number, sum, overflow,reset);
    input equal,add,reset;
    input   [3:0]   number;
    output reg [4:0]   sum = 5'b00000;
    output reg overflow;
    always@(posedge equal or posedge reset)begin
    if(reset == 1) begin
    sum = 5'b00000;
    overflow =0;
    end
    else if(add == 1) begin
    sum = number + sum;
    if(sum[4]^sum[3] == 1)overflow = 1;
    else overflow =0;
    end
    else sum <= sum;
    end
endmodule

module FSM(clk, endroll, rst, to_start,roller,add,reset);
input   clk, endroll, rst, to_start;
output reg roller;
output reg add;
output reg reset;
reg   [1:0] curr_state, next_state;
parameter   init = 2'b00;
parameter   to_roll = 2'b01;
parameter   to_wait = 2'b10;
parameter   to_add = 2'b11;

always @ (posedge clk)begin 
curr_state <= next_state;
end
always @ (curr_state or endroll or rst or to_start) begin
case(curr_state)
init:   begin
        add <= 0;
        roller <= 0;
        reset <= 0;
        if(to_start == 1) next_state <= to_roll;
        else next_state <= init;
        end
to_roll:    begin
        add <=0;
        roller <= 1;
        reset <=0;
        if(endroll == 1) next_state <= to_wait;
        else next_state <= to_roll;
        end
to_wait:    begin
        add <=0;
        roller<=0;
        reset <= 1;
        next_state <= to_add;
        end
to_add:     begin
        add <= 1;
        roller <=0;
        reset <= 0;
        if(rst == 1) next_state <= to_wait;
        else next_state <= to_add;
        end
endcase
end
endmodule