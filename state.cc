#include <iostream>
#include <set>
#include <vector>
#include <fstream>

#include "state.h"

// Default constructor
State::State(void): state_name_(-1), transitions_() {}

// Constructor
State::State(const int &kStateName): state_name_(kStateName), transitions_() {}

// Copy constructor
State::State(const State &kState) {
  state_name_ = kState.state_name_;
  transitions_ = kState.transitions_;
}

// Default destructor
State::~State(void) {
  state_name_ = -1;
  transitions_.clear();
}

// Remove all the values of the transition set and sets the state_name_ 
// back to its default value
void State::Clear(void) {
  state_name_ = -1;
  transitions_.clear();
}

// Returns the next state using the symbol given as parameter
std::set<int> State::GetNextState(char symbol) const {
  std::set<int> result;
  for (Transition transition : transitions_)
    if (transition.symbol == symbol) 
      result.insert(transition.nextState);
  return result;
}

// Returns all epsilon transitions
std::set<int> State::GetEpsilonTransitions(void) {
  std::set<int> result;
  if (HasEpsilonTransitions()) {
    for (Transition transition : transitions_)
      if (transition.symbol == '~') 
        result.insert(transition.nextState);  
  } else {
    std::cerr << "This state has not epsilon transitions\n";
  }
  return result;
}

// Returns true if transitions_ has epsilons transitions
bool State::HasEpsilonTransitions(void) {
  for (Transition transition : transitions_)
    if (transition.symbol == '~')
      return true;
  return false;
}

// Put a new state in transitions_
void State::SetNextState(int next_state_name, char symbol) {
  Transition new_transition(next_state_name, symbol);
  transitions_.insert(new_transition);
}

// Returns the total number of transitions
int State::NumberOfTransitions(void) const {
  return transitions_.size();
}

// Returns true if the symbol it has as a parameter is used to make a 
// transition
bool State::symbolIsUsed(char symbol) const {
  for (Transition transition : transitions_)
    if (transition.symbol == symbol) 
      return true;
  return false;
}

// Overloading of operator =
State& State::operator=(const State& kOtherState) {
  state_name_ = kOtherState.state_name_;
  transitions_ = kOtherState.transitions_;
}

// Overloading of operator ==
bool State::operator==(const State& kOtherState) const {
  if (state_name_ == kOtherState.state_name_) 
    if (transitions_ == kOtherState.transitions_)
      return true;
  return false;
}

// Overloading of operator <
bool State::operator<(const State& kOtherState) const {
  if (state_name_ < kOtherState.state_name_)
    return true;
  return false;
}

// Friend function used to overload operator <<
std::ostream& operator<<(std::ostream& os, const State& kOtherState) {
  return os << kOtherState.state_name_;
}