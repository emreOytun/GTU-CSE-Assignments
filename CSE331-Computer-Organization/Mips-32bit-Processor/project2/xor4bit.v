module xor4bit(output[3:0] result, input[3:0] a, input[3:0] b);

xor xor1(result[0], a[0], b[0]);
xor xor2(result[1], a[1], b[1]);
xor xor3(result[2], a[2], b[2]);
xor xor4(result[3], a[3], b[3]);

endmodule