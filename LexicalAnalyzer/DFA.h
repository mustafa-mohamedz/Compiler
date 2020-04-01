#ifndef COMPILER_DFA_H
#define COMPILER_DFA_H

#include "FinalNFA.h"
#include "DFAState.h"

class DFA {
public:
    DFA();

    DFAState start_state;
    std::vector<DFAState> accept_states;
    std::vector<DFAState> states;
    //constructor
    DFA(FinalNFA nonDeterministicAutomata);
};


#endif //COMPILER_DFA_H
