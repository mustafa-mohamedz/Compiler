#ifndef COMPILER_NFA_H
#define COMPILER_NFA_H
#include <iostream>
#include <map>
#include "RegularGrammar.h"
#include "State.h"


class NFA {
public:
    State start_state;
    State accept_state;
    std::vector<State> states;
    void printNFA(set<Symbol> alphabet);
    NFA(){};
// Driver code

};


#endif //COMPILER_NFA_H
