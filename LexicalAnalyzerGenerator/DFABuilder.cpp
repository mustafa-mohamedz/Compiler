//
// Created by Amr Geneidy on 3/25/20.
//

#include "DFABuilder.h"

using namespace std;
FinalNFA global_nfa;

DFA DFABuilder::basicConstruct(FinalNFA nonDeterministicAutomata) {
    global_nfa = nonDeterministicAutomata;
    DFA dfa;
    State s0 = nonDeterministicAutomata.start_state;
    set<DFAState> set;
    queue<DFAState> queue;
    DFAState closure = build_DFA_state(LClosure(s0.id));
    dfa.start_state_id = closure.id;
    set.insert(closure);
    queue.push(closure);
    while (!queue.empty()) {
        DFAState t = queue.front();
        queue.pop();
        auto it = t.transitions.begin();
        while (it != t.transitions.end()) {
            std::vector<int> l_closure_vec = LClosureVec((it->second));
            DFAState u = build_DFA_state(l_closure_vec);
            if (set.find(u) == set.end()) {
                set.insert(u);
                queue.push(u);
            }
            if (u.NFAStates.size() != 0) t.DFATransitions.insert(pair<Symbol, int>(it->first, u.id));
            it++;
        }
        dfa.states.push_back(t);
    }
    for (int i = 0; i < dfa.states.size(); i++) {
        if (dfa.states[i].is_accept) {
            int min = INT_MAX;
            Production min_production;
            for (int j = 0; j < dfa.states[i].NFAStates.size(); j++) {
                if (global_nfa.all_state_list[dfa.states[i].NFAStates[j]].type == State::accept &&
                        global_nfa.all_state_list[dfa.states[i].NFAStates[j]].accepted_production.priority < min) {
                    min_production = global_nfa.all_state_list[dfa.states[i].NFAStates[j]].accepted_production;
                    min = global_nfa.all_state_list[dfa.states[i].NFAStates[j]].accepted_production.priority;
                }
            }
            dfa.states[i].accepted_production = min_production;
        }
    }
    for (int i = 0; i < dfa.states.size(); i++) {
        dfa.states[i].transitions.clear();
        dfa.states[i].NFAStates.clear();
    }
    return dfa;
}

vector<int> DFABuilder::LClosure(int state) {
    vector<int> l_closure;
    set<int> set;
    stack<int> stack;
    stack.push(state);
    set.insert(state);
    while (!stack.empty()) {
        int t = stack.top();
        stack.pop();
        l_closure.push_back(t);
        auto tmp = global_nfa.all_state_list[t].transitions.find(Symbol(special, "L"));
        if (tmp == global_nfa.all_state_list[t].transitions.end()) continue;
        vector<State> vec = tmp->second;
        for (int j = 0; j < vec.size(); j++) {
            if (set.find(vec[j].id) == set.end()) {
                stack.push(vec[j].id);
                set.insert(vec[j].id);
            }
        }
    }
    return l_closure;
}

vector<int> DFABuilder::LClosureVec(vector<int> state_vec) {
    vector<int> l_closure;
    for (int i = 0; i < state_vec.size(); i++) {
        vector<int> single_closure = LClosure(state_vec[i]);
        l_closure.insert(l_closure.end(), single_closure.begin(), single_closure.end());
    }
    return l_closure;
}

int id = 0;
map<vector<int>, int> found_before;

DFAState DFABuilder::build_DFA_state(vector<int> vector) {
    DFAState res;
    std::set<int> ids;
    std::set<Symbol> self_loop_symbols;
    for (int i = 0; i < vector.size(); i++) {
        ids.insert(vector[i]);
    }
    for (int i = 0; i < vector.size(); i++) {
        auto it = global_nfa.all_state_list[vector[i]].transitions.begin();
        while (it != global_nfa.all_state_list[vector[i]].transitions.end()) {
            std::vector<int> next_transition;
            for (int j = 0; j < it->second.size(); j++) {
                if (ids.find(it->second[j].id) == ids.end()) {
                    next_transition.push_back(it->second[j].id);
                } else {
                    self_loop_symbols.insert(it->first);
                }
            }
            if (next_transition.size() != 0) {
                if (res.transitions.find(it->first) == res.transitions.end()) {
                    res.transitions.insert(pair<Symbol, std::vector<int>>(it->first, next_transition));
                } else {
                    std::vector<int> updated_transitions = res.transitions.find(it->first)->second;
                    updated_transitions.insert(updated_transitions.end(), next_transition.begin(),
                                               next_transition.end());
                    res.transitions.erase(it->first);
                    res.transitions.insert(pair<Symbol, std::vector<int>>(it->first, updated_transitions));
                }
            }
            it++;
        }
        res.NFAStates.insert(res.NFAStates.begin(), vector[i]);
        if (global_nfa.all_state_list[vector[i]].type == State::accept) res.is_accept = true;
    }
    if (found_before.find(res.NFAStates) == found_before.end()) {
        res.id = id++;
        found_before.insert({res.NFAStates, res.id});;
    } else {
        res.id = found_before.find(res.NFAStates)->second;
    }
    auto it = self_loop_symbols.begin();
    while (it != self_loop_symbols.end()) {
        if (it->type != special || it->value != "L") res.DFATransitions.insert({*it, res.id});
        it++;
    }
    return res;
}
