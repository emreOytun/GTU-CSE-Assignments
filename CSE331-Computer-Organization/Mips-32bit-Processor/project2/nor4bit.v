module nor4bit(output[3:0] result, input[3:0] a, input[3:0] b);

nor nor1(result[0], a[0], b[0]);
nor nor2(result[1], a[1], b[1]);
nor nor3(result[2], a[2], b[2]);
nor nor4(result[3], a[3], b[3]);

endmodule