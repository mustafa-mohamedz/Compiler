#ifndef COMPILER_FINALNFA_H
#define COMPILER_FINALNFA_H

#include "NFA.h"

class FinalNFA {
public:
    set<Symbol> alphabet;
    State start_state;
    std::vector<State> accept_state_list;
    std::vector<State> all_state_list;
    FinalNFA(std::vector<NFA>, set<Symbol> alphabet);
    FinalNFA(){}

};


#endif //COMPILER_FINALNFA_H
