#include <systemc.h>

#include "place.h"
#include "transition.h"
#include "subnet.h"

// Toplevel:
SC_MODULE(toplevel){
    transition t1("trans1");
    transition t2("trans2");    
    
    SC_CTOR(toplevel){
        SC_THREAD(process);
    }


void process(){
    while (true){
        wait(10,SC_NS);
        t1.fire();
        wait(10,SC_NS);
        t1.fire();
        wait(10, SC_NS);
        t2.fire();
        sc_stop();
    }

}


int sc_main(int, char**)
{
    // TODO
    toplevel t("top1");

    sc_start();
    return 0;
}
