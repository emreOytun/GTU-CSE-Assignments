module alu(output[31:0] alu_result, output zero_bit, input[31:0] alu_src1, input[31:0] alu_src2, input[2:0] alu_ctr);

wire[31:0] andResult, orResult, xorResult, norResult, addSubResult, lessThanResult, modResult;
wire[31:0] temp;

// Set the reset signal as always 0 since the mod operation is not needed.
wire reset;
wire CLK;
and andResetForMaking0(reset, 1'b0, 1'b0);
and andCLKForMaking0(CLK, 1'b0, 1'b0);

and32bit and32bit1(andResult, alu_src1, alu_src2);
or32bit or32bit1(orResult, alu_src1, alu_src2);
xor32bit xor32bit1(xorResult, alu_src1, alu_src2);
nor32bit nor32bit1(norResult, alu_src1, alu_src2);

// Make subract operation except add.
wire isAdd, isNotAdd;
wire AluOp1Not;
not not1(AluOp1Not, alu_ctr[1]);
and and1(isAdd, alu_ctr[0], AluOp1Not, alu_ctr[2]);
not not2(isNotAdd, isAdd);

// Make addition or subtraction according to isNotAdd signal.
wire[31:0] subtractedNumber;
wire isMod;
and and3(isMod, alu_ctr[0], alu_ctr[1], alu_ctr[2]);

thirtytwobit_mux_two_one mux_two_one9(.out(subtractedNumber), .in0(alu_src1), .in1(temp), .sel(isMod));
addSubBlock addSubBlock1(.result(addSubResult), .a(subtractedNumber), .b(alu_src2), .sub(isNotAdd));

// If given numbers are different sign, then the less than can be determined directly without using subtraction.
wire lessThanSignal, differentSign;
xor xor1(differentSign, alu_src1[31], alu_src2[31]);

// If the signs are different and a is negative; or if the signs are the same and msb in subtract result is 1
// then it's true.
onebit_mux_two_one mux_two_one1(.out(lessThanSignal), .in0(addSubResult[31]), .in1(alu_src1[31]), .sel(differentSign));
thirtytwobit_mux_two_one mux_two_one2(.out(lessThanResult), .in0(32'b00000000000000000000000000000000), .in1(32'b00000000000000000000000000000001), .sel(lessThanSignal));

mod mod1(.result(modResult), .temp(temp), .CLK(CLK), .a(alu_src1), .b(alu_src2), .sub(addSubResult), .reset(reset));

wire[31:0] result0_0, result0_1, result0_2;
thirtytwobit_mux_two_one mux_two_one3(.out(result0_0), .in0(andResult), .in1(orResult), .sel(alu_ctr[0]));
thirtytwobit_mux_two_one mux_two_one4(.out(result0_1), .in0(xorResult), .in1(norResult), .sel(alu_ctr[0]));
thirtytwobit_mux_two_one mux_two_one5(.out(result0_2), .in0(lessThanResult), .in1(modResult), .sel(alu_ctr[0]));

wire[31:0] result1_0, result1_1;
thirtytwobit_mux_two_one mux_two_one6(.out(result1_0), .in0(result0_0), .in1(result0_1), .sel(alu_ctr[1]));

wire isOp0And1Diff;
xor and2(isOp0And1Diff, alu_ctr[1], alu_ctr[0]); 
thirtytwobit_mux_two_one mux_two_one7(.out(result1_1), .in0(result0_2), .in1(addSubResult), .sel(isOp0And1Diff));

thirtytwobit_mux_two_one mux_two_one8(.out(alu_result), .in0(result1_0), .in1(result1_1), .sel(alu_ctr[2]));

wire orAllResultBits;
or orForAll(
    orAllResultBits,
    addSubResult[31],
    addSubResult[30],
    addSubResult[29],
    addSubResult[28],
    addSubResult[27],
    addSubResult[26],
    addSubResult[25],
    addSubResult[24],
    addSubResult[23],
    addSubResult[22],
    addSubResult[21],
    addSubResult[20],
    addSubResult[19],
    addSubResult[18],
    addSubResult[17],
    addSubResult[16],
    addSubResult[15],
    addSubResult[14],
    addSubResult[13],
    addSubResult[12],
    addSubResult[11],
    addSubResult[10],
    addSubResult[9],
    addSubResult[8],
    addSubResult[7],
    addSubResult[6],
    addSubResult[5],
    addSubResult[4],
    addSubResult[3],
    addSubResult[2],
    addSubResult[1],
    addSubResult[0]
  );
not not3(zero_bit, orAllResultBits);

endmodule