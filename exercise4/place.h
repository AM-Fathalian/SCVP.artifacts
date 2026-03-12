#ifndef PLACE_H
#define PLACE_H

#include <systemc.h>

// Place Interface:
// template <class T>
class placeInterface : public sc_interface{
    public:
    virtual void removeTokens() = 0;
    virtual void addTokens() = 0;
    virtual bool testTokens() = 0;
    
};




// Place Channel:
// template <class T> 
template<unsigned int Win = 1, unsigned int Wout = 1>
class place : public placeInterface, public sc_prim_channel{

    private:
        unsigned int tokens;

    public:
    place (){
        tokens = 0;        
    };

    void removeTokens(){
        tokens -= Wout;
    }

    void addTokens(){
        tokens += Win;
    }

    bool testTokens(){
        if (tokens >= Wout)
            return true;
        else
            return false;
    }

};
#endif // PLACE_H
