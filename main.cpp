#include <iostream>
#include <NFABuilder.h>
#include <winsock.h>
#include <State.h>
#include <InputParser.h>
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

    string input = "a|b";

    InputParser parser(input, alphabet, initial_nfa, builder);

    NFA result = parser.get_NFA_of();

    result.printNFA(alphabet);






    return 0;
}

