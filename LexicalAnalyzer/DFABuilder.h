//
// Created by Amr Geneidy on 3/25/20.
//

#ifndef COMPILER_DFABUILDER_H
#define COMPILER_DFABUILDER_H

#include <vector>
#include "DFA.h"

class DFABuilder {
public:
    DFA basicConstruct(NFA nonDeterministicAutomata);

    vector<State> LClosure(State state);

    State merge_states(vector<State> vector);

    vector<State> LClosureVec(vector<State> vector);
};
#endif //COMPILER_DFABUILDER_H
