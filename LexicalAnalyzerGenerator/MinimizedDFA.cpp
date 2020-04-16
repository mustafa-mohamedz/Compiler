//
// Created by Mustafa Mohamed on 4/1/2020.
//

#include "MinimizedDFA.h"
#include <fstream>
#include <iostream>

ofstream MyFile("..//DFA.txt");

MinimizedDFA::MinimizedDFA(const DFA &dfa) {
    vector<set<DFAState>> oldPartitions;
    vector<set<DFAState>> newPartitions = getInitialPartitions(dfa);
    while (!(newPartitions == oldPartitions)) {
        oldPartitions = newPartitions;
        newPartitions.clear();
        for (int i = 0; i < oldPartitions.size(); ++i) {
            vector<set<DFAState>> dividedSet = divideSet(oldPartitions, oldPartitions[i]);
            copy(dividedSet.begin(), dividedSet.end(), back_inserter(newPartitions));
        }
    }
    convertPartitionsToDFA(newPartitions, dfa.start_state_id);
}

vector<set<DFAState>> MinimizedDFA::getInitialPartitions(const DFA &dfa) {
    vector<set<DFAState>> result;
    set<DFAState> internalStates;
    for (int i = 0; i < dfa.states.size(); ++i) {
        if (!dfa.states[i].is_accept) {
            internalStates.insert(dfa.states[i]);
        }
    }
    result.push_back(internalStates);

    unordered_map<string, set<DFAState>> productionToStatesMap;
    for (int j = 0; j < dfa.states.size(); ++j) {
        if (dfa.states[j].is_accept) {
            string acceptedToken = dfa.states[j].accepted_production.LHS.value;
            set<DFAState> tempSet;
            if (productionToStatesMap.find(acceptedToken) != productionToStatesMap.end()) {
                tempSet = productionToStatesMap.find(acceptedToken)->second;
                productionToStatesMap.erase(acceptedToken);
            }
            tempSet.insert(dfa.states[j]);
            productionToStatesMap.insert({acceptedToken, tempSet});
        }
    }
    for (auto const x : productionToStatesMap) {
        result.push_back(x.second);
    }

    return result;
}

vector<set<DFAState>> MinimizedDFA::divideSet(const vector<set<DFAState>> &oldPartitions, set<DFAState> workingSet) {
    vector<set<DFAState>> dividedSet;
    unordered_map<int, int> stateToPartitionMap = mapStateToPartition(oldPartitions);
    unordered_map<string, set<DFAState>> rowToNewPartitionMap;
    for (auto const state : workingSet) {
        string row;
        for (const auto s : state.DFATransitions) {
            row += s.first.value;
            row += to_string(stateToPartitionMap.find(s.second)->second);
            row.push_back(' ');
        }
        set<DFAState> tempSet;
        if (rowToNewPartitionMap.find(row) != rowToNewPartitionMap.end()) {
            tempSet = rowToNewPartitionMap.find(row)->second;
            rowToNewPartitionMap.erase(row);
        }
        tempSet.insert(state);
        rowToNewPartitionMap.insert({row, tempSet});
    }
    for (auto const x : rowToNewPartitionMap) {
        dividedSet.push_back(x.second);
    }

    return dividedSet;
}

unordered_map<int, int> MinimizedDFA::mapStateToPartition(const vector<set<DFAState>> &partitions) {
    unordered_map<int, int> result;
    for (int i = 0; i < partitions.size(); ++i) {
        for (const auto state : partitions[i]) {
            result.insert({state.id, i});
        }
    }
    return result;
}

void MinimizedDFA::convertPartitionsToDFA(const vector<set<DFAState>> &partitions, const int start_state_id) {

    vector<MinimizedState> states;
    unordered_map<int, int> stateToPartitionMap = mapStateToPartition(partitions);
    for (int i = 0; i < partitions.size(); ++i) {
        MinimizedState ithState;
        ithState.id = i;
        DFAState sampleState = *partitions[i].begin();
        if (sampleState.is_accept) {
            ithState.is_accept = true;
            ithState.accepted_production = sampleState.accepted_production;
        } else {
            ithState.is_accept = false;
        }
        unordered_map<Symbol, int, SymbolHF> ithStateTransitions;
        for (auto transition : sampleState.DFATransitions) {
            ithStateTransitions.insert({transition.first, stateToPartitionMap.find(transition.second)->second});
        }
        ithState.transitions = ithStateTransitions;

        states.push_back(ithState);
    }
    this->states = states;
    bool startStateFound = false;
    for (int i = 0; i < partitions.size(); ++i) {
        for (const auto state : partitions[i]) {
            if (state.id == start_state_id) {
                this->startState = stateToPartitionMap.find(state.id)->second;
                startStateFound = true;
                break;
            }
        }
        if (startStateFound) break;
    }
}

void MinimizedDFA::printDFA(const set<Symbol> &alphabet) {
    vector<MinimizedState> accept_states;
    cout << "Start State: " << this->startState << endl;
    MyFile << "Start State: " << this->startState << endl;
    cout << "  State  |";
    MyFile << "  State  |";
    for (const auto s : alphabet) {
        int l = s.value.length();
        printBeforeSpaces(l);
        cout << s.value;
        MyFile << s.value;
        printAfterSpaces(l);
    }
    printHLine(alphabet.size() * 4);

    for (int i = 0; i < this->states.size(); ++i) {
        int n = states[i].id;
        int number_of_digits = 0;
        do {
            ++number_of_digits;
            n /= 10;
        } while (n);
        if (states[i].is_accept) {
            accept_states.push_back(states[i]);
            printBeforeSpaces(number_of_digits + 2);
            cout << "(" << states[i].id << ")";
            MyFile << "(" << states[i].id << ")";
            printAfterSpaces(number_of_digits + 2);
        } else {
            printBeforeSpaces(number_of_digits);
            cout << states[i].id;
            MyFile << states[i].id;
            printAfterSpaces(number_of_digits);
        }
        for (const auto s : alphabet) {
            auto itr = states[i].transitions.find(s);
            if (itr != states[i].transitions.end()) {
                n = itr->second;
                number_of_digits = 0;
                do {
                    ++number_of_digits;
                    n /= 10;
                } while (n);
                if (states[itr->second].is_accept) {
                    printBeforeSpaces(number_of_digits + 2);
                    cout << "(" << itr->second << ")";
                    MyFile << "(" << itr->second << ")";
                    printAfterSpaces(number_of_digits + 2);
                } else {
                    printBeforeSpaces(number_of_digits);
                    cout << itr->second;
                    MyFile << itr->second;
                    printAfterSpaces(number_of_digits);
                }
            } else {
                cout << "  e   |";
                MyFile << "  e   |";
            }
        }
        printHLine(alphabet.size() * 4);
    }
    MyFile << "Accepted Productions:" << endl;
    for (MinimizedState s : accept_states) {
        cout << "   State " << s.id << " accepts the production: " << s.accepted_production.LHS.value << endl;
        MyFile << "   State " << s.id << " accepts the production: " << s.accepted_production.LHS.value << endl;
    }
    MyFile.close();
}

void MinimizedDFA::printBeforeSpaces(int l) {
    int num_of_spaces = (6 - l) / 2;
    for (int i = 0; i < num_of_spaces; ++i) {
        cout << " ";
        MyFile << " ";
    }
}

void MinimizedDFA::printAfterSpaces(int l) {
    int num_of_spaces = (6 - l) / 2;
    if (l % 2 == 1) num_of_spaces++;
    for (int i = 0; i < num_of_spaces; ++i) {
        cout << " ";
        MyFile << " ";
    }
    cout << "|";
    MyFile << "|";
}

void MinimizedDFA::printHLine(int l) {
    cout << endl;
    MyFile << endl;
    for (int i = 0; i < l; ++i) {
        cout << "--";
        MyFile << "--";
    }
    cout << endl << "   ";
    MyFile << endl << "   ";
}