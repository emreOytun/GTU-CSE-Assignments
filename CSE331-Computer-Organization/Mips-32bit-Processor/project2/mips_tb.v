module mips_tb();

reg clock = 1;

mips mips1(clock);

// Clock generate
always 
begin
	#15
	clock = ~clock;
end

endmodule