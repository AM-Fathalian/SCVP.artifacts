#include <systemc.h>

#include "stim.h"
#include "exor.h"
#include "mon.h"

int sc_main(int, char**)
{
    sc_signal<bool> sigA, sigB, sigZ;
    // sc_signal<bool> clk;

    sc_clock clock("Clk", sc_time(10, SC_NS));


    stim Stim1("Stimulus");
    Stim1.A.bind(sigA);
    Stim1.B.bind(sigB);
    Stim1.Clk.bind(clock);

    exor DUT("exor");
    DUT.A.bind(sigA);
    DUT.B.bind(sigB);
    DUT.Z.bind(sigZ);

    Monitor mon("Monitor");
    mon.A.bind(sigA);
    mon.B.bind(sigB);
    mon.Z.bind(sigZ);
    mon.Clk.bind(clock);
;
    // Setup Waveform Tracing:
    sc_trace_file *wf = sc_create_vcd_trace_file("exor_trace");
    sc_trace(wf, sigA, "In_A");
    sc_trace(wf, sigB, "In_B");
    sc_trace(wf, sigZ, "Out_Z");
    sc_trace(wf, clock, "clk");

    // Start Simulation
    sc_start();

    // Close Trace File:
    sc_close_vcd_trace_file(wf);
    return 0;
}
