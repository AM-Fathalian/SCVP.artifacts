#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>

#include "place.h"
using namespace std;

// Transition:
template<unsigned int N = 1, unsigned int M = 1>
SC_MODULE (transition){
    sc_port<placeInterface, N, SC_ALL_BOUND> in;
    sc_port<placeInterface, M, SC_ALL_BOUND> out;
    bool flag_N = false;
    SC_CTOR(transition){

    }

    void fire(){
        // 
        for(int i=0; i < N; i++){
                if (in[i]->testTokens() != 0)
                    flag_N = true;
                else{
                    std::cout << name() << " : NOT Fired" << std::endl;
                    flag_N = false;
                    return;
                }
            }
        
        for (int i = 0; i < in.size(); i++){
            in[i] -> removeTokens();
        }
        for (int j = 0; j < out.size(); j++){
            out[j] -> addTokens();
        }
        cout << this->name() << " : Fired" << endl;

        // 
    }
};
#endif // TRANSITION_H
