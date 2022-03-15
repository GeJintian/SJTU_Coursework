`timescale 1ns / 1ps
`include "main_mem.v"

/*
 * This a write-back, two-way cache.
*/
module Cache_2B(
    cache_write,    // 0-read, 1-write
    address_cpu,
    data_write2cache,
    data_read4cpu,
    is_hit,         // 0-miss, 1-hit
);
    input cache_write;
    input [9:0] address_cpu;
    input [31:0] data_write2cache;
    output reg [31:0] data_read4cpu;
    output reg is_hit;
    
    // Cache
    // 2 sets, each set with 2 blocks + 1 bit indicating LRU
    // Each block has data of 16 bytes (4 words) = 128 bits
    // #134 valid bit
    // #133 dirty bit
    // #132:128 tag
    // #127:0 data
    reg [270:0] cache [1:0];

    reg mem_write;
    reg [9:0] address_mem;
    reg [127:0] data_write2mem;
    wire [127:0] data_read2cache;

    integer k;

    reg i,j;

    // initialization
    initial begin
        data_read4cpu <= 32'b0;
        is_hit <= 1'b0;     
        for (k=0; k<2; k=k+1) begin
            cache[k] <= 271'b0;
        end
        mem_write <= 1'b0;
        address_mem <= address_cpu;
        data_write2mem <= 128'b0;
    end

    MainMemory today_memory(mem_write, address_mem, data_write2mem, data_read4cache);

    always @(cache_write or address_cpu or data_write2cache) begin

        if(cache_write == 1'b0) begin // read
            
            if( (cache[address_cpu[4]][134] == 1'b1) && (address_cpu[9:5] == cache[address_cpu[4]][132:128]) ) begin // hit right block
                is_hit = 1'b1;
                // set LRU to be left block
                cache[address_cpu[4]][270] = 1'b1;
                // select word
                case (address_cpu[3:2])
                    2'b00: data_read4cpu = cache[address_cpu[4]][31:0];
                    2'b01: data_read4cpu = cache[address_cpu[4]][63:32];
                    2'b10: data_read4cpu = cache[address_cpu[4]][95:64];
                    2'b11: data_read4cpu = cache[address_cpu[4]][127:96];
                    default: data_read4cpu = 32'b0;
                endcase
            // end hit right block

            end else if( (cache[address_cpu[4]][269] == 1'b1) && (address_cpu[9:5] == cache[address_cpu[4]][267:263]) ) begin // hit left block
                is_hit = 1'b1;
                // set LRU to be right block
                cache[address_cpu[4]][270] = 1'b0;
                // select word
                case (address_cpu[3:2])
                    2'b00: data_read4cpu = cache[address_cpu[4]][135+31:135+0];
                    2'b01: data_read4cpu = cache[address_cpu[4]][135+63:135+32];
                    2'b10: data_read4cpu = cache[address_cpu[4]][135+95:135+64];
                    2'b11: data_read4cpu = cache[address_cpu[4]][135+127:135+96];
                    default: data_read4cpu = 32'b0;
                endcase
            // end hit left block; end hit as well

            end else begin // miss          
                is_hit  = 1'b0;
                // get LRU
                i = cache[address_cpu[4]][270];
                // set valid
                cache[address_cpu[4]][i*135+134] = 1'b1;

                // deal with dirty case
                if (cache[address_cpu[4]][i*135+133]) begin
                    // store the right block to memory
                    address_mem = {cache[address_cpu[4]][i*135+132:i*135+128], address_cpu[4:0]};
                    mem_write = 1'b1;
                    data_write2mem = cache[address_cpu[4]][i*135+127:i*135+0];
                    #1 mem_write = 1'b0; 
                    // reset dirty bit
                    cache[address_cpu[4]][i*135+133] = 1'b0;
                // end dirty
                end

                address_mem = address_cpu;
                // write block data
                cache[address_cpu[5:4]][i*135+127:i*135+0] = data_read4cache;
                // update tag
                #1 cache[address_cpu[5:4]][i*135+132:i*135+128] = address_cpu[9:5];
                // select word
                case (address_cpu[3:2])
                    2'b00: data_read4cpu = cache[address_cpu[4]][i*135+31:i*135+0];
                    2'b01: data_read4cpu = cache[address_cpu[4]][i*135+63:i*135+32];
                    2'b10: data_read4cpu = cache[address_cpu[4]][i*135+95:i*135+64];
                    2'b11: data_read4cpu = cache[address_cpu[4]][i*135+127:i*135+96];
                    default: data_read4cpu = 32'b0;
                endcase
                // update LRU
                cache[address_cpu[4]][270] = ~i;
            // end miss
            end
        // end read

        end else begin // write

            if((cache[address_cpu[4]][134] == 1'b1) && (address_cpu[9:5] == cache[address_cpu[4]][132:128])) begin // hit right block
                is_hit = 1'b1;
                // set dirty
                cache[address_cpu[4]][133] = 1'b1;
                // select word                
                case (address_cpu[3:2])
                    2'b00: cache[address_cpu[4]][31:0] = data_write2cache;
                    2'b01: cache[address_cpu[4]][63:32] = data_write2cache;
                    2'b10: cache[address_cpu[4]][95:64] = data_write2cache;
                    2'b11: cache[address_cpu[4]][127:96] = data_write2cache;
                    default: cache[address_cpu[4]][127:0] = 128'b0;
                endcase
            // end hit right block
             
            end else if((cache[address_cpu[4]][269] == 1'b1) & (address_cpu[9:5] == cache[address_cpu[4]][267:263])) begin // hit left block
                is_hit = 1'b1;
                // set dirty
                cache[address_cpu[4]][268] = 1'b1;
                // select word
                case (address_cpu[3:2])
                    2'b00: cache[address_cpu[4]][166:135] = data_write2cache;
                    2'b01: cache[address_cpu[4]][198:167] = data_write2cache;
                    2'b10: cache[address_cpu[4]][230:199] = data_write2cache;
                    2'b11: cache[address_cpu[4]][262:231] = data_write2cache;
                    default: cache[address_cpu[4]][262:135] = 128'b0;
                endcase
            // end hit left block
                
            end else begin // miss
                is_hit = 1'b0;
                // get LRU
                j = cache[address_cpu[4]][270];
                // set valid
                cache[address_cpu[4]][j*135+134] = 1'b1;
                // if dirty
                if (cache[address_cpu[4]][j*135+133]) begin
                    address_mem = {cache[address_cpu[4]][j*135+132:j*135+128], address_cpu[4:0]};
                    mem_write = 1'b1;
                    data_write2mem = cache[address_cpu[4]][j*135+127:j*135+0];
                    #1 mem_write = 1'b0; 
                // end dirty
                end

                address_mem = address_cpu;
                // replace the block
                cache[address_cpu[4]][j*135+127:j*135+0] = data_read4cache;
                // update tag
                #1 cache[address_cpu[4]][j*135+132:j*135+128] = address_cpu[9:5];
                // set dirty
                cache[address_cpu[4]][j*135+133] = 1'b1;                
                // write the new word
                case (address_cpu[3:2])
                    2'b00: cache[address_cpu[4]][j*135+31:j*135+0] = data_write2cache;
                    2'b01: cache[address_cpu[4]][j*135+63:j*135+32] = data_write2cache;
                    2'b10: cache[address_cpu[4]][j*135+95:j*135+64] = data_write2cache;
                    2'b11: cache[address_cpu[4]][j*135+127:j*135+96] = data_write2cache;
                    default: cache[address_cpu[4]][j*135+127:j*135+0] = 128'b0;
                endcase
                // update LRU
                cache[address_cpu[4]][270] = ~j;
            // end miss
            end
        // end write
        end
    // end always@
    end
endmodule
