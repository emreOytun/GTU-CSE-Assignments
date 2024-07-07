module register(input CLK, input we, input in, output reg data);

always@(posedge CLK)
begin
	if (we) data <= in;
end

endmodule