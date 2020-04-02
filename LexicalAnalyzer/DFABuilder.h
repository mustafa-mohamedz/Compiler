//
// Created by Amr Geneidy on 3/25/20.
//

#ifndef COMPILER_DFABUILDER_H
#define COMPILER_DFABUILDER_H

#include "DFA.h"
#include <queue>
#include "State.h"
#include "DFAState.h"

class DFABuilder {
public:
    DFA basicConstruct(FinalNFA nonDeterministicAutomata);

    vector<State> LClosure(State state);

    DFAState build_DFA_state(vector<State> vector);

    vector<State> LClosureVec(vector<State> vector);
};

#endif //COMPILER_DFABUILDER_H
