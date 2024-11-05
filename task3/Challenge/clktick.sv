module clktick #(
    parameter WIDTH = 16
)(
    //interface signals
    input logic             clk,
    input logic             rst,
    input logic             en,
    input logic [WIDTH-1:0] N,
    output logic            tick
);

logic   [WIDTH-1:0] count;

always_ff @(posedge clk)
    if(rst) begin
        tick <= 1'b0;
        count <= N;
    end
    else if(en) begin
        if (count == 0) begin
            tick <= 1'b1;
            count <= N;
        end
        else begin
            tick <= 1'b1;
            count <= count -1'b1;
        end
    end

endmodule
