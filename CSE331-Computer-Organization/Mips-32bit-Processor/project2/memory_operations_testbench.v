module memory_operations_testbench();

reg[31:0] pc;
wire[31:0] instr;

reg[4:0] read_reg1;
reg[4:0] read_reg2;
reg[4:0] write_reg;
reg[31:0] write_data;
reg regWrite = 0;
wire[31:0] read_data1;
wire[31:0] read_data2;

reg[17:0] address;
reg[31:0] write_data_mem;
reg memRead = 0;
reg memWrite = 0;
wire[31:0] read_data_mem;

reg[15:0] imm;
wire[31:0] sign_ext_imm;
//sign_extend sign_extend1(sign_ext_imm, imm);

wire[31:0] shifted_address;
reg[31:0] shift_address;
//shift_left_2 shift_left2(shifted_address, shift_address);

reg clock = 0;

instruction_block instr_block1 (instr, pc);
//register_block reg_block1 (read_data1, read_data2, write_data, read_reg1, read_reg2, write_reg, regWrite);
//memory_block mem_block1(read_data_mem, address, write_data_mem, memRead, memWrite);

initial begin
	pc = 32'd0;
	#1
	$display("Time=%0t instr=%b", $time, instr);
	
	read_reg1 = 4'b0000;
	read_reg2 = 4'b0001;
	#1
	$display("Time=%0t read_data1=%b read_data2=%b", $time, read_data1, read_data2);
	
	read_reg1 = 4'b0001;
	read_reg2 = 4'b0001;
	write_data = 32'b11111111111;
	write_reg = 4'b0001;
	regWrite = 1'b1;
	#9
	$display("Time=%0t read_data1=%b read_data2=%b", $time, read_data1, read_data2);
	
	memRead = 1;
	address = 17'd1;
	#10
	$display("Time=%0t read_data_mem=%b", $time, read_data_mem);
	
	imm = 16'b1110011101011010;
	#1
	$display("Imm=%b Imm[15]=%b Sign_extended =%b", imm, imm[15], sign_ext_imm);
	
	shift_address = 32'b11100111010110101110011101011010;
	#1
	$display("Address=%b Shifted_address=%b", shift_address, shifted_address);
	
end


// Clock generate
always 
begin
	#10
	clock = ~clock;
end

endmodule