#include "NFA.h"


void NFA::printNFA(set<Symbol> alphabet) {
    for (int i = 0; i < this->states.size(); ++i) {
        State s = this->states[i];
        std::cout << "State " << s.id << std::endl;
        for (auto elem : alphabet) {
            if (s.transitions.find(elem) != s.transitions.end()){
                std::vector<State> next = s.transitions.find(elem)->second;
                for (int k = 0; k < next.size(); ++k) {
                    std::cout << "#i/p: " << elem.value << std::endl << s.id << "-->" << next[k].id << std::endl;
                }
            }
        }
    }
}

