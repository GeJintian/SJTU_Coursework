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


module Cache_1b(
    //  Connect to Main Memory
    // Connect to CPU
    input instruction, // zero for read, 1 for write     
    input                  [9:0]cpu_address,      
    input                  [31:0]c_WriteData,       
    output reg              [31:0]c_ReadData,           
    output reg                 hit          
    );  
    reg     [133:0]cache_data[3:0];  // bits of block = 4*32+4+1+1 = 134, block number=4
    integer  i;
    reg [127:0] m_writeData;
    wire [127:0] m_readData;
    reg m_instruction;
    reg [9:0] m_address;
    reg address;
    
    // initialize 
    initial begin
            for (i=0;i<=3;i=i+1)
                cache_data[i]=133'b0;
            m_writeData = 128'b0;
            m_instruction = 1'b0;
            hit = 1'b0; 
            m_address =0;
            m_address = cpu_address;
     end
    
    
    MainMemory main_mem(m_instruction,m_address, m_writeData, m_readData);
     
    always@(instruction or cpu_address or c_WriteData)
    begin
        // read
        // read part here is the same as 1a
        if (instruction==0)
        begin
          // hit
          if(cache_data[cpu_address[5:4]][131:128]==cpu_address[9:6]&&cache_data[cpu_address[5:4]][132]==1) //tag number matches, hit =1
          begin
            hit = 1'b1;
            case (cpu_address[3:2]) //case block number
                0: c_ReadData = cache_data[cpu_address[5:4]][(0+1)*(32)-1:(0)*(32)]; // word #0
                1: c_ReadData = cache_data[cpu_address[5:4]][(1+1)*(32)-1:(1)*(32)]; // word #1
                2: c_ReadData = cache_data[cpu_address[5:4]][(2+1)*(32)-1:(2)*(32)]; // word #2
                3: c_ReadData = cache_data[cpu_address[5:4]][(3+1)*(32)-1:(3)*(32)]; // word #3
                default: c_ReadData = 32'b0;
            endcase
           
          end
        
        else 
        begin
          //miss
          hit = 1'b0;
          cache_data[cpu_address[5:4]][132]=1'b1;
          
          m_address = cpu_address;
          // check dirty
          if(cache_data[cpu_address[5:4]][133]==1) // if it's dirty
             begin
               m_instruction = 1;
               m_address = {cache_data[cpu_address[5:4]][131:128], cpu_address[5:0]}; // first four digits are tag, last six digits are the same as cpu address
               m_writeData = cache_data[cpu_address[5:4]][127:0];
               #0.1
               cache_data[cpu_address[5:4]][133]=0;
             end
          //store the memory into cache memory
          m_instruction = 1'b0;
          m_address = cpu_address;
          cache_data[cpu_address[5:4]][127:0] = m_readData;
          // read from cache memory
           case (cpu_address[3:2]) //case block number
                0: c_ReadData = cache_data[cpu_address[5:4]][(0+1)*(32)-1:(0)*(32)]; // word #0
                1: c_ReadData = cache_data[cpu_address[5:4]][(1+1)*(32)-1:(1)*(32)]; // word #1
                2: c_ReadData = cache_data[cpu_address[5:4]][(2+1)*(32)-1:(2)*(32)]; // word #2
                3: c_ReadData = cache_data[cpu_address[5:4]][(3+1)*(32)-1:(3)*(32)]; // word #3
                default: c_ReadData = 32'b0;
            endcase
        end
       end
       // write
       // 'dirty' bit is at cache_data[133]
       else 
       begin
         if(cache_data[cpu_address[5:4]][131:128]==cpu_address[9:6]&&cache_data[cpu_address[5:4]][132]==1) //hit
         begin
             
             hit = 1'b1;
            case (cpu_address[3:2])
             0: cache_data[cpu_address[5:4]][(0+1)*(32)-1:(0)*(32)] = c_WriteData; // word #0
             1: cache_data[cpu_address[5:4]][(1+1)*(32)-1:(1)*(32)] = c_WriteData; // word #1
             2: cache_data[cpu_address[5:4]][(2+1)*(32)-1:(2)*(32)] = c_WriteData; // word #2
             3: cache_data[cpu_address[5:4]][(3+1)*(32)-1:(3)*(32)] = c_WriteData; // word #3 
             default:  cache_data[cpu_address[5:4]][(0+1)*(32)-1:(0)*(32)] = 32'b0;
            endcase
            cache_data[cpu_address[5:4]][133]=1; // set dirty

         end
         else 
         begin
           hit = 1'b0;
           cache_data[cpu_address[5:4]][132]=1'b1;
           // To check if the block dirty
           if(cache_data[cpu_address[5:4]][133]==1) // if it's dirty
             begin
               m_instruction = 1;
               m_address = {cache_data[cpu_address[5:4]][131:128], cpu_address[5:0]}; // first four digits are tag, last six digits are the same as cpu address
               m_writeData = cache_data[cpu_address[5:4]][127:0];
               
               #0.1
               cache_data[cpu_address[5:4]][133]=0;
               
             end
           // write on main memory
           m_instruction = 1'b1;
           cache_data[cpu_address[5:4]][131:128] = cpu_address[9:6];  //tag
           cache_data[cpu_address[5:4]][127:0] = m_readData;
            case (cpu_address[3:2]) 
             0: cache_data[cpu_address[5:4]][(0+1)*(32)-1:(0)*(32)] = c_WriteData; // word #0
             1: cache_data[cpu_address[5:4]][(1+1)*(32)-1:(1)*(32)] = c_WriteData; // word #1
             2: cache_data[cpu_address[5:4]][(2+1)*(32)-1:(2)*(32)] = c_WriteData; // word #2
             3: cache_data[cpu_address[5:4]][(3+1)*(32)-1:(3)*(32)] = c_WriteData; // word #3 
             default:  cache_data[cpu_address[5:4]][(0+1)*(32)-1:(0)*(32)] = 32'b0;
            endcase
         end
        //m_writeData = cache_data[cpu_address[5:4]][127:0];
       end
        
    end
       
            
        
   
endmodule