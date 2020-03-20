#include <iostream>
#include "LexicalAnalyzer/ProgramReader.h"

int main() {
    std::cout << "starting!!" << std::endl;
    RegularGrammar rg("");
    NFA nfa(rg);
    DFA dfa(nfa);
    ProgramReader pr("",dfa);
    return 0;
}
