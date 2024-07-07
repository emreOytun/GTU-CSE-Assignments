module shift_left_2 (
output [31:0] shifted_address,
input [31:0] address);

thirtytwobit_mux_two_one mux1(.out(shifted_address), .in0({address[29:0], 2'b00}), .in1(32'b0), .sel(1'b0));

endmodule