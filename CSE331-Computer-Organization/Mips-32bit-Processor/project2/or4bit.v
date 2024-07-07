module or4bit(output[3:0] result, input[3:0] a, input[3:0] b);

or or1(result[0], a[0], b[0]);
or or2(result[1], a[1], b[1]);
or or3(result[2], a[2], b[2]);
or or4(result[3], a[3], b[3]);

endmodule