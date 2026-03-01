#ifndef NAND_H
#define NAND_H

#include <systemc.h>


SC_MODULE(nand){
    // Port, methos and constructor declarations go here.
    private:
        sc_in<bool> A;
        sc_in<bool> B;
        sc_out<bool> Z;
    
    public:
        SC_CTOR(nand) : A("A") , B("B") , Z("Z") {

            SC_METHOD(do_nand);
            sensitive << A << B;    // This process is sensitive to changes in signals A and B. Therefore, it
                                    // will be triggered every time there is a change in any of these
                                    // two signals.


        }

        void do_nand(){
            Z.write(!(A.read() && B.read()));
        }

};

#endif



// //     public:
//         sc_in<bool> A;
//         sc_in<bool> B;
//         sc_out<bool> Z;

//         SC_CTOR(nand){
//             SC_METHOD(process);
//             sensitive << A << B;
//         }

//         void process(){
//             Z.write(!(A.read() && B.read()));
//         }