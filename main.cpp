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
    set<Symbol> tempAlpha = rg.terminals;
    rg.terminals.insert(Symbol(special, "L"));
    InputParser parser(rg);
    vector<NFA> temp = parser.get_NFA();
    cout << temp.size() << endl;
    temp[0].printNFA(rg.terminals);
    FinalNFA finalNfa(temp, rg.terminals);
    //finalNfa.print(rg.terminals);
    cout << "NFA is done" << endl;
    DFABuilder dfaBuilder;
    DFA dfa = dfaBuilder.basicConstruct(finalNfa);
    cout << "DFA is done" << endl;
    MinimizedDFA mDFA(dfa, rg.terminals);
    mDFA.printDFA(tempAlpha);
    cout << "MDFA is done" << endl;
    ProgramReader pr("..//program sample 1.txt",mDFA);
    vector<Token> tokens = pr.getTokens();
    cout << endl;
    for (int i = 0; i < tokens.size(); ++i) {
        cout << tokens[i].type << " : " <<tokens[i].value << endl;
    }
    return 0;
}

