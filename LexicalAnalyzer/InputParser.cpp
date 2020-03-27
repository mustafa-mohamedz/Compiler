//
// Created by Ahmed on 3/25/2020.
//

#include "InputParser.h"

InputParser::InputParser(RegularGrammar input) {
    this->input = input;
    builder = NFABuilder(input.terminals);
    initial_nfa = builder.basicConstruct();


}

NFA InputParser::get_NFA() {

    NFA result_nfa;
    Symbol s();
    int counter = 1;

    return result_nfa;
}

NFA InputParser::getNFA_of(Symbol c){
    //TODO
    NFA result_nfa;
    /*int i = 0;
    for (auto elem : alphabet) {
        if(c.value == elem.value && c.type == elem.type){
            result_nfa = initial_nfa[i];
            break;
        }
        i++;
    }
     */
    return result_nfa;
}