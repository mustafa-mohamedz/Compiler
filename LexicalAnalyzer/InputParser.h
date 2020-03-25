//
// Created by Ahmed on 3/25/2020.
//

#ifndef CLIONPROJECTS_INPUTPARSER_H
#define CLIONPROJECTS_INPUTPARSER_H


#include "NFA.h"
#include "NFABuilder.h"

class InputParser {
    private:
    string input;
    vector<char> alphabet;
    vector<NFA> initial_nfa;
    NFABuilder builder;
    public:
    InputParser(string input, vector<char> alphabet, vector<NFA> initial_nfa, NFABuilder builder);
    NFA findNFA(char c);
    NFA get_NFA_of();

};


#endif //CLIONPROJECTS_INPUTPARSER_H
