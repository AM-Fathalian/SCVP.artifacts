#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>

#include "place.h"
using namespace std;

// Transition:
template<unsigned int N = 1, unsigned int M = 1, unsigned int L=0>
SC_MODULE (transition){
    sc_port<placeInterface, N, SC_ALL_BOUND> in;
    sc_port<placeInterface, M, SC_ALL_BOUND> out;
    sc_port<placeInterface, L, SC_ZERO_OR_MORE_BOUND> inhibitors;
    bool flag_N = false;
    SC_CTOR(transition){

    }

    void fire(){
        // 
        for(int i=0; i < in.size(); i++){
                if (in[i]->testTokens() == 0){
                    std::cout << this->name() << " : NOT Fired" << std::endl;
                    flag_N = false;
                    return;
                }
                    // continue;
            }
        if (inhibitors.size() > 0){
            for(int k = 0; k < inhibitors.size(); k++){
                if (inhibitors[k]->testTokens()){
                    cout << this->name() << " : Not Fired (Inhibited)" << endl;
                    return;
                }
            }
        }
        for (int i = 0; i < in.size(); i++)
            in[i] -> removeTokens();
        
        for (int j = 0; j < out.size(); j++)
            out[j] -> addTokens();
        
        cout << this->name() << " : Fired" << endl;

        // 
    }
};
#endif // TRANSITION_H
