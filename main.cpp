#include <InputParser.h>
#include <DFABuilder.h>
#include "LexicalAnalyzer/ProgramReader.h"
#include <time.h>

using namespace std;

int main() {

    std::cout << "starting!!" << std::endl;
    clock_t start = clock();
    RegularGrammar rg("..//input sample 1.txt");
    clock_t rg_time = clock();
    cout << "Regular grammar execution time:" << (double)(rg_time - start) * 1000.0 / CLOCKS_PER_SEC << endl;
    set<Symbol> tempAlpha = rg.terminals;
    rg.terminals.insert(Symbol(special, "L"));
    InputParser parser(rg);
    vector<NFA> temp = parser.get_NFA();
    clock_t nfa_time = clock();
    cout << "NFA execution time:" << (double)(nfa_time - rg_time) * 1000.0 / CLOCKS_PER_SEC << endl;
    FinalNFA finalNfa(temp, rg.terminals);
    clock_t final_nfa_time = clock();
    cout << "FinalNFA execution time:" << (double)(final_nfa_time - nfa_time) * 1000.0 / CLOCKS_PER_SEC << endl;
    DFABuilder dfaBuilder;
    DFA dfa = dfaBuilder.basicConstruct(finalNfa);
    clock_t dfa_time = clock();
    cout << "DFA execution time:" << (double)(dfa_time - final_nfa_time) * 1000.0 / CLOCKS_PER_SEC << endl;
    MinimizedDFA mDFA(dfa);
    clock_t minimized_dfa_time = clock();
    cout << "DFA minimization execution time:" << (double)(minimized_dfa_time - dfa_time) * 1000.0 / CLOCKS_PER_SEC << endl;
    mDFA.printDFA(tempAlpha);
    ProgramReader pr("..//program sample 1.txt",mDFA);
    vector<string> messageList = pr.getMessages();
    cout << endl;
    for (int i = 0; i < messageList.size(); ++i) {
        cout << messageList[i] << endl;
    }
    return 0;
}

