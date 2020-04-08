//
// Created by Mustafa Mohamed on 4/1/2020.
//

#ifndef COMPILER_MINIMIZEDDFA_H
#define COMPILER_MINIMIZEDDFA_H

#include "DFA.h"
#include <unordered_map>


class MinimizedState {
public:
    bool is_accept;
    int id;
    unordered_map<Symbol, int, SymbolHashFunction> transitions;
    Production accepted_production;

    bool operator<(const DFAState &x) const {
        return x.id > id;
    }
};

class MinimizedDFA {

private:
    vector<set<DFAState>> getInitialPartitions(const DFA &dfa);

    unordered_map<int, int> mapStateToPartition(const vector<set<DFAState>> &vector);

    vector<set<DFAState>>
    divideSet(const vector<set<DFAState>> &oldPartitions, set<DFAState> workingSet);

    void convertPartitionsToDFA(const vector<set<DFAState>> &partitions, const int start_state_id);

    void printBeforeSpaces(int l);

    void printAfterSpaces(int l);

    void printHLine(int l);

public:
    MinimizedDFA(const DFA &dfa);

    void printDFA(const set<Symbol> &alphabet);

    int startState;
    vector<MinimizedState> states;
};


#endif //COMPILER_MINIMIZEDDFA_H
