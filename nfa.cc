#include <iostream> 
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

#include "nfa.h"

// Constructor
NFA::NFA(const std::string& kFile, int open_file) {
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

// Method to write the NFA
void NFA::Write() {
  for (State state : nfa_) {
    std::cout << "Nodos nfa: " << state << "\n";
    std::cout << "Sus next states usando simbolo 'a': \n";
    for (int state_int : state.GetNextState('a'))
      std::cout << state_int << "\n";  
    if (state.NumberOfTransitions() == 0)
      std::cout << "{}\n";
  }
  for (State state : accepted_states_)
    std::cout << "Aceptados: " << state << "\n";
  for (char state : alphabet_) 
    std::cout << "Alafabeto: " << state << "\n";
}

// 
std::ifstream& NFA::CreateNFA(std::ifstream& reader_nfa) {
  int total_states_number;
  std::string line;
  bool initial = false;
  std::stringstream ss;
  std::getline(reader_nfa, line);
  if (line.size() != 1) {
    std::cerr << "There can only be one number of total state. [Line 1 of "
              << "the file]\n";
    exit(2);
  }
  total_states_number = stoi(line);
  if (total_states_number <= 0) {
    std::cerr << "The total number of states must be greater than zero. "
              << "[Line 1 of the file]\n";
    exit(2);
  }
  std::getline(reader_nfa, line);
  if ((line.size() != 1)) {
    std::cerr << "There can only be one initial state. [Line 2 of the file]\n";
    exit(2);
  }
  initial_state_ = stoi(line);
  if ((initial_state_ < 0) || (initial_state_ > total_states_number)) {
    std::cerr << "The states can't across the limits\n";
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
    ss >> read_state.state_name_  >> accept_state >> size_transitions;
    if ((read_state.state_name_  >= total_states_number) || 
        (read_state.state_name_  < 0)) {
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
        std::cout << "State number out of range [Line " 
                  << count << " of de file]\n";
        exit(2);
      }
      read_state.SetNextState(next_name_state, symbol);
      alphabet_.insert(symbol);
    }
    if (!ss.eof()) {
      std::cout << "Transitions do not correspond to the given number "
                << "[Line " << count << " of de file]\n";
      exit(2);
    }
    if(accept_state == 1)
      accepted_states_.insert(read_state);
    nfa_.insert(read_state); 
    ss.clear();
    read_state.Clear();
    ++count;
  }
  return reader_nfa;
}