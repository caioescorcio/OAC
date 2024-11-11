module mod_xor (
    input   [31:0]    A,
    input   [31:0]    B,
    output  [31:0]    R,
);
    assign R = A ^ B;
endmodule