#ifndef SUBNET_H
#define SUBNET_H

#include <systemc.h>

#include "place.h"
#include "transition.h"

// Subnet:
SC_MODULE(subnet){
    place<3, 3> ACTIVE;
    transition<1, 1> RD;
    transition<1, 1> PRE;
    transition<1, 1> WR;
    transition<1, 1> ACT;
    // place<1,1> BUSY;
    sc_port<placeInterface> in, out; 
    
    SC_CTOR(subnet) : RD("RD"), PRE("PRE"), WR("WR"), ACT("ACT"), in("in"), out("out"){
        ACT.in.bind(in);
        ACT.out.bind(ACTIVE);
        RD.in.bind(ACTIVE);
        RD.out.bind(ACTIVE);
        PRE.in.bind(ACTIVE);
        PRE.out.bind(out);
        WR.in.bind(ACTIVE);
        WR.out.bind(ACTIVE);


    }
};
#endif // SUBNET_H
