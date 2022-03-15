`timescale 1ns / 1ps
`include "main_mem.v"

/*
 * This a write-back, direct mapped cache.
*/
module Cache_2A(
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
    // 4 sets, each set with 16 bytes (4 words) = 128 bits
    // #133 valid bit
    // #132 dirty bit
    // #131:128 tag
    // #127:0 data
    reg [133:0] cache [3:0];

    reg mem_write;
    reg [9:0] address_mem;
    reg [127:0] data_write2mem;
    wire [127:0] data_read2cache;
    
    integer k;

    // initializaiton
    initial begin
        data_read4cpu <= 32'b0;
        is_hit <= 1'b0;     
        for (k=0; k<4; k=k+1) begin
            cache[k] <= 134'b0;
        end
        mem_write <= 1'b0;
        address_mem <= address_cpu;
        data_write2mem <= 128'b0;
    end

    MainMemory todayMemory(mem_write, address_mem, data_write2mem, data_read4cache);

    always @(cache_write or address_cpu or data_write2cache) begin 
        
        if (cache_write == 1'b0) begin //read

            if ((cache[address_cpu[5:4]][133] == 1'b1) && (address_cpu[9:6] == cache[address_cpu[5:4]][131:128])) begin // hit: valid + same tag
                is_hit = 1'b1;
                // select word (1 word=32 bits)
                case (address_cpu[3:2])
                    2'b00: data_read4cpu = cache[address_cpu[5:4]][31:0];
                    2'b01: data_read4cpu = cache[address_cpu[5:4]][63:32];
                    2'b10: data_read4cpu = cache[address_cpu[5:4]][95:64];
                    2'b11: data_read4cpu = cache[address_cpu[5:4]][127:96];
                    default: data_read4cpu = 32'b0;
                endcase
            // end hit

            end else begin // miss
                is_hit = 1'b0;
                // set valid
                cache[address_cpu[5:4]][133] = 1'b1;

                // if dirty
                if (cache[address_cpu[5:4]][132] == 1'b1) begin
                    // we need to store the original data to memory
                    address_mem = {cache[address_cpu[5:4]][131:128], address_cpu[5:0]};
                    mem_write = 1'b1;
                    data_write2mem = cache[address_cpu[5:4]][127:0];
                    #1 mem_write = 1'b0;
                    // reset dirty bit
                    cache[address_cpu[5:4]][132] = 1'b0;
                // end dirty
                end

                address_mem = address_cpu;
                // overwrite the block with new value
                cache[address_cpu[5:4]][127:0] = data_read2cache;
                // update tag
                #1 cache[address_cpu[5:4]][131:128] = address_cpu[9:6];
                // read word
                case (address_cpu[3:2])
                    2'b00: data_read4cpu = cache[address_cpu[5:4]][31:0];
                    2'b01: data_read4cpu = cache[address_cpu[5:4]][63:32];
                    2'b10: data_read4cpu = cache[address_cpu[5:4]][95:64];
                    2'b11: data_read4cpu = cache[address_cpu[5:4]][127:96];
                    default: data_read4cpu = 32'b0;
                endcase
            // end miss
            end
        // end read
        
        end else begin // write

            if((cache[address_cpu[5:4]][133] == 1'b1) && (address_cpu[9:6] == cache[address_cpu[5:4]][131:128])) begin // hit: valid + tag same
                is_hit = 1'b1;
                // set dirty
                cache[address_cpu[5:4]][132] = 1'b1;
                // select word
                case (address_cpu[3:2])
                    2'b00: cache[address_cpu[5:4]][31:0] = data_write2cache;
                    2'b01: cache[address_cpu[5:4]][63:32] = data_write2cache;
                    2'b10: cache[address_cpu[5:4]][95:64] = data_write2cache;
                    2'b11: cache[address_cpu[5:4]][127:96] = data_write2cache;
                    default: cache[address_cpu[5:4]][127:0] = 128'b0;
                endcase
            // end hit

            end else begin // miss
                is_hit = 1'b0;
                // set valid
                cache[address_cpu[5:4]][133] = 1'b1;

                // if dirty
                if (cache[address_cpu[5:4]][132] == 1'b1) begin
                    address_mem = {cache[address_cpu[5:4]][131:128], address_cpu[5:0]};
                    mem_write = 1'b1;
                    data_write2mem = cache[address_cpu[5:4]][127:0];
                    #1 mem_write = 1'b0;
                // end dirty
                end

                address_mem = address_cpu;
                // replace the block
                cache[address_cpu[5:4]][127:0] = data_read2cache;
                // update tag
                #1 cache[address_cpu[5:4]][131:128] = address_cpu[9:6];
                // set dirty
                cache[address_cpu[5:4]][132] = 1'b1;
                // write the new word
                case (address_cpu[3:2])
                    2'b00: cache[address_cpu[5:4]][31:0] = data_write2cache;
                    2'b01: cache[address_cpu[5:4]][63:32] = data_write2cache;
                    2'b10: cache[address_cpu[5:4]][95:64] = data_write2cache;
                    2'b11: cache[address_cpu[5:4]][127:96] = data_write2cache;
                    default: cache[address_cpu[5:4]][127:0] = 128'b0;
                endcase
            // end miss
            end
        // end write
        end
    // end always@
    end
endmodule
