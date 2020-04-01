//
// Created by Amr Geneidy on 3/25/20.
//

#include "DFABuilder.h"

using namespace std;

DFA DFABuilder::basicConstruct(FinalNFA nonDeterministicAutomata) {
    DFA dfa;
    State s0 = nonDeterministicAutomata.start_state;
    set<DFAState> set;
    queue<DFAState> queue;
    DFAState closure = merge_states(LClosure(s0));
    dfa.start_state = closure;
    dfa.states.push_back(closure);
    set.insert(closure);
    queue.push(closure);
    while (!queue.empty()) {
        DFAState t = queue.front();
        queue.pop();
        auto it = t.transitions.begin();
        while (it != t.transitions.end()) {
            DFAState u = merge_states(LClosureVec((it->second)));
            if (set.find(u) == set.end()) {
                set.insert(u);
                queue.push(u);
                dfa.states.push_back(u);
            }
            t.DFATransitions.insert(pair<Symbol, DFAState>(it->first, u));
            it++;
        }
    }
    return dfa;
}

vector<State> DFABuilder::LClosure(State state) {
    vector<State> l_closure;
    set<State> set;
    stack<State> stack;
    stack.push(state);
    set.insert(state);
    while (!stack.empty()) {
        State t = stack.top();
        stack.pop();
        auto tmp = t.transitions.find(Symbol(special, "L"));
        if (tmp == t.transitions.end()) continue;
        vector<State> vec = tmp->second;
        for (int j = 0; j < vec.size(); j++) {
            stack.push(vec[j]);
            l_closure.push_back(vec[j]);
        }
    }
    return l_closure;
}

vector<State> DFABuilder::LClosureVec(vector<State> state_vec) {
    vector<State> l_closure;
    for (int i = 0; i < state_vec.size(); i++) {
        vector<State> single_closure = LClosure(state_vec[i]);
        l_closure.insert(l_closure.end(), single_closure.begin(), single_closure.end());
    }
    return l_closure;
}

int id = 0;
map<vector<State>, int> found_before;

DFAState DFABuilder::merge_states(vector<State> vector) {
    DFAState res;
    res.type = DFAState::internal;
    for (int i = 0; i < vector.size(); i++) {
        res.transitions.insert(vector[i].transitions.begin(), vector[i].transitions.end());
        res.NFAStates.insert(res.NFAStates.begin(), vector[i]);
        if (vector[i].type == State::accept) res.type = DFAState::accept;
        else if (vector[i].type == State::start) res.type = DFAState::start;
    }
    if (found_before.find(res.NFAStates) == found_before.end()) {
        res.id = id++;
        found_before.insert({res.NFAStates, res.id});;
    } else {
        res.id = found_before.find(res.NFAStates)->second;
    }
    return res;
}
