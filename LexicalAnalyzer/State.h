//
// Created by Ahmed on 3/24/2020.
//

#ifndef CLIONPROJECTS_STATE_H
#define CLIONPROJECTS_STATE_H


#include <map>
#include <vector>

class State {
    public:
    enum Type {
        start, accept, internal
    }type;
    int num;
    std::map<char, std::vector<State>> transitions;
    void updateBy(int n, std::vector<char> alphabet);
    State(Type type, int n, std::map<char, std::vector<State>> t);
    State(){};
};


#endif //CLIONPROJECTS_STATE_H
