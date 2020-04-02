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
    enum Type {
        start, accept, internal
    } type;
    int id;
    std::vector<State> NFAStates;
    map<Symbol, std::vector<State>> transitions;
    map<Symbol, int> DFATransitions;
    Production accepted_production;
    bool operator<(const DFAState &x) const {
        return x.id > id;
    }
    bool operator == (const DFAState &x) const {
        return x.id == id;
    }
    DFAState(Type type, int n, map<Symbol, std::vector<State>> t);

    DFAState() {};
};

#endif //COMPILER_DFASTATE_H
