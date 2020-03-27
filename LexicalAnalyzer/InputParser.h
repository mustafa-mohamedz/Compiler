//
// Created by Ahmed on 3/25/2020.
//

#ifndef CLIONPROJECTS_INPUTPARSER_H
#define CLIONPROJECTS_INPUTPARSER_H


#include "NFA.h"
#include "NFABuilder.h"

class InputParser {
    private:
    RegularGrammar input;
    vector<NFA> initial_nfa;
    NFABuilder builder;
    public:
    InputParser(RegularGrammar input);
    InputParser(){};
    NFA getNFA_of(Symbol c);
    NFA get_NFA();


};


#endif //CLIONPROJECTS_INPUTPARSER_H
