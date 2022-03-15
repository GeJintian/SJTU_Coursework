`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/16 22:30:27
// Design Name: 
// Module Name: Cache
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


module Cache(
    //  Connect to Main Memory
    // Connect to CPU
    input instruction, // zero for read, 1 for write     
    input                  [9:0]cpu_address,      
    input                  [31:0]c_WriteData,       
    output reg              [31:0]c_ReadData,           
    output reg                 hit    ,
    input   clk      
    );  
    reg     full_cache;
    reg     [132:0]cache_data[3:0];  // bits of block = 4*32+4+1 = 133, block number=4
    integer  i;
    reg [127:0] m_writeData;
    wire [127:0] m_readData;
    reg m_instruction;
    wire [9:0] m_address;

    
    // initialize 
    initial begin
            for (i=0;i<=3;i=i+1)
                cache_data[i]=133'b0;
            m_writeData = 128'b0;
            m_instruction = 1'b0;
            hit = 1'b0; 
            
     end
    MainMemory main_mem(m_instruction, cpu_address, m_writeData, m_readData);
     
    always@(negedge clk)
    begin
    m_instruction = 0;
        // read
        if (instruction==0)
        begin
          // hit
          if(cache_data[cpu_address[5:4]][131:128]==cpu_address[9:6]&&cache_data[cpu_address[5:4]][132]==1) //tag number matches, hit =1
          begin
            hit = 1'b1;
             cache_data[cpu_address[5:4]][132]=1'b1;
            case (cpu_address[3:2]) //case block number
                0: c_ReadData = cache_data[cpu_address[5:4]][(0+1)*(32)-1:(0)*(32)]; // block #0
                1: c_ReadData = cache_data[cpu_address[5:4]][(1+1)*(32)-1:(1)*(32)]; // block #1
                2: c_ReadData = cache_data[cpu_address[5:4]][(2+1)*(32)-1:(2)*(32)]; // block #2
                3: c_ReadData = cache_data[cpu_address[5:4]][(3+1)*(32)-1:(3)*(32)]; // block #3
                default: c_ReadData = 32'b0;
            endcase
           
          end
        
            else 
            begin
              //miss
              hit = 1'b0;
              cache_data[cpu_address[5:4]][132]=1'b1;
              cache_data[cpu_address[5:4]][131:128] = cpu_address[9:6];
              //store the memory into cache memory
              cache_data[cpu_address[5:4]][127:0] = m_readData;
              // read from cache memory
               case (cpu_address[3:2]) //case block number
                    2'b00: c_ReadData = cache_data[cpu_address[5:4]][(0+1)*(32)-1:(0)*(32)]; // block #0
                    2'b01: c_ReadData = cache_data[cpu_address[5:4]][(1+1)*(32)-1:(1)*(32)]; // block #1
                    2'b10: c_ReadData = cache_data[cpu_address[5:4]][(2+1)*(32)-1:(2)*(32)]; // block #2
                    2'b11: c_ReadData = cache_data[cpu_address[5:4]][(3+1)*(32)-1:(3)*(32)]; // block #3
                    default: c_ReadData = 32'b0;
                endcase
            end
           end
       // write
       else 
       begin
         if(cache_data[cpu_address[5:4]][131:128]==cpu_address[9:6]&&cache_data[cpu_address[5:4]][132]==1) //hit
         begin
            hit = 1'b1;
            cache_data[cpu_address[5:4]][132]=1'b1;
            case (cpu_address[3:2])
             0: cache_data[cpu_address[5:4]][(0+1)*(32)-1:(0)*(32)] = c_WriteData; // block #0
             1: cache_data[cpu_address[5:4]][(1+1)*(32)-1:(1)*(32)] = c_WriteData; // block #1
             2: cache_data[cpu_address[5:4]][(2+1)*(32)-1:(2)*(32)] = c_WriteData; // block #2
             3: cache_data[cpu_address[5:4]][(3+1)*(32)-1:(3)*(32)] = c_WriteData; // block #3 
             default:  cache_data[cpu_address[5:4]][(0+1)*(32)-1:(0)*(32)] = 32'b0;
            endcase

            m_instruction = 1'b1;

         end
         else 
         begin
           hit = 1'b0;
           cache_data[cpu_address[5:4]][132]=1'b1;
           // write on main memory
           m_instruction = 1'b1;
           cache_data[cpu_address[5:4]][131:128] = cpu_address[9:6];  //tag
           cache_data[cpu_address[5:4]][127:0] = m_readData;
            case (cpu_address[3:2]) 
             0: cache_data[cpu_address[5:4]][(0+1)*(32)-1:(0)*(32)] = c_WriteData; // block #0
             1: cache_data[cpu_address[5:4]][(1+1)*(32)-1:(1)*(32)] = c_WriteData; // block #1
             2: cache_data[cpu_address[5:4]][(2+1)*(32)-1:(2)*(32)] = c_WriteData; // block #2
             3: cache_data[cpu_address[5:4]][(3+1)*(32)-1:(3)*(32)] = c_WriteData; // block #3 
             default:  cache_data[cpu_address[5:4]][(0+1)*(32)-1:(0)*(32)] = 32'b0;
            endcase

         end
        m_writeData = cache_data[cpu_address[5:4]][127:0];
       end
        
    end
       
            
        
   
endmodule