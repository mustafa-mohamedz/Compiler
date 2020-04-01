//
// Created by Ahmed on 3/24/2020.
//

#include "NFABuilder.h"
#include "NFA.h"
//TODO Remove alphabet
NFABuilder::NFABuilder(set<Symbol> alphabet){
    this->alphabet = alphabet;
}
//TODO Remove basicConstruct
NFA NFABuilder::basicConstruct(Symbol s) {
    NFA basic_nfa;
    //create the states
    vector<State> states;
    State start(State::start, 0, map<Symbol, std::vector<State>>());
    State accept(State::accept, 1, map<Symbol, std::vector<State>>());
    basic_nfa.start_state = start;
    basic_nfa.accept_state = accept;
    //update transitions
    std::vector<State> next_states;
    next_states.push_back(accept);
    basic_nfa.start_state.transitions.insert({s, next_states});
    //State addition
    states.push_back(basic_nfa.start_state);
    states.push_back(basic_nfa.accept_state);
    basic_nfa.states = states;
    return basic_nfa;
}
NFA NFABuilder::concatinate(NFA n1, NFA n2) {
    NFA first_nfa = n1;
    NFA second_nfa = n2;
    NFA result_nfa;

    int counter = 0;
    result_nfa.start_state = first_nfa.start_state;
    //Update second nfa states' numbers
    second_nfa.start_state.updateBy(first_nfa.states.size(), alphabet);
    second_nfa.accept_state.updateBy(first_nfa.states.size(), alphabet);
    //Update all states
    for (int i = 0; i < second_nfa.states.size(); ++i) {
        second_nfa.states[i].updateBy(first_nfa.states.size(), alphabet);
        second_nfa.states[i].type = State::internal;
    }
    //common state
    std::map<Symbol, std::vector<State>> common_transitions = second_nfa.states[0].transitions;
    State common_state(State::internal, first_nfa.states.size(), common_transitions);
    //Point to common state
    first_nfa.states[first_nfa.states.size()-1].transitions.insert({Symbol(special, "L"), {second_nfa.states[0]}});
    //Fill the result nfa
    for (int i = 0; i < first_nfa.states.size(); ++i) {
        if(i > 0) first_nfa.states[i].type = State::internal;
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
    State end_state(State::accept, counter, std::map<Symbol, std::vector<State>>());
    result_nfa.accept_state = end_state;
    result_nfa.states.push_back(end_state);

    return result_nfa;
}

NFA NFABuilder::oring(NFA n1, NFA n2) {
    NFA first_nfa = n1;
    NFA second_nfa = n2;
    NFA result_nfa;
    //Update states' numbers
    //Update states' numbers for first nfa
    first_nfa.start_state.updateBy(1, alphabet);
    first_nfa.accept_state.updateBy(1, alphabet);
    //Update all states
    for (int i = 0; i < first_nfa.states.size(); ++i) {
        first_nfa.states[i].updateBy(1, alphabet);
        first_nfa.states[i].type = State::internal;
    }
    //Update states' numbers for second nfa
    second_nfa.start_state.updateBy(first_nfa.states.size() + 1, alphabet);
    second_nfa.accept_state.updateBy(first_nfa.states.size() + 1, alphabet);
    //Update all internal states
    for (int i = 0; i < second_nfa.states.size(); ++i) {
        second_nfa.states[i].updateBy(first_nfa.states.size() + 1, alphabet);
        second_nfa.states[i].type = State::internal;
    }
    //Construct first new state
    //Next states adjusting
    std::vector<State> next_states;
    next_states.push_back(first_nfa.start_state);
    next_states.push_back(second_nfa.start_state);
    std::map<Symbol, std::vector<State>> start_transitions;
    start_transitions.insert({Symbol(special, "L"), next_states});
    State start_of_result(State::start, 0, start_transitions);
    //First state addition
    result_nfa.start_state = start_of_result;
    result_nfa.states.push_back(start_of_result);
    //Accept state addition
    State end_state(State::accept, first_nfa.states.size() + second_nfa.states.size() + 1, std::map<Symbol, std::vector<State>>());
    result_nfa.accept_state = end_state;
    //Update transitions of the input nfa
    std::vector<State> next_states_of_input;
    next_states_of_input.push_back(result_nfa.accept_state);
    first_nfa.states[first_nfa.states.size() - 1].transitions.insert({Symbol(special, "L"), next_states_of_input});
    second_nfa.states[second_nfa.states.size() - 1].transitions.insert({Symbol(special, "L"), next_states_of_input});
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

NFA NFABuilder::closure(NFA nfa) {
    NFA result_nfa;
    //Update states' numbers
    nfa.start_state.updateBy(1, alphabet);
    nfa.accept_state.updateBy(1, alphabet);
    //Update all internal states
    for (int i = 0; i < nfa.states.size(); ++i) {
        nfa.states[i].updateBy(1, alphabet);
        nfa.states[i].type = State::internal;
    }
    //Construct the accept state
    State end_state(State::accept, nfa.states.size() + 1, std::map<Symbol, std::vector<State>>());
    result_nfa.accept_state = end_state;
    //Construct first new state
    //Next states adjusting
    std::vector<State> next_states;
    next_states.push_back(nfa.start_state);
    std::map<Symbol, std::vector<State>> start_transitions;
    start_transitions.insert({Symbol(special, "L"), next_states});
    State start_of_result(State::start, 0, start_transitions);
    //First state addition
    result_nfa.start_state = start_of_result;
    result_nfa.states.push_back(start_of_result);
    //Update transitions of the input nfa
    std::vector<State> next_states_of_input;
    next_states_of_input.push_back(result_nfa.accept_state);
    next_states_of_input.push_back(nfa.states[0]);
    nfa.states[nfa.states.size() - 1].transitions.insert({Symbol(special, "L"), next_states_of_input});
    //Internal states addition
    for (int i = 0; i < nfa.states.size(); ++i) {
        result_nfa.states.push_back(nfa.states[i]);
    }
    result_nfa.states.push_back(end_state);
    return result_nfa;
}

NFA NFABuilder::extended_closure(NFA nfa) {
    NFA result_nfa = closure(nfa);
    Symbol s(special, "L");
    vector<State> next_states_of_start = result_nfa.states[0].transitions[s];
    next_states_of_start.push_back(result_nfa.accept_state);
    result_nfa.states[0].transitions[s].push_back(result_nfa.accept_state);
    result_nfa.start_state.transitions[s].push_back(result_nfa.accept_state);
    return result_nfa;
}