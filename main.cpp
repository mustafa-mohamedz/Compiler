#include <iostream>
#include "LexicalAnalyzer/ProgramReader.h"

int main() {
    std::cout << "starting!!" << std::endl;
    RegularGrammar rg("..//input sample 1.txt");
    NFA nfa(rg);
    DFA dfa(nfa);
    ProgramReader pr("",dfa);
    return 0;
}
