//
// Created by Ahmed on 3/25/2020.
//

#include "InputParser.h"

InputParser::InputParser(string input, vector<char> alphabet, vector<NFA> initial_nfa, NFABuilder builder) {
    this->input = input;
    this->alphabet = alphabet;
    this->initial_nfa = initial_nfa;
    this->builder = builder;
}

NFA InputParser::get_NFA_of() {
    RegularGrammar rg("");
    NFA result_nfa(rg);
    result_nfa = findNFA(input[0]);
    int counter = 1;
    while(counter < input.size()){
        char current_symbol = input[counter];
        switch(input[counter]){
            case '|':
                result_nfa = builder.oring(result_nfa, findNFA(input[counter + 1]), alphabet);
                counter++;
                break;
            case '*':
                result_nfa = builder.closure(result_nfa, alphabet);
                break;
            default:
                result_nfa = builder.concatinate(result_nfa, findNFA(input[counter]), alphabet);
        }
        counter++;
    }
    return result_nfa;
}

NFA InputParser::findNFA(char c){
    RegularGrammar rg("..//input sample 1.txt");
    NFA result_nfa(rg);
    for (int i = 0; i < alphabet.size(); ++i) {
        if(c == alphabet[i]){
            result_nfa = initial_nfa[i];
            break;
        }
    }
    return result_nfa;
}