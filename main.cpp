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
    FinalNFA finalNfa(temp, rg.terminals);
    DFABuilder dfaBuilder;
    DFA dfa = dfaBuilder.basicConstruct(finalNfa);
    MinimizedDFA mDFA(dfa, rg.terminals);
    mDFA.printDFA(tempAlpha);
    ProgramReader pr("..//program sample 1.txt",mDFA);
    vector<string> messageList = pr.getMessages();
    cout << endl;
    for (int i = 0; i < messageList.size(); ++i) {
        cout << messageList[i] << endl;
    }
    return 0;
}

