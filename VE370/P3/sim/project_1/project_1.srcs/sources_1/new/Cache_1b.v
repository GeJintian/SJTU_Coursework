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
    input                  [9:0]cpu_address,      //   5 tag,1 block index ,4 block offset
    input                  [31:0]c_WriteData,       
    output reg              [31:0]c_ReadData,           
    output reg                 hit          ,
    input   clk
    );  
    reg     full_cache;
    reg     [268:0]cache_data[1:0];  // bits of block = 2(way)*(4(word)*32+5(tag)+1(vaild))+ 1(LRU) = 269, two sets
                                        //[268] for LRU, [267] for valid, [266:262] for tag, [261:134] for data; 
                                            //[133] for valid, [132:128] for tag, [127:0] for data
    integer  i;
    reg [127:0] m_writeData;
    wire [127:0] m_readData;
    reg m_instruction;
    wire [9:0] m_address;
    reg LRU;
    
    // initialize 
    initial begin
            for (i=0;i<=1;i=i+1)
                cache_data[i]=269'b0;
            m_writeData = 128'b0;
            m_instruction = 1'b0;
            hit = 1'b0; 
            LRU = 0;
     end
    MainMemory main_mem(m_instruction, cpu_address, m_writeData, m_readData);
     
    always@(negedge clk)
    begin
        m_instruction = 0;
        // read
        if (instruction==0)
        begin
          // hit
          if(cache_data[cpu_address[4]][132:128]==cpu_address[9:5]&&cache_data[cpu_address[4]][133]==1) //tag number matches, valid =1
          begin
            hit = 1'b1;
            // set LRU to be left block
            cache_data[cpu_address[4]][268] = 1'b1;
            case (cpu_address[3:2]) //case word offset
                0: c_ReadData = cache_data[cpu_address[4]][(0+1)*(32)-1:(0)*(32)]; // word #0
                1: c_ReadData = cache_data[cpu_address[4]][(1+1)*(32)-1:(1)*(32)]; // word #1
                2: c_ReadData = cache_data[cpu_address[4]][(2+1)*(32)-1:(2)*(32)]; // word #2
                3: c_ReadData = cache_data[cpu_address[4]][(3+1)*(32)-1:(3)*(32)]; // word #3
                default: c_ReadData = 32'b0;
            endcase
           
          end
          else if(cache_data[cpu_address[4]][266:262]==cpu_address[9:5]&&cache_data[cpu_address[4]][267]==1) //tag number matches, valid =1, (second group of data )
          begin
            hit = 1'b1;
            //Set LRU
            cache_data[cpu_address[4]][268] = 1'b0;
            case (cpu_address[3:2]) //case word offset
                0: c_ReadData = cache_data[cpu_address[4]][134+(0+1)*(32)-1:134+(0)*(32)]; // word #0
                1: c_ReadData = cache_data[cpu_address[4]][134+(1+1)*(32)-1:134+(1)*(32)]; // word #1
                2: c_ReadData = cache_data[cpu_address[4]][134+(2+1)*(32)-1:134+(2)*(32)]; // word #2
                3: c_ReadData = cache_data[cpu_address[4]][134+(3+1)*(32)-1:134+(3)*(32)]; // word #3
                default: c_ReadData = 32'b0;
            endcase
          end
        else 
        begin
          //miss
          hit = 1'b0;
          //find LRU
          LRU = cache_data[cpu_address[4]][268];
          //set valid
          cache_data[cpu_address[4]][LRU*134+133] = 1'b1;
          
          if(LRU)begin
          //update tag
          cache_data[cpu_address[4]][266:262] = cpu_address[9:5];
          //update cache
          cache_data[cpu_address[4]][261:134] = m_readData;
          //update output
            case (cpu_address[3:2]) //case word offset
                0: c_ReadData = cache_data[cpu_address[4]][134+(0+1)*(32)-1:134+(0)*(32)]; // word #0
                1: c_ReadData = cache_data[cpu_address[4]][134+(1+1)*(32)-1:134+(1)*(32)]; // word #1
                2: c_ReadData = cache_data[cpu_address[4]][134+(2+1)*(32)-1:134+(2)*(32)]; // word #2
                3: c_ReadData = cache_data[cpu_address[4]][134+(3+1)*(32)-1:134+(3)*(32)]; // word #3
                default: c_ReadData = 32'b0;
            endcase
          end
          else//LRU == 0
          begin
          //update tag
          cache_data[cpu_address[4]][132:128] = cpu_address[9:5];
          //update cache
          cache_data[cpu_address[4]][127:0] = m_readData;
          //update output
            case (cpu_address[3:2]) //case word offset
                0: c_ReadData = cache_data[cpu_address[4]][(0+1)*(32)-1:(0)*(32)]; // word #0
                1: c_ReadData = cache_data[cpu_address[4]][(1+1)*(32)-1:(1)*(32)]; // word #1
                2: c_ReadData = cache_data[cpu_address[4]][(2+1)*(32)-1:(2)*(32)]; // word #2
                3: c_ReadData = cache_data[cpu_address[4]][(3+1)*(32)-1:(3)*(32)]; // word #3
                default: c_ReadData = 32'b0;
            endcase
          end
          //update LRU
        cache_data[cpu_address[4]][268] = ~LRU;

        end
       end
       // write
       else 
       begin
         if(cache_data[cpu_address[4]][132:128]==cpu_address[9:5]&&cache_data[cpu_address[4]][133]==1) //hit
         begin
             hit = 1'b1;
            case (cpu_address[3:2])
             0: cache_data[cpu_address[4]][(0+1)*(32)-1:(0)*(32)] = c_WriteData; //  #0
             1: cache_data[cpu_address[4]][(1+1)*(32)-1:(1)*(32)] = c_WriteData; //  #1
             2: cache_data[cpu_address[4]][(2+1)*(32)-1:(2)*(32)] = c_WriteData; // #2
             3: cache_data[cpu_address[4]][(3+1)*(32)-1:(3)*(32)] = c_WriteData; // #3 
             default:  cache_data[cpu_address[4]][(0+1)*(32)-1:(0)*(32)] = 32'b0;
            endcase
            m_instruction = 1'b1;
            //set LRU
            cache_data[cpu_address[4]][268] = 1'b1;
            m_writeData = cache_data[cpu_address[4]][127:0];

         end
         else if (cache_data[cpu_address[4]][266:262]==cpu_address[9:5]&&cache_data[cpu_address[4]][267]==1)
         begin
            hit = 1'b1;
            case (cpu_address[3:2])
             0: cache_data[cpu_address[4]][134+(0+1)*(32)-1:134+(0)*(32)] = c_WriteData; // #0
             1: cache_data[cpu_address[4]][134+(1+1)*(32)-1:134+(1)*(32)] = c_WriteData; // #1
             2: cache_data[cpu_address[4]][134+(2+1)*(32)-1:134+(2)*(32)] = c_WriteData; // #2
             3: cache_data[cpu_address[4]][134+(3+1)*(32)-1:134+(3)*(32)] = c_WriteData; // #3 
             default:  cache_data[cpu_address[4]][134+(0+1)*(32)-1:134+(0)*(32)] = 32'b0;
            endcase
            m_instruction = 1'b1;
            //set LRU
            cache_data[cpu_address[4]][268] = 1'b0;
            m_writeData = cache_data[cpu_address[4]][261:134];
         end
         else //Miss for write
         begin
            hit = 1'b0;
          //find LRU
          LRU = cache_data[cpu_address[4]][268];
          //set valid
          cache_data[cpu_address[4]][LRU*134+133] = 1'b1;
          
          if(LRU)begin
          //update tag
          cache_data[cpu_address[4]][266:262] = cpu_address[9:5];
          //update cache
            case (cpu_address[3:2])
             0: cache_data[cpu_address[4]][134+(0+1)*(32)-1:134+(0)*(32)] = c_WriteData; // #0
             1: cache_data[cpu_address[4]][134+(1+1)*(32)-1:134+(1)*(32)] = c_WriteData; // #1
             2: cache_data[cpu_address[4]][134+(2+1)*(32)-1:134+(2)*(32)] = c_WriteData; // #2
             3: cache_data[cpu_address[4]][134+(3+1)*(32)-1:134+(3)*(32)] = c_WriteData; // #3 
             default:  cache_data[cpu_address[4]][134+(0+1)*(32)-1:134+(0)*(32)] = 32'b0;
            endcase
            m_instruction = 1'b1;
            m_writeData = cache_data[cpu_address[4]][261:134];
          end
          else//LRU == 0
          begin
          //update tag
          cache_data[cpu_address[4]][132:128] = cpu_address[9:5];
          //update cache
          cache_data[cpu_address[4]][127:0] = m_readData;
          //update output
            case (cpu_address[3:2])
             0: cache_data[cpu_address[4]][(0+1)*(32)-1:(0)*(32)] = c_WriteData; //  #0
             1: cache_data[cpu_address[4]][(1+1)*(32)-1:(1)*(32)] = c_WriteData; //  #1
             2: cache_data[cpu_address[4]][(2+1)*(32)-1:(2)*(32)] = c_WriteData; // #2
             3: cache_data[cpu_address[4]][(3+1)*(32)-1:(3)*(32)] = c_WriteData; // #3 
             default:  cache_data[cpu_address[4]][(0+1)*(32)-1:(0)*(32)] = 32'b0;
            endcase
            m_instruction = 1'b1;
            m_writeData = cache_data[cpu_address[4]][127:0];
          end
          //update LRU
        cache_data[cpu_address[4]][268] = ~LRU;

        
             end
          
       end
        //change the LRU
        
    end
       
            
        
   
endmodule