#include <systemc.h>

#include "place.h"
#include "transition.h"
#include "subnet.h"


// SC_MODULE(toplevel){
//     place<1, 1> IDLE;
//     place<3, 3> ACTIVE;
//     transition<1, 1, 1> RD;
//     transition<1, 1> PRE;
//     transition<1, 1> WR;
//     transition<1, 1> ACT;
//     // place<1,1> BUSY;
    
//     SC_CTOR(toplevel) : RD("RD"), PRE("PRE"), WR("WR"), ACT("ACT"){
//         ACT.in.bind(IDLE);
//         ACT.out.bind(ACTIVE);
//         RD.in.bind(ACTIVE);
//         RD.out.bind(ACTIVE);
//         // RD.inhibitors.bind(BUSY);
        
//         PRE.in.bind(ACTIVE);
//         PRE.out.bind(IDLE);
//         WR.in.bind(ACTIVE);
//         WR.out.bind(ACTIVE);


//         // Initialize with tokens
//         // p1.addTokens();  // Start with 1 token in p1
//         IDLE.addTokens();
//         SC_THREAD(process);
//     }
//     void process(){
//         while (true){
//             wait(10,SC_NS);
//             ACT.fire();
//             wait(10,SC_NS);
//             ACT.fire();
//             wait(10, SC_NS);
//             RD.fire();
//             wait(10,SC_NS);
//             WR.fire();
//             wait(10,SC_NS);
//             PRE.fire();
//             wait(10,SC_NS);
//             ACT.fire();
//             // wait(SC_ZERO_TIME);
//             sc_stop();
//         }
//     }

// };

// TopLevel:
    SC_MODULE(toplevel){
        place<2, 2> IDLE;
        subnet s1, s2;

        SC_CTOR(toplevel): s1("s1"), s2("s2") {
            s1.in.bind(IDLE);
            s1.out.bind(IDLE);
            s2.in.bind(IDLE);
            s2.out.bind(IDLE);

            IDLE.addTokens();

            SC_THREAD(process);
        }

        void process(){
            while (true){
                wait(10, SC_NS);
                s1.ACT.fire();
                wait(10, SC_NS);
                s1.ACT.fire();
                wait(10, SC_NS);
                s1.RD.fire();
                wait(10, SC_NS);
                s1.WR.fire();
                wait(10, SC_NS);
                s1.PRE.fire();
                wait(10, SC_NS);
                s1.ACT.fire();
                wait(10, SC_NS);
                s2.ACT.fire();
                wait(10, SC_NS);
                s2.ACT.fire();
                wait(10, SC_NS);
                s1.PRE.fire();
                wait(10, SC_NS);
                s2.PRE.fire();
                wait(10, SC_NS);
                sc_stop();
            }
        }
    };




int sc_main(int, char**)
{
    // TODO
    toplevel t("t");

    sc_start();
    return 0;
}
