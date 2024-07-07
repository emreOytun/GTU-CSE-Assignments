module control_unit (
output regDst,
output branch,
output memRead,
output memWrite,
output [2:0] ALUop,
output ALUsrc,
output regWrite,
output jump,
output byteOperations,
output move,
input [5:0] opcode);

wire[5:0] opCodeNot;
not not1(opCodeNot[0], opcode[0]);
not not2(opCodeNot[1], opcode[1]);
not not3(opCodeNot[2], opcode[2]);
not not4(opCodeNot[3], opcode[3]);
not not5(opCodeNot[4], opcode[4]);
not not6(opCodeNot[5], opcode[5]);

wire rtype, addi, subi, andi, ori, lw, sw, lb, sb, slti, beq, bne, j, jal;
and and_rtype(rtype, opCodeNot[0], opCodeNot[1], opCodeNot[2], opCodeNot[3], opCodeNot[4], opCodeNot[5]);
and and_addi(addi, opCodeNot[0], opcode[1], opCodeNot[2], opCodeNot[3], opCodeNot[4], opCodeNot[5]);
and and_subi(subi, opcode[0], opcode[1], opCodeNot[2], opCodeNot[3], opCodeNot[4], opCodeNot[5]);
and and_andi(andi, opCodeNot[0], opCodeNot[1], opcode[2], opCodeNot[3], opCodeNot[4], opCodeNot[5]);
and and_ori(ori, opcode[0], opCodeNot[1], opcode[2], opCodeNot[3], opCodeNot[4], opCodeNot[5]);
and and_lw(lw, opCodeNot[0], opCodeNot[1], opCodeNot[2], opcode[3], opCodeNot[4], opCodeNot[5]);
and and_sw(sw, opCodeNot[0], opCodeNot[1], opCodeNot[2], opCodeNot[3], opcode[4], opCodeNot[5]);
and and_lb(lb, opcode[0], opCodeNot[1], opCodeNot[2], opcode[3], opCodeNot[4], opCodeNot[5]);
and and_sb(sb, opcode[0], opCodeNot[1], opCodeNot[2], opCodeNot[3], opcode[4], opCodeNot[5]);
and and_slti(slti, opcode[0], opcode[1], opcode[2], opCodeNot[3], opCodeNot[4], opCodeNot[5]);
and and_beq(beq, opcode[0], opcode[1], opCodeNot[2], opCodeNot[3], opCodeNot[4], opcode[5]);
and and_bne(bne, opcode[0], opcode[1], opcode[2], opCodeNot[3], opCodeNot[4], opcode[5]);
and and_j(j, opCodeNot[0], opCodeNot[1], opCodeNot[2], opcode[3], opcode[4], opcode[5]);
and and_jal(jal, opcode[0], opCodeNot[1], opCodeNot[2], opcode[3], opcode[4], opcode[5]);

and and_move(move, opCodeNot[0], opCodeNot[1], opCodeNot[2], opCodeNot[3], opCodeNot[4], opcode[5]);

or regDst_or(regDst, rtype, rtype);
or aluSrc_or(ALUsrc, addi, subi, andi, ori, lw, sw, lb, sb, slti);

or memRead_or(memRead, lw, lb);
or memWrite_or(memWrite, sw, sb);
or byteOperations_or(byteOperations, lb, sb);

or branch_or(branch, beq, bne);
or jump_or(jump, j, jal);

or regWrite_or(regWrite, rtype, addi, subi, andi, ori, lw, lb, slti, jal, move);

or aluop2_or(ALUop[2], rtype, addi, subi, lw, sw, lb, sb, slti, beq, bne);
or aluop1_or(ALUop[1], rtype, subi, beq, bne);
or aluop0_or(ALUop[0], rtype, addi, ori, lw, sw, lb, sb);


endmodule