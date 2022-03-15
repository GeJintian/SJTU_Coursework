`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/09 03:42:42
// Design Name: 
// Module Name: pipe_test
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


module pipe_test;
    integer i;
    reg clk;
    pipeline    UUT (clk);
    initial begin
    clk = 1;
    i = 0;
    $display("========================");
    end
    always #5 begin
        $display("Time: %d, CLK = %d, PC = %d",i,clk,UUT.pcout);
        $display("[$s0] = %H, [$s1] = %H, [$s2] = %H", UUT.register_file.memory[16], UUT.register_file.memory[17], UUT.register_file.memory[18]);
        $display("[$s3] = %H, [$s4] = %H, [$s5] = %H", UUT.register_file.memory[19], UUT.register_file.memory[20], UUT.register_file.memory[21]);
        $display("[$s6] = %H, [$s7] = %H, [$t0] = %H", UUT.register_file.memory[22], UUT.register_file.memory[23], UUT.register_file.memory[8]);
        $display("[$t1] = %H, [$t2] = %H, [$t3] = %H", UUT.register_file.memory[9], UUT.register_file.memory[10], UUT.register_file.memory[11]);
        $display("[$t4] = %H, [$t5] = %H, [$t6] = %H", UUT.register_file.memory[12], UUT.register_file.memory[13], UUT.register_file.memory[14]);
        $display("[$t7] = %H, [$t8] = %H, [$t9] = %H", UUT.register_file.memory[15], UUT.register_file.memory[24], UUT.register_file.memory[25]);
        //$display("[$z1] = %H, [$z2] = %H", UUT.dm.memory[1],UUT.dm.memory[2]);
        //$display("Instruction is %b, PCWrite is %b, is_branch is %b", UUT.IF_instruct, UUT.PCWrite, UUT.is_branch);
        //$display("pcin is %d",UUT.pcin);
        //$display("ForwardA is %b, EX_RegRs is %H, ID_Data1 is %H",UUT.ForwardA,UUT.EX_RegRs, UUT.ID_data1);
        //$display("ForwardB is %b, EX_RegRt is %H, ID_Data2 is %H",UUT.ForwardB,UUT.EX_RegRt, UUT.ID_data2);
        //$display("ALU input1 is %H, ALU input2 is %H, ALU control is %b", UUT.ALU1, UUT.ALU21, UUT.ALUControl);
        //$display("ALU result is %H",UUT.EX_ALUResult);
        //$display("ID_data2 is %H, EX_RegRt is %H", UUT.ID_data2, UUT.EX_RegRt);
        //$display("MemWrite is %b, MEM_MemWrite is %b, MEM_RegRt is %H", UUT.MemWrite, UUT.MEM_MemWrite, UUT.MEM_RegRt);
        //$display("WB_WriteData is %H", UUT.WB_WriteData);
        //$display("WB_MemtoReg is %b, WB_ReadData is %H", UUT.WB_MemtoReg, UUT.WB_ReadData);
        clk = ~clk;
        if (clk) i = i + 1;
        end
endmodule
