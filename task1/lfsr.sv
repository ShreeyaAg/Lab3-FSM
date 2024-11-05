module lfsr(
    input   logic       clk,        //clock
    input   logic       rst,        //reset, bring state to 1 not 0
    input   logic       en,         //enable
    output  logic [3:0] data_out    //pseudo-random output
);

logic [4:1] sreg; //initial error, had to intitiliase the sreg

always_ff @(posedge clk, posedge rst) //asynchronous ff
    if (rst)
        sreg <= 4'b1; //set sreg to 0001, needs to output 0010 from XOR (only works if non-zero)
    else if (en == 1)
        sreg <= {sreg[3:1], sreg[4] ^ sreg[3]};

assign data_out = sreg;

endmodule
