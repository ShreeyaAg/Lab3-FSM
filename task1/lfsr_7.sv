module lfsr_7 (
    input   logic       clk,
    input   logic       rst,
    input   logic       en,
    output  logic [6:0] data_out //modify into 7-bit PRBS generator
);

logic[4:1] sreg;

always_ff @ (posedge clk, posedge rst)
    if (rst)
        sreg <= 7'b1; //reset 7 bit counter back to 1
    else if (en == 1)
        sreg <= {sreg[6:1], sreg[7] ^ sreg[3]}; //change polynomial for 7 bits, from 1 + X^3 + X^7
        //allow PBRS to do 7 XOR 3
assign data_out = sreg
endmodule
