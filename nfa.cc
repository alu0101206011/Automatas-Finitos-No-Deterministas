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
/*    for (Transition hola : nfa_[3].transitions)
    std::cout << hola.character << "-" << hola.state << "->";
  std::cout << "\n";  */
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
  ss << line;
  ss >> total_states_number;
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
  ss << line;
  ss >> initial_state_;
  std::cout << initial_state_ << "\n";
  initial_state_ = stoi(line);
  if ((initial_state_ < 0) || (initial_state_ > total_states_number)) {
    std::cerr << "The states can't across the limits\n";
    exit(2);
  }
  int next_name_state = 0, size_transitions = 0, count = 3, accept_state = 0;
  char symbol;
  State read_state;

  std::getline(reader_nfa, line);
  std::cout << line << "\n";
  ss << line; 
  ss >> next_name_state >> accept_state;
  std::cout << next_name_state << " " << accept_state << " " << size_transitions << "\n";
/*   while (!reader_nfa.eof()) {
    std::getline(reader_nfa, line, '\n');
    if (line.size() - 1 < 3) {
      std::cerr << "The node on line " << count << " of the file should"
                << " have more arguments.\nWrite ./nfa_simulation --help"
                << " for more info\n";
      exit(2);
    }
    std::cout << line << "\n";
    ss << line; 
    ss >> next_name_state  >> accept_state >> size_transitions;
    ss >> symbol >> next_name_state;
    std::cout << next_name_state << " " << accept_state << " " << size_transitions << "\n";
    std::cout << symbol << " " << next_name_state << "\n";
    if ((next_name_state  >= total_states_number) || (next_name_state  < 0)) {
      std::cerr << "The node on line " << count << " is not in the limits.\n";
      exit(2);
    }
    if (accept_state != 0 && accept_state != 1) {
      std::cerr << "The accept state on line " << count << " must be a "
                << "boolean expresion.\n";
      exit(2);      
    }
    std::cout << "Linea: " << count << "Tamaño: " << size_transitions << "\n";
    for (unsigned iterator = 0; iterator < size_transitions; iterator++) {
      ss >> symbol >> next_name_state;
      read_state.SetNextState(next_name_state, symbol);
      alphabet_.insert(symbol);
      std::cout << iterator << "\n";
      if (ss.eof()) {
        std::cout << "Transitions do not correspond to the given number "
                  << "[Line " << count << " of de file]\n";
        exit(2);        
      }
      if(accept_state == 1)
        accepted_states_.insert(read_state);
      nfa_.insert(read_state); 
    }
    //ss >> line;  // Quitamos \n
    if (!ss.eof()) {
      std::cout << "Transitions do not correspond to the given number "
                << "[Line " << count << " of de file]\n";
      exit(2);
    }
    ss.clear();
    ++count;
  } */
  return reader_nfa;
}