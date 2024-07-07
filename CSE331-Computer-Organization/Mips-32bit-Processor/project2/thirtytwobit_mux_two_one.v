module thirtytwobit_mux_two_one(output[31:0] out, input[31:0] in0, in1, input sel);

fourbit_mux_two_one mux_two_one1(.out(out[3:0]), .in0(in0[3:0]), .in1(in1[3:0]), .sel(sel));
fourbit_mux_two_one mux_two_one2(.out(out[7:4]), .in0(in0[7:4]), .in1(in1[7:4]), .sel(sel));
fourbit_mux_two_one mux_two_one3(.out(out[11:8]), .in0(in0[11:8]), .in1(in1[11:8]), .sel(sel));
fourbit_mux_two_one mux_two_one4(.out(out[15:12]), .in0(in0[15:12]), .in1(in1[15:12]), .sel(sel));
fourbit_mux_two_one mux_two_one5(.out(out[19:16]), .in0(in0[19:16]), .in1(in1[19:16]), .sel(sel));
fourbit_mux_two_one mux_two_one6(.out(out[23:20]), .in0(in0[23:20]), .in1(in1[23:20]), .sel(sel));
fourbit_mux_two_one mux_two_one7(.out(out[27:24]), .in0(in0[27:24]), .in1(in1[27:24]), .sel(sel));
fourbit_mux_two_one mux_two_one8(.out(out[31:28]), .in0(in0[31:28]), .in1(in1[31:28]), .sel(sel));

endmodule