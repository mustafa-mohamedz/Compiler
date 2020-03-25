//
// Created by Ahmed on 3/24/2020.
//

#include <winsock.h>
#include "NFABuilder.h"
#include "NFA.h"

std::vector<NFA> NFABuilder::basicConstruct(std::vector<char> alphabet) {
    std::vector<NFA> basic_nfa_list;
    for (int t = 0; t < alphabet.size(); ++t) {
        RegularGrammar rg("");
        NFA temp(rg);
        std::vector<State> states;
        //create the states
        State start(State::start, 0, std::map<char, std::vector<State>>());
        State accept(State::accept, 1, std::map<char, std::vector<State>>());
        temp.start_state = start;
        temp.accept_state = accept;
        //update transitions
        std::vector<State> next_states;
        next_states.push_back(accept);
        start.transitions[alphabet[t]] = next_states;
        temp.start_state.transitions = start.transitions;
        //State addition
        states.push_back(start);
        states.push_back(accept);
        temp.states = states;
        basic_nfa_list.push_back(temp);
    }
    return basic_nfa_list;
}
NFA NFABuilder::concatinate(NFA n1, NFA n2, std::vector<char> alphabet) {
    NFA first_nfa = n1;
    NFA second_nfa = n2;
    RegularGrammar rg("");
    NFA result_nfa(rg);

    int counter = 0;
    result_nfa.start_state = first_nfa.start_state;
    //Update second nfa states' numbers
    second_nfa.start_state.updateBy(first_nfa.states.size() - 1, alphabet);
    second_nfa.accept_state.updateBy(first_nfa.states.size() - 1, alphabet);
    //Update all internal states
    for (int i = 0; i < second_nfa.states.size(); ++i) {
        second_nfa.states[i].updateBy(first_nfa.states.size() - 1, alphabet);
    }
    //common state
    std::map<char, std::vector<State>> common_transitions = second_nfa.states[0].transitions;
    State common_state(State::internal, first_nfa.states.size()-1, common_transitions);
    //Fill the result nfa
    for (int i = 0; i < first_nfa.states.size()-1; ++i) {
        result_nfa.states.push_back(first_nfa.states[i]);
        counter++;
    }
    result_nfa.states.push_back(common_state);
    counter++;
    for (int i = 1; i < second_nfa.states.size() - 1; ++i) {
        State temp(State::internal,  counter, second_nfa.states[i].transitions);
        result_nfa.states.push_back(temp);
        counter++;
    }
    State end_state(State::accept, counter, std::map<char, std::vector<State>>());
    result_nfa.accept_state = end_state;
    result_nfa.states.push_back(end_state);

    return result_nfa;
}

NFA NFABuilder::oring(NFA n1, NFA n2, std::vector<char> alphabet) {
    NFA first_nfa = n1;
    NFA second_nfa = n2;
    RegularGrammar rg("");
    NFA result_nfa(rg);
    //Update states' numbers
    //Update states' numbers for first nfa
    first_nfa.start_state.updateBy(1, alphabet);
    first_nfa.accept_state.updateBy(1, alphabet);
    //Update all internal states
    for (int i = 0; i < first_nfa.states.size(); ++i) {
        first_nfa.states[i].updateBy(1, alphabet);
    }
    //Update states' numbers for second nfa
    second_nfa.start_state.updateBy(first_nfa.states.size() + 1, alphabet);
    second_nfa.accept_state.updateBy(first_nfa.states.size() + 1, alphabet);
    //Update all internal states
    for (int i = 0; i < second_nfa.states.size(); ++i) {
        second_nfa.states[i].updateBy(first_nfa.states.size() + 1, alphabet);
    }
    //Construct first new state
    //Next states adjusting
    std::vector<State> next_states;
    next_states.push_back(first_nfa.start_state);
    next_states.push_back(second_nfa.start_state);
    std::map<char, std::vector<State>> start_transitions;
    start_transitions['L'] = next_states;
    State start_of_result(State::start, 0, start_transitions);
    //First state addition
    result_nfa.start_state = start_of_result;
    result_nfa.states.push_back(start_of_result);
    //Accept state addition
    State end_state(State::accept, first_nfa.states.size() + second_nfa.states.size() + 1, std::map<char, std::vector<State>>());
    result_nfa.accept_state = end_state;
    //Update transitions of the input nfa
    std::vector<State> next_states_of_input;
    next_states_of_input.push_back(result_nfa.accept_state);
    first_nfa.states[first_nfa.states.size() - 1].transitions['L'] = next_states_of_input;
    second_nfa.states[second_nfa.states.size() - 1].transitions['L'] = next_states_of_input;
    //Internal states addition
    for (int i = 0; i < first_nfa.states.size(); ++i) {
        result_nfa.states.push_back(first_nfa.states[i]);
    }
    for (int i = 0; i < second_nfa.states.size(); ++i) {
        result_nfa.states.push_back(second_nfa.states[i]);
    }
    result_nfa.states.push_back(end_state);
    return result_nfa;
}