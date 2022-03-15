`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/07/13 21:18:13
// Design Name: 
// Module Name: FSM
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

module scanner(clk, reset, row, col, O, anode1, anode2, anode3, anode4);
input clk,reset;
input   [3:0]   row;
output anode1, anode2, anode3, anode4;
output  [3:0]   col;
output  [6:0]   O;
wire    clk1, clkdivider;
wire    [3:0]code;

//divider10_4 d1(clk, clkdivider, reset);
divider10_4 d2(clk, clk1, reset);
FSM fsm(clk1, reset, row, col, code);
lab5 ssd(clk, O,anode1, anode2, anode3, anode4, reset, code);

endmodule

module FSM(clock, reset, row, col, code);
input   clock, reset;
input   [3:0]   row;
output  [3:0]   col; 
output  [3:0]   code;   


reg [3:0]   col, code;
reg [2:0]   curr_state, next_state;
wire _xor;

parameter s0 = 3'b000;
parameter s1 = 3'b001;
parameter s2 = 3'b010;
parameter s3 = 3'b011;
parameter s4 = 3'b100;
parameter s5 = 3'b101;

assign _xor = |row;

always@(posedge clock or posedge reset)//state change
    if(reset == 1) curr_state<= s0;
    else    curr_state <= next_state;
always @ (curr_state or _xor)//next state
    case(curr_state)
    s0: begin
    if (_xor == 0) next_state <= s0; else
    if (_xor == 1) next_state <= s1; else
                   next_state <= s0;
        col = 4'b1111;
                   end
    s1: begin
    if (_xor == 0) next_state <= s2; else
    if (_xor == 1) next_state <= s5; else
                   next_state <= s0;
        col = 4'b0001;
                       end
    s2: begin
    if (_xor == 0) next_state <= s3; else
    if (_xor == 1) next_state <= s5; else
                       next_state <= s0;
        col = 4'b0010;
                       end
    s3: begin
    if (_xor == 0) next_state <= s4; else
    if (_xor == 1) next_state <= s5; else
                   next_state <= s0;
        col = 4'b0100;
                       end
    s4: begin
    if (_xor == 0) next_state <= s0; else
    if (_xor == 1) next_state <= s5; else
                   next_state <= s0;
        col = 4'b1000;
                       end
    s5: begin
    if (_xor == 0) next_state <= s0; else
    if (_xor == 1) next_state <= s5; else
                   next_state <= s0;
        col = 4'b1111;
                       end
    default:           next_state <= s0;
    endcase
always @(posedge clock or posedge reset)begin//code output
    if(reset == 1) code <= 4'b0000;
    else if (_xor == 0) code<=4'b0000;
    else 
    case(curr_state)
        s0:
            case(row)
            4'b0001:code<=4'b0000;
            4'b0010:code<=4'b0000;
            4'b0100:code<=4'b0000;
            4'b1000:code<=4'b0000;
            default:code<=4'b0000;
            endcase
        s1:
            case(row)
            4'b0001:code<=4'b0000;//0
            4'b0010:code<=4'b0100;//4
            4'b0100:code<=4'b1000;//8
            4'b1000:code<=4'b1100;//12
            default:code<=4'b0000;
            endcase
        s2:
            case(row)
            4'b0001:code<=4'b0001;//1
            4'b0010:code<=4'b0101;//5
            4'b0100:code<=4'b1001;//8
            4'b1000:code<=4'b1101;//13
            default:code<=4'b0000;
            endcase
        s3:
            case(row)
            4'b0001:code<=4'b0010;
            4'b0010:code<=4'b0110;
            4'b0100:code<=4'b1010;
            4'b1000:code<=4'b1110;
            default:code<=4'b0000;
            endcase
        s4:
            case(row)
            4'b0001:code<=4'b0011;
            4'b0010:code<=4'b0111;
            4'b0100:code<=4'b1011;
            4'b1000:code<=4'b1111;
            default:code<=4'b0000;
            endcase
        s5:code<=code;
        default: code<=4'b0000;
    endcase
end
endmodule








//Lab5 part
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

module lab5(clk, O,anode1, anode2, anode3, anode4, rst, in);
input clk,rst;
input   [3:0] in;
output [6:0] O; 
output  anode1, anode2, anode3, anode4;
wire  clkdivider, clka;
reg [6:0] O;
reg anode1 = 0, anode2 = 1;

divider10_5 d4 (clk, clka,rst);//clka for anode

always @ (posedge clka) begin
anode1 <= ~anode1;
anode2 <= ~anode2;
if(anode2 == 0)
case (in)
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
        4'b1010: O = 7'b0000001;//10
        4'b1011: O = 7'b1001111;//11
        4'b1100: O = 7'b0010010;//12
        4'b1101: O = 7'b0000110;//13
        4'b1110: O = 7'b1001100;//14
        4'b1111: O = 7'b0100100;//15
endcase
else if(anode1 == 0)
case (in)
        4'b0000: O = 7'b0000001;//0
        4'b0001: O = 7'b0000001;//1
        4'b0010: O = 7'b0000001;//2
        4'b0011: O = 7'b0000001;//3
        4'b0100: O = 7'b0000001;//4
        4'b0101: O = 7'b0000001;//5
        4'b0110: O = 7'b0000001;//6
        4'b0111: O = 7'b0000001;//7
        4'b1000: O = 7'b0000001;//8
        4'b1001: O = 7'b0000001;//9
        4'b1010: O = 7'b1001111;//10
        4'b1011: O = 7'b1001111;//11
        4'b1100: O = 7'b1001111;//12
        4'b1101: O = 7'b1001111;//13
        4'b1110: O = 7'b1001111;//14
        4'b1111: O = 7'b1001111;//15
endcase
end
assign anode3 = 1;
assign anode4 = 1;
endmodule



