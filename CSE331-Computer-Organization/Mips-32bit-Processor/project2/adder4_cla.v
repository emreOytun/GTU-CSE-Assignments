module adder4_cla(
output[3:0] s,
input[3:0] g,
input[3:0] p,
input[3:0] a,
input[3:0] b,
input cin);

wire c1, c2, c3;

// c1 = g0 + p0c0
wire p0c0;
and and4(p0c0, p[0], cin);
or or4(c1, g[0], p0c0);

// c2 = g1 + p1g0 + p1p0c0
wire p1g0, p1p0c0;
and and5(p1g0, p[1], g[0]);
and and6(p1p0c0, p[1], p0c0);
or or5(c2, g[1], p1g0, p1p0c0);

// c3 = g2 + p2g1 + p2p1g0 + p2p1p0c0
wire p2g1, p2p1g0, p2p1p0c0;
and and7(p2g1, p[2], g[1]);
and and8(p2p1g0, p[2], p1g0);
and and9(p2p1p0c0, p[2], p1p0c0);
or or6(c3, g[2], p2g1, p2p1g0, p2p1p0c0);

adder1 adder1_0(.s(s[0]), .a(a[0]), .b(b[0]), .cin(cin));
adder1 adder1_1(.s(s[1]), .a(a[1]), .b(b[1]), .cin(c1));
adder1 adder1_2(.s(s[2]), .a(a[2]), .b(b[2]), .cin(c2));
adder1 adder1_3(.s(s[3]), .a(a[3]), .b(b[3]), .cin(c3));

endmodule