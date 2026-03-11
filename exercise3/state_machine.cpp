#include <iostream>

#include "state_machine.h"


void StateMachine::process(){
    char current_char = input.read();
    position++;
    switch(current_state){
        case Start:
            if(current_char == 'G')
                current_state = G;
            else
                current_state = Start; // C || A || T
            break;
        
        case G:
            if(current_char == 'A')
                current_state = GA;
            else if (current_char == 'G')
                current_state = G;
            else 
                current_state = Start;
            break;

        case GA:
            if (current_char == 'A') 
                current_state = GAA;
            else if (current_char == 'G') 
                current_state = G;
            else 
                current_state = Start; // C || T
            break;
        
        case GAA:
            if (current_char == 'G')
                current_state = GAAG;
            else if (current_char == 'A')
                current_state = GAA;
            else 
                current_state = Start;
            break;
        
        case GAAG:
            if (current_char == 'G')
                current_state = G;
            else
                current_state = Start;

        default:
            current_state = Start;
            break;
    }

    if (current_state == GAAG) {
        cout << " @: " << sc_time_stamp() << " Found GAAG!" << " | in position: " << position << " | Total occurrences: " << freq + 1 << endl;
        freq++;
    }
}
// TODO