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
    vector<NFA> temp = parser.get_NFA();
    FinalNFA finalNfa(temp, rg.terminals);
    //finalNfa.print(rg.terminals);
    DFABuilder dfaBuilder;
    DFA dfa = dfaBuilder.basicConstruct(finalNfa);
    MinimizedDFA mDFA(dfa, rg.terminals);
    ProgramReader pr("..//program sample 1.txt",mDFA);
    vector<Token> tokens = pr.getTokens();
    for (int i = 0; i < tokens.size(); ++i) {
        cout << tokens[i].type << " : " << tokens[i].value << endl;
    }
    return 0;
}

