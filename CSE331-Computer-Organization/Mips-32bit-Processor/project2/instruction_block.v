module instruction_block (
output reg [31:0] instruction,
input [31:0] pc);

reg[7:0] instrMem [4095:0];
initial begin
  $readmemb("instructions.mem", instrMem);
end

reg[9:0] address;

always @ (pc) begin
	$readmemb("instructions.mem", instrMem);
	address = pc[9:0]; // Only take least-significant 10 bit of PC as instruction memory address
	instruction = {instrMem[address+3], instrMem[address+2], instrMem[address+1], instrMem[address]};
end

endmodule