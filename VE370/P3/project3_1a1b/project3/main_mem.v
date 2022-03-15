`timescale 1ns / 1ps
module MainMemory(
    input readOrwrite, // read 0, write 1
    input [9:0]mem_address,
    input [127:0]mem_writedata,
    output [127:0]mem_readdata
);

integer i;
reg [31:0]main_memory[255:0];
initial begin
  for(i=0; i<254;i=i+1)
        main_memory[i] = 32'b0;
end
assign mem_readdata = {main_memory[{mem_address[9:4],2'b11}],
                main_memory[{mem_address[9:4],2'b10}],
                main_memory[{mem_address[9:4],2'b01}],
                main_memory[{mem_address[9:4],2'b00}]};
always @(readOrwrite or mem_address or mem_writedata)
begin
  if(readOrwrite)
  begin
      main_memory[{mem_address[9:4],2'b11}] = mem_writedata[32*4-1:32*3];
      main_memory[{mem_address[9:4],2'b10}] = mem_writedata[32*3-1:32*2];
      main_memory[{mem_address[9:4],2'b01}] = mem_writedata[32*2-1:32*1];
      main_memory[{mem_address[9:4],2'b00}] = mem_writedata[32*1-1:32*0];
  end 

end


endmodule