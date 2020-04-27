//
// Created by OWNER on 4/13/2020.
//

#include "ContextFreeGrammar.h"
#include <iostream>


ContextFreeGrammar::ContextFreeGrammar(const string &CFG_path) {

}

void ContextFreeGrammar::print() {
    for (int i = 0; i < productions.size(); ++i) {
        cout << productions[i].LHS.value << " --> ";
        for (int j = 0; j < productions[i].RHS.size(); ++j) {
            for (int k = 0; k < productions[i].RHS[j].size(); ++k) {
                cout << productions[i].RHS[j][k].value << " ";
            }
            cout << " | ";
        }
        cout << endl;
    }
}
