module register_block (
output reg [31:0] read_data1,
output reg [31:0] read_data2,
input [31:0] write_data,
input [4:0] read_reg1,
input [4:0] read_reg2,
input [4:0] write_reg,
input regWrite);

reg[31:0] registers[31:0];
initial begin
  $readmemb("registers.mem", registers);
end

always @ (read_reg1 or read_reg2 or registers[read_reg1] or registers[read_reg2]) 
begin
	$readmemb("registers.mem", registers);
	
	if (read_reg1 == 0) 
		read_data1 = 32'b0;
	else 
		read_data1 = registers[read_reg1];	
		
	if (read_reg2 == 0) 
		read_data2 = 32'b0;
	else
		read_data2 = registers[read_reg2];
end

always @ (*) 
begin
	if (regWrite) 
	begin
		registers[write_reg] = write_data;
		$writememb("registers.mem", registers);
	end
end


endmodule