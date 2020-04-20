
#include <time.h>
#include "LexicalAnalyzer.h"
#include "SyntaxParser.h"
#include "SyntaxAnalyzerGenerator/LL1GrammerConstructor.h"

using namespace std;

int main() {
   // LexicalAnalyzer lexicalAnalyzer("..//input sample 1.txt" , "..//program sample 1.txt");
   // SyntaxParser syntax_parser(lexicalAnalyzer," ");

    ContextFreeGrammar x;

    CFProduction first;
    first.LHS = Symbol(nonTerminal,"S");
    first.RHS = {{Symbol(nonTerminal,"A"),Symbol(terminal,"a")},{Symbol(terminal,"b")}};
    CFProduction second;
    second.LHS = Symbol(nonTerminal,"A");
    second.RHS = {{Symbol(nonTerminal,"A"),Symbol(terminal,"c")},{Symbol(nonTerminal,"S"), Symbol(terminal,"d")},
                  {Symbol(terminal,"f")}};
    x.productions = {first, second};

    LL1GrammerConstructor l(x);

    ContextFreeGrammar grammar = l.eliminate_left_recursion();
    cout << "";

/*
 * code to test syntaxAnalyzerUtilities
 */
//    ContextFreeGrammar x;
//    CFProduction first;
//    first.LHS = Symbol(nonTerminal,"E");
//    first.RHS = {{Symbol(nonTerminal,"T"),Symbol(nonTerminal,"E'")}};
//    CFProduction second;
//    second.LHS = Symbol(nonTerminal,"E'");
//    second.RHS = {{Symbol(terminal,"+"),Symbol(nonTerminal,"T"),Symbol(nonTerminal,"E'")},{Symbol(special,"L")}};
//    CFProduction third;
//    third.LHS = Symbol(nonTerminal,"T");
//    third.RHS = {{Symbol(nonTerminal,"F"),Symbol(nonTerminal,"T'")}};
//    CFProduction fourth;
//    fourth.LHS = Symbol(nonTerminal,"T'");
//    fourth.RHS = {{Symbol(terminal,"*"),Symbol(nonTerminal,"F"),Symbol(nonTerminal,"T'")},{Symbol(special,"L")}};
//    CFProduction fifth;
//    fifth.LHS = Symbol(nonTerminal,"F");
//    fifth.RHS = {{Symbol(terminal,"("),Symbol(nonTerminal,"E"),Symbol(terminal,")")},{Symbol(terminal,"id")}};
//    x.productions = {first,second,third,fourth,fifth};
//    SyntaxAnalyzerUtilities s(x);


// phase1 main
//    std::cout << "starting!!" << std::endl;
//    clock_t start = clock();
//    RegularGrammar rg("..//input sample 1.txt");
//    clock_t rg_time = clock();
//    cout << "Regular grammar execution time:" << (double)(rg_time - start) * 1000.0 / CLOCKS_PER_SEC << endl;
//    set<Symbol> tempAlpha = rg.terminals;
//    rg.terminals.insert(Symbol(special, "L"));
//    InputParser parser(rg);
//    vector<NFA> temp = parser.get_NFA();
//    clock_t nfa_time = clock();
//    cout << "NFA execution time:" << (double)(nfa_time - rg_time) * 1000.0 / CLOCKS_PER_SEC << endl;
//    FinalNFA finalNfa(temp, rg.terminals);
//    clock_t final_nfa_time = clock();
//    cout << "FinalNFA execution time:" << (double)(final_nfa_time - nfa_time) * 1000.0 / CLOCKS_PER_SEC << endl;
//    DFABuilder dfaBuilder;
//    DFA dfa = dfaBuilder.basicConstruct(finalNfa);
//    clock_t dfa_time = clock();
//    cout << "DFA execution time:" << (double)(dfa_time - final_nfa_time) * 1000.0 / CLOCKS_PER_SEC << endl;
//    MinimizedDFA mDFA(dfa);
//    clock_t minimized_dfa_time = clock();
//    cout << "DFA minimization execution time:" << (double)(minimized_dfa_time - dfa_time) * 1000.0 / CLOCKS_PER_SEC << endl;
//    mDFA.printDFA(tempAlpha);
//    ProgramReader pr("..//program sample 1.txt",mDFA);
//    vector<string> messageList = pr.getLogMessages();
//    cout << endl;
//    for (int i = 0; i < messageList.size(); ++i) {
//        cout << messageList[i] << endl;
//    }

    return 0;
}

