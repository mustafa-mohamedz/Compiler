//
// Created by Ahmed on 3/24/2020.
//

#ifndef CLIONPROJECTS_STATE_H
#define CLIONPROJECTS_STATE_H


#include <map>
#include <vector>
#include <string>
#include "RegularGrammar.h"

using namespace std;
class State {
    public:
    enum Type {
        start, accept, internal
    }type;
    int id;
    Production accepted_production;
    map<Symbol, std::vector<State>> transitions;
    void updateBy(int n, set<Symbol> alphabet);
    State(Type type, int n, map<Symbol, std::vector<State>> t);
    State(){};
};


#endif //CLIONPROJECTS_STATE_H
