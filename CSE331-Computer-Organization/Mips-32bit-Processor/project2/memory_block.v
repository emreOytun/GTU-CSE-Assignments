module memory_block (
output reg [31:0] read_data,
input byteOperations,
input [17:0] address,
input [31:0] write_data,
input memRead,
input memWrite);

reg[7:0] mem[127:0];
initial begin
  $readmemb("memory.mem", mem);
end

always @ (*) 
begin
	if (memRead) begin
		$readmemb("memory.mem", mem);
		
		if (byteOperations) begin
			read_data <= {24'b0, mem[address]};
		end
		
		else begin
			read_data <= {mem[address+3], mem[address+2], mem[address+1], mem[address]};
		end
		
	end
end

always @ (*) 
begin
	if (memWrite && !memRead) begin
		if (byteOperations) begin
			mem[address] <= write_data[7:0];
		end
		
		else begin
			mem[address+3] <= write_data[31:24];
			mem[address+2] <= write_data[23:16];
			mem[address+1] <= write_data[15:8];
			mem[address] <= write_data[7:0];
		end
		
		$writememb("memory.mem", mem);
	end
end

endmodule