module onebit_mux_two_one(output out, input in0, input in1, input sel);

wire w0, w1, selnot;

not not1(selnot, sel);

and and1(w0, in0, selnot);
and and2(w1, in1, sel);

or(out, w0, w1);

endmodule