#include <iostream>
#include <NFABuilder.h>
#include <winsock.h>
#include <State.h>
#include "LexicalAnalyzer/ProgramReader.h"

int main() {
    std::cout << "starting!!" << std::endl;
    RegularGrammar rg("..//input sample 1.txt");
    NFA nfa(rg);
    DFA dfa(nfa);
    ProgramReader pr("",dfa);

    std::vector<char> alphabet = {'a', 'b', 'c', 'd', 'L'};
    NFABuilder builder;
    std::vector<NFA> initial_nfa = builder.basicConstruct(alphabet);


    NFA n3 = builder.oring(initial_nfa[0], initial_nfa[1], alphabet);

    std::cout << "Result of a or b" << std::endl;
    for (int i = 0; i < n3.states.size(); ++i) {
        State s = n3.states[i];
        std::cout << "State " << s.num << std::endl;
        for (int j = 0; j < alphabet.size(); ++j) {
            std::vector<State> next = s.transitions[alphabet[j]];
            for (int k = 0; k < next.size(); ++k) {
                std::cout << "#i/p: " << alphabet[j] << std::endl << s.num << "-->" << next[k].num << std::endl;
            }
        }

    }







    for (int j = 0; j < initial_nfa.size(); ++j) {
        nfa = initial_nfa[j];
        std::cout << "NFA for Symbol " << alphabet[j] << std::endl;
        State start_state = nfa.start_state;
        State accept_state = nfa.accept_state;

        for (int i = 0; i < nfa.states.size(); ++i) {
            State s = nfa.states[i];
            std::vector<State> next = s.transitions[alphabet[j]];
            for (int k = 0; k < next.size(); ++k) {
                std::cout << "#i/p: " << alphabet[j] << std::endl << s.num << "-->" << next[k].num << std::endl;

            }
        }
    }

    NFA n = builder.concatinate(initial_nfa[0], initial_nfa[1], alphabet);

    std::cout << "Result of ab" << std::endl;
    for (int i = 0; i < n.states.size(); ++i) {
        State s = n.states[i];
        std::cout << "State " << s.num << std::endl;
        for (int j = 0; j < alphabet.size(); ++j) {
            std::vector<State> next = s.transitions[alphabet[j]];
            for (int k = 0; k < next.size(); ++k) {
                std::cout << "#i/p: " << alphabet[j] << std::endl << s.num << "-->" << next[k].num << std::endl;
            }
        }
    }

 /*   NFA n2 = builder.concatinate(n, initial_nfa[2], alphabet);

    std::cout << "Result of abc" << std::endl;
    for (int i = 0; i < n2.states.size(); ++i) {
        State s = n2.states[i];
        std::cout << "State " << s.num << std::endl;
        for (int j = 0; j < alphabet.size(); ++j) {
            std::vector<State> next = s.transitions[alphabet[j]];
            for (int k = 0; k < next.size(); ++k) {
                std::cout << "#i/p: " << alphabet[j] << std::endl << s.num << "-->" << next[k].num << std::endl;
            }
        }

    }
*/




    return 0;
}
