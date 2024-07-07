module sign_extend (
output [31:0] sign_ext_imm,
input [15:0] imm);

thirtytwobit_mux_two_one mux1(.out(sign_ext_imm), .in0({16'b0000000000000000, imm}), .in1({16'b1111111111111111, imm}), .sel(imm[15]));

endmodule