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
    DFAState closure = build_DFA_state(LClosure(s0));
    set.insert(closure);
    queue.push(closure);
    while (!queue.empty()) {
        DFAState t = queue.front();
        queue.pop();
        auto it = t.transitions.begin();
        while (it != t.transitions.end()) {
            std::vector<State> l_closure_vec = LClosureVec((it->second));
            DFAState u = build_DFA_state(l_closure_vec);
            if (set.find(u) == set.end()) {
                set.insert(u);
                queue.push(u);
            }
            if (u.NFAStates.size() != 0) t.DFATransitions.insert(pair<Symbol, DFAState>(it->first, u));
            it++;
        }
        dfa.states.push_back(t);
    }
    for (int i = 0; i < dfa.states.size(); i++) {
        if (dfa.states[i].type == DFAState::start) {
            dfa.start_state = dfa.states[i];
        } else if (dfa.states[i].type == DFAState::accept) {
            int min = INT_MAX;
            Production min_production;
            for (int j = 0; j < dfa.states[i].NFAStates.size(); j++) {
                if (dfa.states[i].NFAStates[j].type == State::accept &&
                    dfa.states[i].NFAStates[j].accepted_production.priority < min) {
                    min_production = dfa.states[i].NFAStates[j].accepted_production;
                    min = dfa.states[i].NFAStates[j].accepted_production.priority;
                }
            }
            dfa.states[i].accepted_production = min_production;
            dfa.accept_states.push_back(dfa.states[i]);
        }
    }
    return dfa;
}

vector<State> DFABuilder::LClosure(State state) {
    state = global_nfa.all_state_list[state.id];
    vector<State> l_closure;
    set<int> set;
    stack<State> stack;
    stack.push(state);
    set.insert(state.id);
    while (!stack.empty()) {
        State t = stack.top();
        stack.pop();
        l_closure.push_back(t);
        auto tmp = t.transitions.find(Symbol(special, "L"));
        if (tmp == t.transitions.end()) continue;
        vector<State> vec = tmp->second;
        for (int j = 0; j < vec.size(); j++) {
            if (set.find(vec[j].id) == set.end()) {
                stack.push(global_nfa.all_state_list[vec[j].id]);
                set.insert(vec[j].id);
            }
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

DFAState DFABuilder::build_DFA_state(vector<State> vector) {
    DFAState res;
    std::set<int> ids;
    for (int i = 0; i < vector.size(); i++) {
        ids.insert(vector[i].id);
    }
    res.type = DFAState::internal;
    for (int i = 0; i < vector.size(); i++) {
        auto it = vector[i].transitions.begin();
        while (it != vector[i].transitions.end()) {
            std::vector<State> next_transition;
            for (int j = 0; j < it->second.size(); j++) {
                if (ids.find(it->second[j].id) == ids.end()) {
                    next_transition.push_back(global_nfa.all_state_list[it->second[j].id]);
                }
            }
            if (next_transition.size() != 0)
                res.transitions.insert(pair<Symbol, std::vector<State>>(it->first, next_transition));
            it++;
        }
        vector[i].transitions = res.transitions;
        res.NFAStates.insert(res.NFAStates.begin(), vector[i]);
        if (vector[i].type == State::accept) res.type = DFAState::accept;
        else if (vector[i].type == State::start && res.type != DFAState::accept) res.type = DFAState::start;
    }
    if (found_before.find(res.NFAStates) == found_before.end()) {
        res.id = id++;
        found_before.insert({res.NFAStates, res.id});;
    } else {
        res.id = found_before.find(res.NFAStates)->second;
    }
    return res;
}
