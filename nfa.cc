/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Computabilidad y algoritmia
///
/// @author Anabel Díaz Labrador <alu0101206011@ull.edu.es>
/// @date 23 Nov 2020
/// @brief Non-Deterministic Finite Automaton class
///
/// @see https://en.wikipedia.org/wiki/Nondeterministic_finite_automaton

#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <string>

#include "nfa.h"

// Constructor
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
void NFA::set_accepted_states(const std::set<State> &kNewAcceptedStates) {
  accepted_states_ = kNewAcceptedStates;
}

// Returns the State according to identifier
State NFA::GetState(int identifier) const {
  State result_state;
  for (State iterator : set_states_)
    if (iterator.state_name_ == identifier)
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
void NFA::WriteResultSearch(std::ostream &os, const std::string &kAnalyzeWord) {
  if (!BelongToAlphabet(kAnalyzeWord)) {
    os << "Error\n";
  } 
  bool accepted = false;
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
        os << "Sus next states usando simbolo '" << alphabet_letters << "': \n";
        os << state_int << "\n";
      }
    if (state.NumberOfTransitions() == 0) 
      os << "\n";
  }
}

// Method that initializes the attributes of the NFA class given an input
// stream source
std::ifstream &NFA::CreateNFA(std::ifstream &reader_nfa) {
  int total_states_number;
  std::string line;
  std::stringstream ss;
  std::getline(reader_nfa, line);
  total_states_number = stoi(line);
  if (total_states_number <= 0) {
    std::cerr << "The total number of states must be greater than zero. "
              << "[Line 1 of the file]\n";
    exit(2);
  }
  std::getline(reader_nfa, line);
  initial_state_ = stoi(line);
  if ((initial_state_ < 0) || (initial_state_ > total_states_number)) {
    std::cerr << "The states can't cross the limits\n";
    exit(2);
  }
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
    ss << line;
    ss >> read_state.state_name_ >> accept_state >> size_transitions;
    if ((read_state.state_name_ >= total_states_number) ||
        (read_state.state_name_ < 0)) {
      std::cerr << "The node on line " << count << " is not in the limits.\n";
      exit(2);
    }
    if (accept_state != 0 && accept_state != 1) {
      std::cerr << "The accept state on line " << count << " must be a "
                << "boolean expresion.\n";
      exit(2);
    }
    for (unsigned iterator = 0; iterator < size_transitions; iterator++) {
      if (ss.eof()) {
        std::cout << "Transitions do not correspond to the given number "
                  << "[Line " << count << " of de file]\n";
        exit(2);
      }
      ss >> symbol >> next_name_state;
      if (total_states_number <= next_name_state || next_name_state < 0) {
        std::cout << "State number out of range [Line " << count
                  << " of de file]\n";
        exit(2);
      }
      read_state.SetNextState(next_name_state, symbol);
      alphabet_.insert(symbol);
    }
    ss >> line;
    if (!ss.eof()) {
      std::cout << "Transitions do not correspond to the given number "
                << "[Line " << count << " of de file]\n";
      exit(2);
    }
    if (accept_state == 1) 
      accepted_states_.insert(read_state);
    set_states_.insert(read_state);
    ss.clear();  // to clean buffer before it is used again
    read_state.Clear();
    ++count;
  }
  return reader_nfa;
}

// Recursive method that returns true if the string is an accepted string
bool NFA::AnalyzeString(const std::string &analyze_word,
                        int current_identifier) {
  if (analyze_word.size() == 0)
    if (accepted_states_.count(current_identifier)) 
      return true;
  if (GetState(current_identifier).HasEpsilonTransitions()) {
    std::set<int> epsilon_transitions =
        GetState(current_identifier).GetEpsilonTransitions();
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
    for (int iterator : next_id)
      if (AnalyzeString(next_word, iterator)) 
        return true;
  } else if (analyze_word.size() == 1) {
    char symbol = analyze_word[0];
    std::string empty_word = "";
    std::set<int> next_id = GetState(current_identifier).GetNextState(symbol);
    for (int iterator : next_id)
      if (AnalyzeString(empty_word, iterator)) 
        return true;
  }
  return false;
}