#include "FinalNFA.h"

FinalNFA::FinalNFA(std::vector<NFA> NFAList, set<Symbol> alphabet) {
    this->alphabet = alphabet;
    //Update states' numbers for all NFAs
    int updateCounter = 1;
    for (vector<NFA>::size_type j = 0; j < NFAList.size(); j++) {
        //Update states' numbers
        NFAList[j].start_state.updateBy(updateCounter, alphabet);
        NFAList[j].accept_state.updateBy(updateCounter, alphabet);
        //Update all states
        for (int i = 0; i < NFAList[j].states.size(); ++i) {
            NFAList[j].states[i].updateBy(updateCounter, alphabet);
            if(NFAList[j].states[i].type == State::start){
                NFAList[j].states[i].type = State::internal;
            }
        }
        updateCounter += NFAList[j].states.size();
    }

    //Construct first new state
    //Next states adjusting
    std::vector<State> next_states;
    for (vector<NFA>::size_type j = 0; j < NFAList.size(); j++) {
        next_states.push_back(NFAList[j].start_state);
    }
    //First state addition
    std::map<Symbol, std::vector<State>> start_transitions;
    start_transitions.insert({Symbol(special, "L"), next_states});
    State start_of_result(State::start, 0, start_transitions);
    this->start_state = start_of_result;
    this->all_state_list.push_back(start_of_result);

    //add accept states
    for (vector<NFA>::size_type j = 0; j < NFAList.size(); j++) {
        this->accept_state_list.push_back(NFAList[j].accept_state);
    }

    //All states addition
    for (vector<NFA>::size_type j = 0; j < NFAList.size(); j++) {
        //insert all states
        for (int i = 0; i < NFAList[j].states.size(); ++i) {
            this->all_state_list.push_back(NFAList[j].states[i]);
        }

    }
}

void FinalNFA::print(set<Symbol> alphabet) {
    for (int i = 0; i < this->all_state_list.size(); ++i) {
        State s = this->all_state_list[i];
        std::cout << "State " << s.id << std::endl;
        for (auto elem : alphabet) {
            if (s.transitions.find(elem) != s.transitions.end()){
                std::vector<State> next = s.transitions.find(elem)->second;
                for (int k = 0; k < next.size(); ++k) {
                    std::cout << "#i/p: " << elem.value << std::endl << s.id << "-->" << next[k].id << std::endl;
                }
            }
        }
    }
}
