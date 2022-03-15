`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/03 17:27:36
// Design Name: 
// Module Name: single_sim
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


module single_sim;
    integer i;
    reg clk;
    single  UUT (clk);
    initial begin
        clk = 0;
        i = 0;
        $display("========================");
        #9  begin
        $display("Time: %d, CLK = %d, PC = %d",i,clk,UUT.pcout);
        $display("[$s0] = %H, [$s1] = %H, [$s2] = %H", UUT.register_file.memory[16], UUT.register_file.memory[17], UUT.register_file.memory[18]);
        $display("[$s3] = %H, [$s4] = %H, [$s5] = %H", UUT.register_file.memory[19], UUT.register_file.memory[20], UUT.register_file.memory[21]);
        $display("[$s6] = %H, [$s7] = %H, [$t0] = %H", UUT.register_file.memory[22], UUT.register_file.memory[23], UUT.register_file.memory[8]);
        $display("[$t1] = %H, [$t2] = %H, [$t3] = %H", UUT.register_file.memory[9], UUT.register_file.memory[10], UUT.register_file.memory[11]);
        $display("[$t4] = %H, [$t5] = %H, [$t6] = %H", UUT.register_file.memory[12], UUT.register_file.memory[13], UUT.register_file.memory[14]);
        $display("[$t7] = %H, [$t8] = %H, [$t9] = %H", UUT.register_file.memory[15], UUT.register_file.memory[24], UUT.register_file.memory[25]);
            //$display("pcadd %b",UUT.pcadd);
            //$display("pcjump %b",UUT.pcjump);
            //$display("pcbranch %b",UUT.pcbranch);
            //$display("signshift %b",UUT.signshift);
            //$display("pcmux %b",UUT.pcmux);
            //$display("isbranch %b, zero %b",UUT.isbranch, UUT.zero);
        end
    end
    
    always #10 clk = ~clk;
    always #10 begin
        if (~clk) i = i + 1;
        $display("Time: %d, CLK = %d, PC = %d",i,clk,UUT.pcout);
        $display("[$s0] = %H, [$s1] = %H, [$s2] = %H", UUT.register_file.memory[16], UUT.register_file.memory[17], UUT.register_file.memory[18]);
        $display("[$s3] = %H, [$s4] = %H, [$s5] = %H", UUT.register_file.memory[19], UUT.register_file.memory[20], UUT.register_file.memory[21]);
        $display("[$s6] = %H, [$s7] = %H, [$t0] = %H", UUT.register_file.memory[22], UUT.register_file.memory[23], UUT.register_file.memory[8]);
        $display("[$t1] = %H, [$t2] = %H, [$t3] = %H", UUT.register_file.memory[9], UUT.register_file.memory[10], UUT.register_file.memory[11]);
        $display("[$t4] = %H, [$t5] = %H, [$t6] = %H", UUT.register_file.memory[12], UUT.register_file.memory[13], UUT.register_file.memory[14]);
        $display("[$t7] = %H, [$t8] = %H, [$t9] = %H", UUT.register_file.memory[15], UUT.register_file.memory[24], UUT.register_file.memory[25]);
        //$display("pcadd %b",UUT.pcadd);
        //$display("pcjump %b",UUT.pcjump);
        //$display("pcbranch %b",UUT.pcbranch);
        //$display("signshift %b",UUT.signshift);
        //$display("pcmux %b",UUT.pcmux);
        //$display("isbranch %b, zero %b",UUT.isbranch, UUT.zero);
        
    end

endmodule
