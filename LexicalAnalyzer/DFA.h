#ifndef COMPILER_DFA_H
#define COMPILER_DFA_H

#include "NFA.h"

class DFA {
public:
    DFA();

    State start_state;
    std::vector<State> accept_states;
    std::vector<State> states;
    //constructor
    DFA(NFA nonDeterministicAutomata);
};


#endif //COMPILER_DFA_H
