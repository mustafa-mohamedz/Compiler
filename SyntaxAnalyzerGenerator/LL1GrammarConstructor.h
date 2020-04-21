//
// Created by Ahmed on 4/19/2020.
//

#ifndef COMPILER_LL1GRAMMARCONSTRUCTOR_H
#define COMPILER_LL1GRAMMARCONSTRUCTOR_H


#include "ContextFreeGrammar.h"

class LL1GrammarConstructor {
private:
    ContextFreeGrammar input_grammer;
    ContextFreeGrammar LL1_grammer;
    string find_longest_prefix(vector<int>);
    void eliminate_immediate_left_recursion(int position);
public:
    LL1GrammarConstructor(ContextFreeGrammar input);
    ContextFreeGrammar eliminate_left_recursion();
    ContextFreeGrammar left_factor();
    LL1GrammarConstructor(){};
};


#endif //COMPILER_LL1GRAMMARCONSTRUCTOR_H
