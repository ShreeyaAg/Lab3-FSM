#include "verilated_vcd_c.h"
#include "verilated.h"
#include "Vf1_cycle.h"
#include "vbuddy.cpp"

#define MAX_SIM_CYC 100000

int main(int argc, char **argv, char **env){
    int simcyc;     //simulation clock count
    int tick;       //each clk cycle has 2 ticks for 2 edges
    int lights = 0; //state to toggle LED lights

    Verilated::commandArgs(argc, argv);
    //init top verilog instance
    Vf1_cycle * top = new Vf1_cycle;
    //init tarce dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("clktick.vcd");

    //init Vbuddy
    if (vbdOpen()!=1) return (-1);
    vbdHeader("LT3T2: Challenge");
    vbdSetMode(1);                  //flag mode set to 1

    //initialise simulation inputs
    top->clk = 1;
    top->en = 1;
    top->rst = 0;
    top-> N = vbdValue();

    //run simulation for MAX_SIM_CYC clock cycles
    for(simcyc=0; simcyc<MAX_SIM_CYC; simcyc++){
        //dump variables into VCD file and toggle clock
        for(tick=0; tick<2; tick++){
            tfp->dump (2*simcyc+tick);
            top->clk = !top->clk;
            top->eval ();
        }

        //display toggle neopixel
        vbdBar(top->out & 0xFF);

        //set up input signals of the testbench
        top->rst = (simcyc < 2);    //assert reset for 1st cycle
        top->en = (simcyc > 2);
        top-> N = vbdValue();
        vbdCycle(simcyc);

        if(Verilated::gotFinish()) exit(0);
    }

    vbdClose();
    tfp->close();
    exit(0);
}
