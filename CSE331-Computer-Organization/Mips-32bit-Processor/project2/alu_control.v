module alu_control (
output [2:0] alu_ctr,
input [5:0] function_code,
input [2:0] ALUop);

wire[5:0] function_code_not;
not not1(function_code_not[0], function_code[0]);
not not2(function_code_not[1], function_code[1]);
not not3(function_code_not[2], function_code[2]);
not not4(function_code_not[3], function_code[3]);
not not5(function_code_not[4], function_code[4]);
not not6(function_code_not[5], function_code[5]);

wire[2:0] ALUopNot;
not not7(ALUopNot[0], ALUop[0]);
not not8(ALUopNot[1], ALUop[1]);
not not9(ALUopNot[2], ALUop[2]);


wire add, sub, addi, subi, andSig, orSig, andi, ori, slt, slti, beqbne;
and and_add(add, ALUop[2], ALUop[1], ALUop[0], function_code_not[5], function_code_not[4], function_code_not[3],
						function_code_not[2], function_code[1], function_code_not[0]);
and and_sub(sub, ALUop[2], ALUop[1], ALUop[0], function_code_not[5], function_code_not[4], function_code_not[3],
						function_code_not[2], function_code[1], function_code[0]);
and and_addi(addi, ALUop[2], ALUopNot[1], ALUop[0]); // also for lw, sw, lb, sb 
and and_subi(subi, ALUop[2], ALUop[1], ALUopNot[0]);
and and_and(andSig, ALUop[2], ALUop[1], ALUop[0], function_code_not[5], function_code_not[4], function_code_not[3],
						function_code[2], function_code_not[1], function_code_not[0]);
and and_or(orSig, ALUop[2], ALUop[1], ALUop[0], function_code_not[5], function_code_not[4], function_code_not[3],
						function_code[2], function_code_not[1], function_code[0]);
and and_andi(andi, ALUopNot[2], ALUopNot[1], ALUopNot[0]);
and and_ori(ori, ALUopNot[2], ALUopNot[1], ALUop[0]);
and and_slt(slt, ALUop[2], ALUop[1], ALUop[0], function_code_not[5], function_code_not[4], function_code_not[3],
						function_code[2], function_code[1], function_code[0]);
and and_slti(slti, ALUop[2], ALUopNot[1], ALUopNot[0]);
and and_beqbne(beqbne, ALUop[2], ALUop[1], ALUopNot[0]);
						
or (alu_ctr[2], add, sub, addi, subi, slt, slti, beqbne);
or (alu_ctr[1], sub, subi, beqbne);
or (alu_ctr[0], add, addi, orSig, ori);


endmodule