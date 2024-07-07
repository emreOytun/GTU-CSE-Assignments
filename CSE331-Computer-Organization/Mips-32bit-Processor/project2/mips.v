module mips(input clock);

wire[31:0] pc_next;
wire[31:0] pc_4;
wire[31:0] imm32;
wire[31:0] imm32_shifted;
wire[31:0] branch_address;
wire branch_res;

wire[31:0] instr;
wire[31:0] rs;
wire[31:0] rt;
wire[31:0] alu_res;
wire[31:0] mem_res;
wire[31:0] write_data;
wire[4:0] write_reg;

wire regDst;
wire branch;
wire memRead;
wire memWrite;
wire[2:0] ALUop;
wire ALUsrc;
wire regWrite;
wire jump;
wire byteOperations;
wire move;
wire[2:0] ALUctr;
wire[31:0] alu_src2;
wire zero;

reg[31:0] write_data_reg;
reg[4:0] write_reg_reg;
reg regWrite_reg;

reg[31:0] mem_write_data_reg;
reg mem_write_reg;

reg[31:0] pc;
initial begin
	pc = 32'b0;
end

reg[31:0] pcCounter;
initial begin
	pcCounter = 32'd0;
end

always @(posedge clock) 
begin
	if (pcCounter == 32'd0) begin
		pcCounter = pcCounter + 1;
	end
	
	else begin
		pc = pc_next;
		pcCounter = pcCounter + 1;
	end	
	
end


sign_extend sign_extend_imm (
.sign_ext_imm(imm32),
.imm(instr[15:0]));

shift_left_2 shift_left_2_instance (
.shifted_address(imm32_shifted),
.address(imm32));

adder adder_pc_4(
.s(pc_4),
.a(pc),
.b(32'd4),
.cin(1'b0));

adder adder_pc_4_imm32_shifted (
.s(branch_address),
.a(pc_4),
.b(imm32_shifted),
.cin(1'b0));

wire bneSig, bne_res, notZero;
and and_bneSig(bneSig, branch, instr[28]);
not not_zeroBit(notZero, zero);
and and_bne_res(bne_res, bneSig, notZero);

wire branchCheck, notBneSig;
and and_branchCheck(branchCheck, branch, zero);
not not_bneSig(notBneSig, bneSig);
and and_branch_Res(branch_res, branchCheck, notBneSig);

wire branch_final_res;
or or_branch_final_res(branch_final_res, branch_res, bne_res);

wire[31:0] pc_next1;
thirtytwobit_mux_two_one mux_branch(.out(pc_next1), .in0(pc_4), .in1(branch_address), .sel(branch_final_res));


// Check jr
wire jr;
wire opCodeOr, opCodeZero, jrFuncCode;
or or_opCode(opCodeOr, instr[31], instr[30], instr[29], instr[28], instr[27], instr[26]); // opcode: instr[31:26]
not not_for_opCodeZero(opCodeZero, opCodeOr);

wire func_code_0_not, func_code_1_not, func_code_2_not, func_code_4_not, func_code_5_not;
not not_func0(func_code_0_not, instr[0]);
not not_func1(func_code_1_not, instr[1]);
not not_func2(func_code_2_not, instr[2]);
not not_func4(func_code_4_not, instr[4]);
not not_func5(func_code_5_not, instr[5]);
and and_for_funccode(jrFuncCode, func_code_5_not, func_code_4_not, instr[3], func_code_2_not, func_code_1_not, func_code_0_not); // func code: instr[5:0] 

and and_jr(jr, opCodeZero, jrFuncCode);

// Extend jump address
reg[31:0] jumpExt;
always @(*) 
begin
	jumpExt = {6'b000000, instr[25:0]};
end

// Find pc_next finally
wire[31:0] pc_next2;
thirtytwobit_mux_two_one mux_pcnext2(.out(pc_next2), .in0(pc_next1), .in1(jumpExt), .sel(jump));
thirtytwobit_mux_two_one mux_pcnext(.out(pc_next), .in0(pc_next2), .in1(rs), .sel(jr));

instruction_block instr_block1(instr, pc);

control_unit control_unit1 (
.regDst(regDst),
.branch(branch),
.memRead(memRead),
.memWrite(memWrite),
.ALUop(ALUop),
.ALUsrc(ALUsrc),
.regWrite(regWrite),
.jump(jump),
.byteOperations(byteOperations),
.move(move),
.opcode(instr[31:26]));

alu_control alu_control1 (
.alu_ctr(ALUctr),
.function_code(instr[5:0]),
.ALUop(ALUop));


wire regWrite_res; // Calculated below in line 170-180 
always @ (negedge clock) 
begin
	write_data_reg = write_data;
	write_reg_reg = write_reg;
end

always @ (clock) 
begin
	if (clock == 1'b1) begin //posedge 0->1
		regWrite_reg = 1'b0;
	end
	else begin
		regWrite_reg = regWrite_res; // negedge 1->0
	end
end

// Check jal
wire jal;
and and_jal(jal, jump, instr[26]);

// Find write_reg with muxes for jal
wire[4:0] write_reg1;
fivebit_mux_two_one mux_for_write_reg1(.out(write_reg1), .in0(instr[20:16]), .in1(instr[15:11]), .sel(regDst));
fivebit_mux_two_one mux_for_write_reg(.out(write_reg), .in0(write_reg1), .in1(5'd31), .sel(jal));

// Find read_reg1 with muxes for jr
wire[4:0] read_reg1;
fivebit_mux_two_one mux_for_read_reg1(.out(read_reg1), .in0(instr[25:21]), .in1(5'd31), .sel(jr));

// Find regWrite with muxes for jr
onebit_mux_two_one mux_for_regWrite(.out(regWrite_res), .in0(regWrite), .in1(1'b0), .sel(jr));

register_block register_block1 (
.read_data1(rs),
.read_data2(rt),
.write_data(write_data_reg),
.read_reg1(read_reg1),
.read_reg2(instr[20:16]),
.write_reg(write_reg_reg),
.regWrite(regWrite_reg));


always @ (negedge clock) 
begin
	mem_write_data_reg = rt;
end

always @ (clock) 
begin
	if (clock == 1'b1) begin //posedge 0->1
		mem_write_reg = 1'b0;
	end
	else begin
		mem_write_reg = memWrite; // negedge 1->0
	end
end

memory_block memory_block1 (
.read_data(mem_res),
.byteOperations(byteOperations),
.address(alu_res[17:0]),
.write_data(mem_write_data_reg),
.memRead(memRead),
.memWrite(mem_write_reg));

thirtytwobit_mux_two_one mux_for_alu_src2(.out(alu_src2), .in0(rt), .in1(imm32), .sel(ALUsrc));

alu alu1 (
.alu_result(alu_res), 
.zero_bit(zero), 
.alu_src1(rs), 
.alu_src2(alu_src2), 
.alu_ctr(ALUctr));

// Find write_data with muxes for jal and move
wire[31:0] write_data1, write_data2;
thirtytwobit_mux_two_one mux_for_write_data1(.out(write_data1), .in0(alu_res), .in1(mem_res), .sel(memRead));
thirtytwobit_mux_two_one mux_for_write_data2(.out(write_data2), .in0(write_data1), .in1(pc_4), .sel(jal));
thirtytwobit_mux_two_one mux_for_write_data(.out(write_data), .in0(write_data2), .in1(rs), .sel(move));

endmodule