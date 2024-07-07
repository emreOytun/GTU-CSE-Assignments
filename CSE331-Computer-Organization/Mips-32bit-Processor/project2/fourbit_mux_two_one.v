module fourbit_mux_two_one(output[3:0] out, input[3:0] in0, in1, input sel);

onebit_mux_two_one mux_two_one1(out[0], in0[0], in1[0], sel);
onebit_mux_two_one mux_two_one2(out[1], in0[1], in1[1], sel);
onebit_mux_two_one mux_two_one3(out[2], in0[2], in1[2], sel);
onebit_mux_two_one mux_two_one4(out[3], in0[3], in1[3], sel);

endmodule