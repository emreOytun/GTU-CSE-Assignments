module adder4_g_p_G_P_signals(
output[3:0] g,
output[3:0] p,
output G,
output P,
input[3:0] a,
input[3:0] b);

// gi = ai * bi
and and0(g[0], a[0], b[0]);
and and1(g[1], a[1], b[1]);
and and2(g[2], a[2], b[2]);
and and3(g[3], a[3], b[3]);

// pi = ai + bi
or or0(p[0], a[0], b[0]);
or or1(p[1], a[1], b[1]);
or or2(p[2], a[2], b[2]);
or or3(p[3], a[3], b[3]);

// G = g3 + p3g2 + p3p2g1 + p3p2p1g0
wire p3g2, p3p2g1, p3p2p1g0;
and and_p3g2(p3g2, p[3], g[2]);
and and_p3p2g1(p3p2g1, p[3], p[2], g[1]);
and and_p3p2p1g0(p3p2p1g0, p[3], p[2], p[1], g[0]);
or or_G(G, g[3], p3g2, p3p2g1, p3p2p1g0);

// P = p3p2p1p0
and and_P(P, p[3], p[2], p[1], p[0]);

endmodule