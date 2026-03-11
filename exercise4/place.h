#ifndef PLACE_H
#define PLACE_H

#include <systemc.h>

// Place Interface:
template <class T>
class placeInterface : public sc_interface{
    public:
    virtual void removeTokens(T) = 0;
    virtual void addTokens(T) = 0;
    virtual T testTokens() = 0;
    
};




// Place Channel:
template <class T>
class place : public placeInterface<T>, public sc_prim_channel{

    private:
        T tokens;

    public:
    place (){
        tokens = 0;        
    };

    void removeTokens(T){
        tokens -= T;
    }

    void addTokens(T){
        tokens += T;
    }

    T testTokens(){
        return tokens;
    }

};
#endif // PLACE_H
