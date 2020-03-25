#include "NFA.h"

NFA::NFA(RegularGrammar regularGrammar) {

}

void NFA::printNFA(std::vector<char> alphabet) {
    for (int i = 0; i < this->states.size(); ++i) {
        State s = this->states[i];
        std::cout << "State " << s.id << std::endl;
        for (int j = 0; j < alphabet.size(); ++j) {
            std::vector<State> next = s.transitions[alphabet[j]];
            for (int k = 0; k < next.size(); ++k) {
                std::cout << "#i/p: " << alphabet[j] << std::endl << s.id << "-->" << next[k].id << std::endl;
            }
        }

    }
}

