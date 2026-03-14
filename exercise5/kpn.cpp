#include <unistd.h>
#include <systemc.h>

#include "kpn.h"
using namespace std;

void kpn::split(){
    while (true){ // with while always do return or break somewhere. (what is the difference??)
        // wait(5, SC_NS);
        e = b.read();
        a.write(e);
        d.write(e);
        
        ++cnt;
        cout << " @ " << sc_time_stamp() << " e = " << e << endl;
        if(cnt >= 10){
            // wait(SC_ZERO_TIME);
            sc_stop();
            break;
        }
    }
}


void kpn::add(){

    while(true){
        // wait(sc_time(1,SC_NS));
        b.write(a.read() + c.read());
    }
}


void kpn::delay(){
    while(true){
        // wait(sc_time(10,SC_NS));
        c.write(d.read());
    }
}
    // virtual void process() = 0;




