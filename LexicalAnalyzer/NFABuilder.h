//
// Created by Ahmed on 3/24/2020.
//

#ifndef CLIONPROJECTS_NFABUILDER_H
#define CLIONPROJECTS_NFABUILDER_H


#include <vector>
#include "NFA.h"

class NFABuilder {
    public:
    std::vector<NFA> basicConstruct(std::vector<char> alphabet);
    NFA concatinate(NFA n1, NFA n2, std::vector<char> alphabet);
    NFA oring(NFA n1, NFA n2, std::vector<char> alphabet);
    NFA closure(NFA n, std::vector<char> alphabet);




};


#endif //CLIONPROJECTS_NFABUILDER_H
