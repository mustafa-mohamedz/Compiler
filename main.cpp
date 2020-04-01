#include <iostream>
#include <NFABuilder.h>
#include <State.h>
#include <InputParser.h>
#include <FinalNFA.h>
#include <DFABuilder.h>
#include "LexicalAnalyzer/ProgramReader.h"

using namespace std;

int main() {

    std::cout << "starting!!" << std::endl;
    RegularGrammar rg("..//input sample 1.txt");
    rg.terminals.insert(Symbol(special, "L"));
    InputParser parser(rg);
    FinalNFA finalNfa(parser.get_NFA(), rg.terminals);
    DFABuilder dfaBuilder;
    dfaBuilder.basicConstruct(finalNfa);
    return 0;
}

