//
// Created by Amr Geneidy on 4/1/20.
//

#include "DFAState.h"

DFAState::DFAState(DFAState::Type type, int n, std::map<Symbol, std::vector<State>> t) {
    this->type = type;
    this->id = n;
    this->transitions = t;
}

void DFAState::updateBy(int n, set<Symbol> alphabet) {
    //Update transition by value
    this->id += n;
    for (auto elem : alphabet) {
        if (this->transitions.find(elem) != this->transitions.end()) {
            for (int k = 0; k < this->transitions.find(elem)->second.size(); ++k) {
                this->transitions.find(elem)->second[k].id += n;
            }
        }
    }
}
