//
// Created by Amr Geneidy on 3/25/20.
//

#include <queue>
#include "DFABuilder.h"
#include "DFA.h"
#include "State.h"

DFA DFABuilder::basicConstruct(NFA nonDeterministicAutomata) {
    DFA dfa;
    State s0 = nonDeterministicAutomata.start_state;
    std::set<State> set;
    std::queue<State> queue;
    State closure = merge_states(LClosure(s0));
    dfa.start_state = closure;
    closure.type = State::start;
    dfa.states.push_back(closure);
    set.insert(closure);
    queue.push(closure);
    while (!queue.empty()) {
        State t = queue.front();
        queue.pop();
        auto it = t.transitions.begin();
        while (it != t.transitions.end()) {
            State u = merge_states(LClosureVec(it->second));
            if (set.find(u) == set.end()) {
                set.insert(u);
                queue.push(u);
                dfa.states.push_back(u);
            }
            std::vector<State> u_vec;
            u_vec.push_back(u);
            t.transitions.insert(std::pair<char, std::vector<State>>(it->first, u_vec));
            it++;
        }
    }
    return dfa;
}

std::vector<State> DFABuilder::LClosure(State state) {
    vector<State> l_closure;
    set<State> set;
    std::stack<State> stack;
    stack.push(state);
    set.insert(state);
    while (!stack.empty()) {
        State t = stack.top();
        stack.pop();
        auto tmp = t.transitions.find('L');
        if (tmp == t.transitions.end()) continue;
        vector<State> vec = tmp->second;
        for (int j = 0; j < vec.size(); j++) {
            stack.push(vec[j]);
            l_closure.push_back(vec[j]);
        }
    }
    return l_closure;
}

std::vector<State> DFABuilder::LClosureVec(std::vector<State> state_vec) {
    vector<State> l_closure;
    for (int i = 0; i < state_vec.size(); i++) {
        vector<State> single_closure = LClosure(state_vec[i]);
        l_closure.insert(l_closure.end(), single_closure.begin(), single_closure.end());
    }
    return l_closure;
}

int id = 0;

State DFABuilder::merge_states(vector<State> vector) {
    State res;
    res.num = id++;
    for (int i = 0; i < vector.size(); i++) {
        res.transitions.insert(vector[i].transitions.begin(), vector[i].transitions.end());
    }
    return res;
}
