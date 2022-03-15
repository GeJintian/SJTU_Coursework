`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/22 15:58:18
// Design Name: 
// Module Name: tb_1b
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

//Test bench for 2-way, write through
module tb_1b;
reg ReadOWrite;
reg [9:0]   address;
reg [31:0]  WriteData;
wire    [31:0]  ReadData;
wire    hit;
reg clk;
Cache_1b   UUT (ReadOWrite, address, WriteData, ReadData, hit, clk);
//For directed-map, 4-words, 4-block cache, add[1:0] are bits-offset, add[3:2] are word-offset, add[5:4] are index, add[9:6] are tag.
initial begin
    clk = 1;
    #0  ReadOWrite = 0; address = 10'b0000000000; //1
    #8  $display("Data is %H, hit is %d", ReadData, hit); 
    //$display("Address is %b", UUT.address_mem);
    #2 ReadOWrite = 1; address = 10'b0000000000;WriteData = 8'b11111111; //2
    #8 $display("Data is %H, hit is %d, mem is %H", ReadData, hit, UUT.main_mem.main_memory[0]);
    //$display("Address is %b", UUT.address_mem);
    #2 ReadOWrite = 0; address = 10'b0000000000; //3
    #8  $display("Data is %H, hit is %d, mem is %H", ReadData, hit, UUT.main_mem.main_memory[0]); 
    //$display("Address is %b", UUT.address_mem);
    #2 ReadOWrite = 0; address = 10'b1000000000; //4
    #8  $display("Data is %H, hit is %d, mem is %H", ReadData, hit, UUT.main_mem.main_memory[0]); 
        //$display("Address is %b", UUT.address_mem);
    #2 ReadOWrite = 0; address = 10'b0000000000; //5
    #8  $display("Data is %H, hit is %d, mem is %H", ReadData, hit, UUT.main_mem.main_memory[0]); 
    //$display("Address is %b", UUT.address_mem);
    #2 ReadOWrite = 0; address = 10'b1100000000; //6
    #8  $display("Data is %H, hit is %d", ReadData, hit); 
    //$display("Address is %b", UUT.address_mem);
    #2 ReadOWrite = 0; address = 10'b1000000000; //7
    #8  $display("Data is %H, hit is %d, mem is %H", ReadData, hit, UUT.main_mem.main_memory[0]); 
    //$display("Address is %b", UUT.address_mem);
end
always #5   clk = ~clk;
endmodule
