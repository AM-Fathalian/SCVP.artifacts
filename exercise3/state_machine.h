#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <systemc.h>
#include <iostream>

enum base {Start, G, GA, GAA, GAAG};


SC_MODULE(StateMachine){
    public:
        sc_in<bool> clk;
        sc_in<char> input;

        void process();

        SC_CTOR(StateMachine){
            SC_METHOD(process);
            sensitive << clk.pos();
            dont_initialize();

            // Then initializing the state to Start.
            current_state = Start;
            freq = 0;
            position = 0;
            
        }

    // Define the inernal signals/wires inside the private.
    private:
        base current_state;
        uint64_t freq;
        uint64_t position;

};


#endif // STATE_MACHINE_H


