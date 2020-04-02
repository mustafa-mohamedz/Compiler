//
// Created by Mustafa Mohamed on 4/1/2020.
//

#ifndef COMPILER_MINIMIZEDDFA_H
#define COMPILER_MINIMIZEDDFA_H
#include "DFA.h"
class MinimizedState {
public:
    enum Type {
        accept, internal
    } type;
    int id;
    map<Symbol, int> transitions;
    Production accepted_production;
    bool operator<(const DFAState &x) const {
        return x.id > id;
    }
};
class MinimizedDFA {

private:
    vector<set<DFAState>> getInitialPartitions(const DFA& dfa);
    map<int, int> mapStateToPartition(const vector<set<DFAState>> &vector);
    vector<set<DFAState>> divideSet(const vector<set<DFAState>>& oldPartitions,set<DFAState> workingSet,const set<Symbol> &alphabet);
    void convertPartitionsToDFA(const vector<set<DFAState>> &partitions,const DFAState& startState);
public:
    MinimizedDFA(const DFA& dfa,const set<Symbol>& alphabet);
    int startState;
    vector<MinimizedState> states;
};


#endif //COMPILER_MINIMIZEDDFA_H
