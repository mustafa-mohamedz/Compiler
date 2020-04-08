//
// Created by Amr Geneidy on 4/1/20.
//

#ifndef COMPILER_DFASTATE_H
#define COMPILER_DFASTATE_H

#include "RegularGrammar.h"
#include "State.h"

using namespace std;

class DFAState {
public:
    bool is_accept;
    int id;
    std::vector<int> NFAStates;
    map<Symbol, std::vector<int>> transitions;
    map<Symbol, int> DFATransitions;
    Production accepted_production;
    bool operator<(const DFAState &x) const {
        return x.id > id;
    }
    bool operator == (const DFAState &x) const {
        return x.id == id;
    }

    DFAState() {is_accept = false;};
};

#endif //COMPILER_DFASTATE_H
