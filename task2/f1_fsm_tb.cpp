#include "verilated_vcd_c.h"
#include "verilated.h"
#include "Vf1_fsm.h"
#include "vbuddy.cpp"

#define MAX_SIM_CYC 100000000
#define ADDRESS_WIDTH 8

int main(int argc, char **argv, char **env){
    int simcyc;         //simulation clock count
    int tick;           //each clk cycle has 2 ticks for 2 edges

    Verilated::commandArgs(argc, argv);
    //init top verilog instance
    Vf1_fsm* top = new Vf1_fsm;
    //init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("f1_fsm.vcd");

    //init Vbuddy
    if (vbdOpen()!=1) return (-1);
    vbdHeader("L2T1: f1");
    //vbdSetMode(1);        //flag mode set to one-shot

    //init simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 1;

    //run simulation for MAX_SIM_CYC clock cycles
    for(simcyc=0; simcyc<MAX_SIM_CYC; simcyc++){
        //dump variables into VCD file and toggle clock
        for (tick = 0; tick < 2; tick++){
            tfp->dump (2*simcyc+tick);
            top->clk = !top->clk;
            top->eval();
        }
        top->rst = 0;
        top->en = vbdFlag();
        vbdSetMode(1);

        //plot ROM output and print cycle count
        vbdBar(top->data_out & 0xFF);

        //either simulation finished, or 'q' is pressed
        if((Verilated::gotFinish()) || (vbdGetkey() == 'q'))
        exit(0);
    }

    vbdClose();
    tfp->close();
    exit(0);
}