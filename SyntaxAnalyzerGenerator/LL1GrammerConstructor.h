//
// Created by Ahmed on 4/19/2020.
//

#ifndef COMPILER_LL1GRAMMERCONSTRUCTOR_H
#define COMPILER_LL1GRAMMERCONSTRUCTOR_H


#include "ContextFreeGrammar.h"

class LL1GrammerConstructor {
private:
    ContextFreeGrammar input_grammer;
    ContextFreeGrammar LL1_grammer;
    void eliminate_immediate_left_recursion(int position);
public:
    LL1GrammerConstructor(ContextFreeGrammar input);
    ContextFreeGrammar eliminate_left_recursion();
    LL1GrammerConstructor(){};
};


#endif //COMPILER_LL1GRAMMERCONSTRUCTOR_H
