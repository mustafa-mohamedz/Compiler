//
// Created by Ahmed on 3/25/2020.
//

#include "InputParser.h"

InputParser::InputParser(RegularGrammar input) {
    this->input = input;
    builder = NFABuilder(input.terminals);
    postfix_productions = getPostfix();
}

vector<NFA> InputParser::get_NFA() {
    vector<NFA> result_nfa;
    int counter = 0;
    for(Production p : postfix_productions){
        stack <NFA> s;
        for (Symbol current : p.RHS) {
            if (current.type == terminal || (current.type == special && current.value == "L")) s.push(builder.getNFA_of(current));
            else if (current.type == special){
                if(current.value == "*" ){
                    NFA temp = s.top();
                    s.pop();
                    s.push(builder.extended_closure(temp));
                }
                else if(current.value == "+"){
                    NFA temp = s.top();
                    s.pop();
                    s.push(builder.closure(temp));
                }
                else if(current.value == "|"){
                    NFA temp1 = s.top();
                    s.pop();
                    NFA temp2 = s.top();
                    s.pop();
                    s.push(builder.oring(temp2, temp1));
                }
                else if(current.value == "."){
                    NFA temp1 = s.top();
                    s.pop();
                    NFA temp2 = s.top();
                    s.pop();
                    s.push(builder.concatinate(temp2, temp1));
                }
            }
        }
        NFA temp = s.top();
        temp.accept_state.accepted_production = input.regularExpression[counter];
        temp.states[temp.states.size() - 1].accepted_production = input.regularExpression[counter];
        result_nfa.push_back(temp);
        s.pop();
        counter++;
    }
    return result_nfa;
}

NFA InputParser::getNFA_of(Symbol c){
    return builder.getNFA_of(c);
}

int InputParser::getPrecedence(Symbol s) {
    if (s.value == "|") return 1;
    if (s.value == ".") return 2;
    if (s.value == "*") return 3;
    if (s.value == "+") return 3;
    return -1;
}

vector<Production> InputParser::getPostfix() {
    for(Production p : input.regularExpression){
        stack <Symbol> s;
        vector<Symbol> p_regex_postfix;
        vector<Symbol> original_regex = p.RHS;
        Production updated_production;
        updated_production.LHS = p.LHS;
        for(Symbol current_symbol : original_regex) {
            if (current_symbol.type == terminal || (current_symbol.type == special && current_symbol.value == "L")) p_regex_postfix.push_back(current_symbol);
            else if (current_symbol.value == "(" && current_symbol.type == special) s.push(current_symbol);
            else if (current_symbol.value == ")" && current_symbol.type == special){
                while (!s.empty() && s.top().value != "("){
                    p_regex_postfix.push_back(s.top());
                    s.pop();
                }
                if (s.top().value == "(") s.pop();
            }
            else {
                while(!s.empty() && getPrecedence(s.top()) >= getPrecedence(current_symbol)){
                    p_regex_postfix.push_back(s.top());
                    s.pop();
                }
                s.push(current_symbol);
            }
        }
        while (!s.empty()){
            p_regex_postfix.push_back(s.top());
            s.pop();
        }
        updated_production.RHS = p_regex_postfix;
        postfix_productions.push_back(updated_production);
    }
    return  postfix_productions;
}