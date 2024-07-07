module mod(output[31:0] result, output[31:0] temp, input CLK, input[31:0] a, input[31:0] b, input[31:0] sub, input reset);

wire selA, we, ltb, saveResult, saveSub;

mod_cu mod_control(.we(we), .selA(selA), .saveResult(saveResult), .saveSub(saveSub), .CLK(CLK), .ltb(ltb), .reset(reset));
mod_dp mod_datapath(.result(result), .temp(temp), .ltb(ltb), .CLK(CLK), .a(a), .b(b), .we(we), .selA(selA), .saveResult(saveResult), .sub(sub), .saveSub(saveSub));

endmodule