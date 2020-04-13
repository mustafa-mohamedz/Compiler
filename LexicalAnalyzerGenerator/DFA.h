#ifndef COMPILER_DFA_H
#define COMPILER_DFA_H

#include "FinalNFA.h"
#include "DFAState.h"

class DFA {
public:
    DFA();

    int start_state_id;
    std::vector<DFAState> states;
    //constructor
    DFA(FinalNFA nonDeterministicAutomata);
};


#endif //COMPILER_DFA_H
