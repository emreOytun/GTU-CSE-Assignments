module addSubBlock(output[31:0] result, input[31:0] a, input[31:0] b, input sub);

wire[31:0] bInverterRes;
inverter32 inverter1(.result(bInverterRes), .in(b), .invert(sub));
adder adder1(.s(result), .a(a), .b(bInverterRes), .cin(sub));

endmodule