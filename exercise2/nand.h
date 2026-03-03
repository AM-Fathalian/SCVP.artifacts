#ifndef NAND_H
#define NAND_H

#include <systemc.h>

//  Instead of class nand : public sc_module, we can also write SC_MODULE(nand)
//  and then write the constructor and methods of the module inside the body of the macro.
SC_MODULE(nand){
    public:
    // Port, methods and constructor declarations go here.
        sc_in<bool> A ;
        sc_in<bool> B;
        sc_out<bool> Z;
    
        SC_CTOR(nand) {

            SC_METHOD(do_nand); // This is just to register the process(do_nand) with the kernel;
                                //  so that the kernel can call this process when it is triggered by signals in sensitivity list.
           
             sensitive << A << B;    // This process is sensitive to changes in signals A and B. Therefore, it
                                     // will be triggered every time there is a change in them.

        }

        private:
        
        void do_nand(){                         // this is a process.

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