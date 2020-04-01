//
// Created by Amr Geneidy on 4/1/20.
//

#include "DFAState.h"

DFAState::DFAState(DFAState::Type type, int n, std::map<Symbol, std::vector<State>> t) {
    this->type = type;
    this->id = n;
    this->transitions = t;
}
