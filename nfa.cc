/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Computabilidad y algoritmia
///
/// @author Anabel Díaz Labrador <alu0101206011@ull.edu.es>
/// @date 24 Nov 2020
/// @brief Non-Deterministic Finite Automaton class
///
/// @see https://en.wikipedia.org/wiki/Nondeterministic_finite_automaton

#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <string>

#include "nfa.h"

// Constructor of the NFA class
NFA::NFA(const std::string &kFile, int &open_file) {
  std::ifstream reader(kFile);
  if (reader) {
    if (!reader.eof()) {
      CreateNFA(reader);
      open_file = 0;
      reader.close();
    } else {
      open_file = 2;
      reader.close();
    }
  } else {
    open_file = 1;
  }
}

std::set<char> NFA::get_alphabet(void) const { 
  return alphabet_; 
}
std::set<State> NFA::get_set_states(void) const { 
  return set_states_;
}
int NFA::get_initital_state(void) const {
  return initial_state_;
}
std::set<State> NFA::get_accepted_states(void) const {
  return accepted_states_;
}

void NFA::set_alphabet(const std::set<char> &kNewAlphabet) {
  alphabet_ = kNewAlphabet;
}
void NFA::set_set_states(const std::set<State> &kNewStates) {
  set_states_ = kNewStates;
}
void NFA::set_initial_state(const int kNewInitialState) {
  initial_state_ = kNewInitialState;
}
void NFA::set_initial_state(const std::string &kInitialStateString,
                            const int kUpperRange) {
  initial_state_ = stoi(kInitialStateString);
  if ((initial_state_ < 0) || (initial_state_ > kUpperRange)) {
    std::cerr << "The states can't cross the limits\n";
    exit(2);
  }
}
void NFA::set_accepted_states(const std::set<State> &kNewAcceptedStates) {
  accepted_states_ = kNewAcceptedStates;
}

// Returns the State according to identifier
State NFA::GetState(int identifier) const {
  State result_state;
  for (State iterator : set_states_)
    if (iterator.get_state_name() == identifier)
      result_state = iterator;
  return result_state;
}

// Returns true if all characters of the string belongs to the alphabet
bool NFA::BelongToAlphabet(const std::string &kAnalyzeWord) {
  for (const char analyze_letter : kAnalyzeWord)
    if (!alphabet_.count(analyze_letter) && analyze_letter != '~')
      return false;
  return true;
}

// Write the result of the analyze string if kAnailyzeWord belong to the
// alphabet of the NFA
void
NFA::WriteResultSearch(const std::string &kAnalyzeWord, std::ostream &os) {
  if (!BelongToAlphabet(kAnalyzeWord)) {
    os << "No\n";
    return;
  }
  bool accepted = false;
  epsilon_path_.clear();
  if (kAnalyzeWord == "~") {
    accepted = AnalyzeString("", initial_state_);
  } else {
    accepted = AnalyzeString(kAnalyzeWord, initial_state_);
  }
  if (accepted) {
    os << "Si\n";
  } else {
    os << "No\n";
  }
}

// Method to write the NFA
void NFA::Write(std::ostream &os) {
  for (char state : alphabet_) 
    os << "Alafabeto: " << state << "\n";
  os << "\n";
  for (State state : accepted_states_) 
    os << "Aceptados: " << state << "\n";
  for (State state : set_states_) {
    os << "\nNodos nfa: " << state << "\n";
    for (char alphabet_letters : alphabet_)
      for (int state_int : state.GetNextState(alphabet_letters)) {
        os << "Sus next states usando simbolo '" << alphabet_letters 
           << "': \n";
        os << state_int << "\n";
      }
    if (state.NumberOfTransitions() == 0) 
      os << "\n";
  }
}

// Method that initializes the attributes of the NFA class given an input
// stream source
std::ifstream &NFA::CreateNFA(std::ifstream &reader_nfa) {
  int total_states_number, state;
  std::string line;
  std::stringstream buffer;
  std::getline(reader_nfa, line);
  total_states_number = stoi(line);
  if (total_states_number <= 0) {
    std::cerr << "The total number of states must be greater than zero. "
              << "[Line 1 of the file]\n";
    exit(2);
  }
  std::getline(reader_nfa, line);
  set_initial_state(line, total_states_number);
  int next_name_state = 0, size_transitions = 0, count = 3, accept_state = 0;
  char symbol;
  State read_state;
  while (!reader_nfa.eof()) {
    std::getline(reader_nfa, line, '\n');
    if (line.size() - 1 < 3) {
      std::cerr << "The node on line " << count << " of the file should"
                << " have more arguments.\nWrite ./nfa_simulation --help"
                << " for more info\n";
      exit(2);
    }
    buffer << line;
    buffer >> state >> accept_state >> size_transitions;
    read_state.set_state_name(state, total_states_number, count);
    accepted_state_into_limits(accept_state, count);
    for (unsigned iterator = 0; iterator < size_transitions; iterator++) {
      if (buffer.eof()) {
        std::cout << "Transitions do not correspond to the given number "
                  << "[Line " << count << " of de file]\n";
        exit(2);
      }
      buffer >> symbol >> next_name_state;
      if (total_states_number <= next_name_state || next_name_state < 0) {
        std::cout << "State number out of range [Line " << count
                  << " of de file]\n";
        exit(2);
      }
      read_state.SetNextState(next_name_state, symbol);
      alphabet_.insert(symbol);
    }
    buffer >> line;
    if (!buffer.eof()) {
      std::cout << "Transitions do not correspond to the given number "
                << "[Line " << count << " of de file]\n";
      exit(2);
    }
    if (accept_state == 1) 
      accepted_states_.insert(read_state);
    set_states_.insert(read_state);
    buffer.clear();  // to clean buffer before it is used again
    read_state.Clear();
    ++count;
  }
  return reader_nfa;
}

// Verify if the accepted state is in the limits
void NFA::accepted_state_into_limits(const int kAcceptedState,
                                     const int kNumLine) {
  if (kAcceptedState != 0 && kAcceptedState != 1) {
    std::cerr << "The accept state on line " << kNumLine << " must be a "
              << "boolean expresion.\n";
    exit(2);
  }
}

// Recursive method that returns true if the string is an accepted string
bool NFA::AnalyzeString(const std::string &analyze_word,
                        int current_identifier) {
  if (analyze_word.size() == 0)
    if (accepted_states_.count(current_identifier)) 
      return true;
  if (GetState(current_identifier).HasEpsilonTransitions()) {
    std::set<int> epsilon_transitions =
        GetState(current_identifier).GetEpsilonClosure();
    if (EpsilonPath(current_identifier))
      return false;
    for (int state : epsilon_transitions)
      if (AnalyzeString(analyze_word, state)) 
        return true;
  }
  if (analyze_word.size() > 1) {
    char symbol = analyze_word[0];
    std::string next_word = analyze_word.substr(1, analyze_word.size() - 1);
    std::set<int> next_id = GetState(current_identifier).GetNextState(symbol);
    if (next_id.empty())  // There are not next transitions
      return false;
    for (int state : next_id) {
      epsilon_path_.clear();
      if (AnalyzeString(next_word, state)) 
        return true;
    }
  } else if (analyze_word.size() == 1) {
    char symbol = analyze_word[0];
    std::string empty_word = "";
    std::set<int> next_id = GetState(current_identifier).GetNextState(symbol);
    for (int state : next_id) {
      epsilon_path_.clear();
      if (AnalyzeString(empty_word, state)) 
        return true;
    }
  }
  return false;
}

// Method that keeps track of which states have been visited through epsilon 
// transitions.
bool NFA::EpsilonPath(int state) {
  if (!epsilon_path_.count(state)) {
    epsilon_path_.insert(state);
    return false;
  } else {
    return true;
  }
}


