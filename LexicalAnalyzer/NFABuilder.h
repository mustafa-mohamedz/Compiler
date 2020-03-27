//
// Created by Ahmed on 3/24/2020.
//

#ifndef CLIONPROJECTS_NFABUILDER_H
#define CLIONPROJECTS_NFABUILDER_H


#include <vector>
#include "NFA.h"

class NFABuilder {
    public:
    set<Symbol> alphabet;
    NFA basicConstruct(Symbol s);
    NFA concatinate(NFA n1, NFA n2);
    NFA oring(NFA n1, NFA n2);
    NFA extended_closure(NFA nfa);
    NFA closure(NFA nfa);
    NFABuilder(set<Symbol> alphabet);
    NFABuilder(){};




};


#endif //CLIONPROJECTS_NFABUILDER_H
