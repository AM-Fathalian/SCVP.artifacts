#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>

#include "place.h"
using namespace std;

// Transition:
SC_MODULE (transition){
    sc_port<placeInterface<unsigned int>> in, out;

    SC_CTOR(transition){

    }

    void fire(){
        if (in->testTokens() != 0){
            cout << this->name() << " : Fired" << endl;
            in -> removeTokens(1);
            out -> addTokens(1);
        }
        else
           cout << this->name() << ": NOT Fired" << endl;
    }
};
#endif // TRANSITION_H
