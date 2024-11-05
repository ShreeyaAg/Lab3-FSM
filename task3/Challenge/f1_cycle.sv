module f1_cycle #(
    parameter WIDTH = 16
)(
    input logic         clk,
    input logic         rst,
    input logic         en,
    input logic [WIDTH-1:0] N,
    output logic [7:0]   out
);

logic tick;

clktick clktick_instance(
    .clk(clk),
    .en(en),
    .rst(rst),
    .N(N),
    .tick(tick)
);

f1_fsm f1_fsm_instance(
    .clk(clk),
    .rst(rst),
    .en(tick),
    .out(out)
);

endmodule
