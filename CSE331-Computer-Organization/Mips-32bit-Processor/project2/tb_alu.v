module tb_alu();

reg[31:0] a;
reg[31:0] b;
reg CLK = 0;  // Initialize CLK
wire[31:0] result;
wire zero_bit;
reg[2:0] AluOp;
reg reset;

alu alu1(.alu_result(result), .zero_bit(zero_bit), .alu_src1(a), .alu_src2(b), .alu_ctr(AluOp));

// Initial values
initial 
begin
	 // Logical operators test
	 a = 32'b11111111111110011000101100001101; 
	 b = 32'b10011011101110011010101101101010; 
	 
	 AluOp = 3'b000; // AND 
	 #10
	 $display("Time=%0t a=%b b=%b AND=%b", $time, a, b, result);
	 
	 // Or test
	 AluOp = 3'b001; // OR
	 #10
	 $display("Time=%0t a=%b b=%b OR=%b", $time, a, b, result);
	 
	 // Xor test
	 AluOp = 3'b010; // XOR
	 #10
	 $display("Time=%0t a=%b b=%b XOR=%b", $time, a, b, result);
	 
	 // Nor test
	 AluOp = 3'b011; // NOR
	 #10
	 $display("Time=%0t a=%b b=%b NOR=%b", $time, a, b, result);
	 
	 // Less-than test
	 AluOp = 3'b100; // LESS THEN
	 #20
	 $display("Time=%0t a=%d b=%d LESS THAN=%d", $time, a, b, result); // a=5, b=15
	 
	 // Less-than test
	 AluOp = 3'b100; // LESS THEN
	 a = 32'd15; // 15
	 b = 32'd5; // 5
	 #20
	 $display("Time=%0t a=%d b=%d LESS THAN=%d", $time, a, b, result); // a=15, b=5
	 
	 // Less-than test
	 AluOp = 3'b100; // LESS THEN
	 a = 32'd15; // 15
	 b = 32'd15; // 15
	 #20
	 $display("Time=%0t a=%d b=%d LESS THAN=%d", $time, a, b, result); // a=15, b=15
	 
	 // Less-than test
	 AluOp = 3'b100; // LESS THEN
	 a = 32'b11111111111111111111111111111011; // -5
	 b = 32'b00000000000000000000000000000101; // 5
	 #20
	 $display("Time=%0t a=%b b=%b LESS THAN=%d", $time, a, b, result); // a=-5, b=5
	 
	 // Less-than test
	 AluOp = 3'b100; // LESS THEN
	 a = 32'b11111111111011010010101100110100; // -1234124 
	 b = 32'b11111111111110011000101100001101; // -423155
	 #20
	 $display("Time=%0t a=%b b=%b LESS THAN=%d", $time, a, b, result); // a=-1234124, b=-423155
	 
	 // Add test
	 AluOp = 3'b101; // ADD
	 #20
	 $display("Time=%0t a=%b b=%b ADD=%b", $time, a, b, result); // a=-5, b=5
	 
	 // Add test
	 AluOp = 3'b101; // ADD
	 a = 32'd15; // 15
	 b = 32'd15; // 15
	 #20
	 $display("Time=%0t a=%d b=%d ADD=%d", $time, a, b, result); // a=15, b=15
	 
	 // Add test
	 AluOp = 3'b101; // ADD
	 a = 32'd2147352571; // 2147352571
	 b = 32'd393211; // 393211
	 #20
	 $display("Time=%0t a=%d b=%d ADD=%d", $time, a, b, result); // a=2147352571, b=393211
	
	 // Subtract test
	 AluOp = 3'b110; // SUB
	 a = 32'd15; // 15
	 b = 32'd15; // 15
	 #20
	 $display("Time=%0t a=%d b=%d SUB=%d", $time, a, b, result); // a=15, b=15
	 
	 // Subtract test
	 AluOp = 3'b110; // SUB
	 a = 32'd5; // 5
	 b = 32'd15; // 15
	 #20
	 $display("Time=%0t a=%d b=%d SUB=%b", $time, a, b, result); // a=5, b=15
	 
	 // Subtract test
	 AluOp = 3'b110; // SUB
	 a = 32'd2147352571; // 2147352571
	 b = 32'd393211; // 393211
	 #20
	 $display("Time=%0t a=%d b=%d SUB=%d", $time, a, b, result); //  a=2147352571, b=393211
end

// Clock generate
always 
begin
	#1 
	CLK = ~CLK;
end

endmodule