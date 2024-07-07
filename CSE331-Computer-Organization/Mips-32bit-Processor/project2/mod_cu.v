module mod_cu(output reg we, output reg selA, output reg saveResult, output reg saveSub, input CLK, input ltb, input reset);

localparam	INIT = 2'b00,
				SUBTRACT = 2'b01,
				CHECK = 2'b10,
				END = 2'b11;
				
reg [1:0] curr_state = INIT;
reg [1:0] next_state = INIT;
				
always @(posedge CLK)
begin
	if (reset)
		curr_state <= INIT;
	else
		curr_state <= next_state;
end

always @(*)
begin
	case(curr_state)
	INIT: begin
				next_state <= SUBTRACT;
			end
			
	SUBTRACT: begin
					next_state <= CHECK;
				 end
	
	CHECK: begin
			 if (ltb)
				next_state <= END;
			 else 
				next_state <= SUBTRACT;
			 end
	
	END: begin
			 next_state <= INIT;
		  end
	endcase
end

always @(*)
begin
	case(curr_state)
	INIT: begin
			selA = 1'b1;
			we = 1'b1;
			saveSub = 1'b1;
			saveResult = 1'b0;
			end
			
	SUBTRACT: begin
				 saveSub = 1'b0;
				 we = 1'b1;
				 selA = 1'b0;
				 saveResult = 1'b0;
				 end
	
	CHECK: begin
			 we = 1'b0;
			 saveSub = 1'b1;
			 selA = 1'b0;
			 saveResult = 1'b0;
			 end
			 
	 END: begin
			saveResult = 1'b1;
			we = 1'b0;
			selA = 1'b0;
			saveSub = 1'b0;
			end
	endcase

end

endmodule