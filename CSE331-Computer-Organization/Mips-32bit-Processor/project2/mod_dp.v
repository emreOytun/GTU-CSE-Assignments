module mod_dp(output reg[31:0] result, output reg[31:0] temp, output ltb, input CLK, input[31:0] a, input[31:0] b, input we, input selA, input saveResult, input[31:0] sub, input saveSub);

reg[31:0] subReg;
wire[31:0] tempNextValueFinal;
or or1(ltb, sub[31], 1'b0);

thirtytwobit_mux_two_one mux_for_temp(.out(tempNextValueFinal), .in0(subReg), .in1(a), .sel(selA));

always@(*)
begin
	if (we) temp <= tempNextValueFinal;
	if (saveSub) subReg <= sub;
	if (saveResult) result <= temp;
end

endmodule