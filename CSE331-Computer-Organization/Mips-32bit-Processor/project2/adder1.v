module adder1(output s, input a, b, cin);

wire wire1;
xor xor1(wire1, a, b);
xor xor2(s, wire1, cin);

endmodule