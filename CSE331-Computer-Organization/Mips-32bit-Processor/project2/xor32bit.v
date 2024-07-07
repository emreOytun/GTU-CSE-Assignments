module xor32bit(output[31:0] result, input[31:0] a, input[31:0] b);

xor4bit xor4bit1(result[3:0], a[3:0], b[3:0]);
xor4bit xor4bit2(result[7:4], a[7:4], b[7:4]);
xor4bit xor4bit3(result[11:8], a[11:8], b[11:8]);
xor4bit xor4bit4(result[15:12], a[15:12], b[15:12]);
xor4bit xor4bit5(result[19:16], a[19:16], b[19:16]);
xor4bit xor4bit6(result[23:20], a[23:20], b[23:20]);
xor4bit xor4bit7(result[27:24], a[27:24], b[27:24]);
xor4bit xor4bit8(result[31:28], a[31:28], b[31:28]);

endmodule