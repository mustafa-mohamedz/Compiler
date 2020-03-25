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
    n3.printNFA(alphabet);

    NFA n4 = builder.concatinate(n3, initial_nfa[1], alphabet);
    n4.printNFA(alphabet);





    NFA n = builder.concatinate(initial_nfa[0], initial_nfa[1], alphabet);
    n.printNFA(alphabet);

    NFA n2 = builder.concatinate(n, initial_nfa[2], alphabet);
    n2.printNFA(alphabet);

    NFA n5 = builder.closure(n3, alphabet);
    std::cout << "Result of (a|b)*" << std::endl;
    n5.printNFA(alphabet);


    return 0;
}
