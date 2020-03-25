//
// Created by Ahmed on 3/24/2020.
//

#include "State.h"
State::State(State::Type type, int n, std::map<char, std::vector<State>> t) {
    this->type = type;
    this->id = n;
    this->transitions = t;
}
void State::updateBy(int n, std::vector<char> alphabet) {
    this->id += n;
    for (int i = 0; i < alphabet.size(); ++i) {
        for (int k = 0; k < this->transitions[alphabet[i]].size(); ++k) {
            this->transitions[alphabet[i]][k].id += n;
        }
    }

}
