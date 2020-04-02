//
// Created by Mustafa Mohamed on 4/1/2020.
//

#include "MinimizedDFA.h"

MinimizedDFA::MinimizedDFA(const DFA &dfa,const set<Symbol> &alphabet) {
    vector<set<DFAState>> oldPartitions;
    vector<set<DFAState>> newPartitions = getInitialPartitions(dfa);
    while(!(newPartitions == oldPartitions)){
        oldPartitions = newPartitions;
        newPartitions.clear();
        for (int i = 0; i < oldPartitions.size(); ++i) {
            vector<set<DFAState>> dividedSet = divideSet(oldPartitions,oldPartitions[i],alphabet);
            copy(dividedSet.begin(), dividedSet.end(), back_inserter(newPartitions));
        }
    }
    convertPartitionsToDFA(newPartitions,dfa.start_state);
}

vector<set<DFAState>> MinimizedDFA::getInitialPartitions(const DFA &dfa) {
    vector<set<DFAState>> result;
    set<DFAState> internalStates;
    for (int i = 0; i < dfa.states.size(); ++i) {
        if(dfa.states[i].type != DFAState::accept){
            internalStates.insert(dfa.states[i]);
        }
    }
    result.push_back(internalStates);

    map<string,set<DFAState>> productionToStatesMap;
    for (int j = 0; j < dfa.accept_states.size() ; ++j) {
        string acceptedToken = dfa.accept_states[j].accepted_production.LHS.value;
        set<DFAState> tempSet;
        if(productionToStatesMap.find(acceptedToken) != productionToStatesMap.end()){
            tempSet = productionToStatesMap.find(acceptedToken)->second;
            productionToStatesMap.erase(acceptedToken);
        }
        tempSet.insert(dfa.accept_states[j]);
        productionToStatesMap.insert({acceptedToken,tempSet});
    }
    for (auto const x : productionToStatesMap){
        result.push_back(x.second);
    }

    return result;
}

vector<set<DFAState>> MinimizedDFA::divideSet(const vector<set<DFAState>>& oldPartitions,set<DFAState> workingSet,const set<Symbol> &alphabet) {
    vector<set<DFAState>> dividedSet;
    map<int,int> stateToPartitionMap = mapStateToPartition(oldPartitions);
    map<vector<int>,set<DFAState>> rowToNewPartitionMap;
    for (auto const state : workingSet){
        vector<int> row;
        for (const auto s : alphabet) {
            auto nextState = state.DFATransitions.find(s);
            if(nextState == state.DFATransitions.end()){
                row.push_back(-1);
            }else{
                row.push_back(stateToPartitionMap.find(nextState->second)->second);
            }
        }
        set<DFAState> tempSet;
        if(rowToNewPartitionMap.find(row) != rowToNewPartitionMap.end()){
            tempSet = rowToNewPartitionMap.find(row)->second;
            rowToNewPartitionMap.erase(row);
        }
        tempSet.insert(state);
        rowToNewPartitionMap.insert({row,tempSet});
    }
    for (auto const x : rowToNewPartitionMap){
        dividedSet.push_back(x.second);
    }

    return dividedSet;
}
map<int, int> MinimizedDFA::mapStateToPartition(const vector<set<DFAState>> &partitions) {
    map<int,int>result;
    for (int i = 0; i < partitions.size(); ++i) {
        for (const auto state : partitions[i]) {
            result.insert({state.id,i});
        }
    }
    return result;
}

void MinimizedDFA::convertPartitionsToDFA(const vector<set<DFAState>> &partitions,const DFAState& startState) {

    vector<MinimizedState> states;
    map<int,int> stateToPartitionMap = mapStateToPartition(partitions);
    for (int i = 0; i < partitions.size(); ++i) {
        MinimizedState ithState;
        ithState.id = i;
        DFAState sampleState = *partitions[i].begin();
        if(sampleState.type == DFAState::accept){
            ithState.type = MinimizedState::accept;
            ithState.accepted_production = sampleState.accepted_production;
        }else{
            ithState.type = MinimizedState::internal;
        }
        map<Symbol,int> ithStateTransitions;
        for (auto transition : sampleState.DFATransitions) {
            ithStateTransitions.insert({transition.first,stateToPartitionMap.find(transition.second)->second});
        }
        ithState.transitions = ithStateTransitions;

        states.push_back(ithState);
    }
    this->states = states;

    for (int i = 0; i < partitions.size(); ++i) {
        for (const auto state : partitions[i]) {
            if(state.id == startState.id){
                this->startState = stateToPartitionMap.find(state.id)->second;
            }
        }
    }
}


