module and32bit(output[31:0] result, input[31:0] a, input[31:0] b);

and4bit and4bit1(result[3:0], a[3:0], b[3:0]);
and4bit and4bit2(result[7:4], a[7:4], b[7:4]);
and4bit and4bit3(result[11:8], a[11:8], b[11:8]);
and4bit and4bit4(result[15:12], a[15:12], b[15:12]);
and4bit and4bit5(result[19:16], a[19:16], b[19:16]);
and4bit and4bit6(result[23:20], a[23:20], b[23:20]);
and4bit and4bit7(result[27:24], a[27:24], b[27:24]);
and4bit and4bit8(result[31:28], a[31:28], b[31:28]);

endmodule