module inverter32(output[31:0] result, input[31:0] in, input invert);

xor xor1(result[0], in[0], invert);
xor xor2(result[1], in[1], invert);
xor xor3(result[2], in[2], invert);
xor xor4(result[3], in[3], invert);
xor xor5(result[4], in[4], invert);
xor xor6(result[5], in[5], invert);
xor xor7(result[6], in[6], invert);
xor xor8(result[7], in[7], invert);
xor xor9(result[8], in[8], invert);
xor xor10(result[9], in[9], invert);
xor xor11(result[10], in[10], invert);
xor xor12(result[11], in[11], invert);
xor xor13(result[12], in[12], invert);
xor xor14(result[13], in[13], invert);
xor xor15(result[14], in[14], invert);
xor xor16(result[15], in[15], invert);
xor xor17(result[16], in[16], invert);
xor xor18(result[17], in[17], invert);
xor xor19(result[18], in[18], invert);
xor xor20(result[19], in[19], invert);
xor xor21(result[20], in[20], invert);
xor xor22(result[21], in[21], invert);
xor xor23(result[22], in[22], invert);
xor xor24(result[23], in[23], invert);
xor xor25(result[24], in[24], invert);
xor xor26(result[25], in[25], invert);
xor xor27(result[26], in[26], invert);
xor xor28(result[27], in[27], invert);
xor xor29(result[28], in[28], invert);
xor xor30(result[29], in[29], invert);
xor xor31(result[30], in[30], invert);
xor xor32(result[31], in[31], invert);

endmodule