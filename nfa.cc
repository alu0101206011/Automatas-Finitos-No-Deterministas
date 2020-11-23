#include <iostream> 
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <string>

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

State NFA::GetState(int identifier) const {
  State result_state;
  for (State iterator : nfa_) {
    if (iterator.state_name_ == identifier) {
      result_state = iterator;
    }
  }
  return result_state;
}

bool NFA::BelongToAlphabet(const std::string& kAnalyzeWord) {
  for (const char analyze_letter : kAnalyzeWord)
    if (!alphabet_.count(analyze_letter))  // If count = 0, analyze_letter is not in the alphabet
      return false;
  return true;
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
    ss >> line;
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

bool NFA::AnalyzeString(std::string& analyze_word, int current_id) {
  if (analyze_word.size() == 0) {
    std::cout << current_id << " Num de estados aceptados: " << accepted_states_.count(current_id) << "\n";
    if (accepted_states_.count(current_id)) {
      std::cout << "cadena vacia:" << analyze_word << "\n";
      return true;
    } 
  }

  if (analyze_word.size() > 1) {
    char symbol = analyze_word[0];
    std::string next_word = analyze_word.substr(1, analyze_word.size() - 1);
    std::set<int> next_id = GetState(current_id).GetNextState(symbol);

    if (next_id.empty()) {
      return false;
    } 

    for (int iterator : next_id) {
      std::cout << "symbol: " << symbol << " nodo: " << iterator <<  " cadena: " << next_word << "\n";
      if (AnalyzeString(next_word, iterator))
        return true;
    }

  } else if (analyze_word.size() == 1) {
    char symbol = analyze_word[0];
    std::string empty_word = "";
    std::set<int> next_id = GetState(current_id).GetNextState(symbol);
    for (int iterator : next_id) {
      std::cout << "symbol: " << symbol << " nodo: " << iterator <<  " cadena: " << empty_word << "\n";
      if (AnalyzeString(empty_word, iterator))
        return true;
    }
  }
  return false;
}