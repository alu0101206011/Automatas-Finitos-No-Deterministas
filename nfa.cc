#include <iostream> 
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

#include "nfa.h"

//
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
  int total_states_number, initial_state;
  std::string line;
  bool initial = false;
  std::stringstream ss;
  std::getline(reader_nfa, line, '\n');
  if (line.size() - 1 > 1) {
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
  std::getline(reader_nfa, line, '\n');
  if (line.size() - 1 != 1) {
    std::cerr << "There can only be one initial state. [Line 2 of the file]\n";
    exit(2);
  }
  initial_state = stoi(line);
  if (initial_state < 0) {
    std::cerr << "The states can't be a negative number\n";
    exit(2);
  }
  //nfa_.resize(total_states_number);
  int position_nfa = 0, size_transitions = 0, count = 3;
  std::set<int> list_position;
  while (!reader_nfa.eof()) {
    std::getline(reader_nfa, line, '\n');
    if (line.size() - 1 < 3) {
      std::cerr << "The node on line " << count << " of the file should"
                << " have more arguments.\nWrite ./nfa_simulation --help"
                << " for more info\n";
      exit(2);
    }
    std::cout << line << "\n";
    ss << line;
    //ss >> position_nfa >> nfa_[position_nfa].accepting >> size_transitions;         // HACER ATRIBUTO CON TODOS LOS ATRIBUTOS
/*     if (list_position.count(position_nfa)) {
      std::cerr << "The node on line " << count << " already exists\n";               NO ESTOY SEGURA DE QUE HAGA FALTA CON SETS
      exit(2);
    } */ 
    list_position.insert(position_nfa);
    if (position_nfa >= total_states_number) {
      std::cerr << "The node on line " << count << " exceeds the limit.\n";
      exit(2);
    }
    //nfa_[position_nfa].transitions.resize(size_transitions);
    for (unsigned iterator = 0; iterator < size_transitions; iterator++) {
      //ss >> nfa_[position_nfa].transitions[iterator].character;                      CORREGIR CON SETS
      //ss >> nfa_[position_nfa].transitions[iterator].state;
      if (ss.eof()) {
        std::cout << "Transitions do not correspond to the given number "
                  << "[Line " << count << " of de file]\n";
        exit(2);        
      }
      //std::cout << nfa_[position_nfa].transitions[iterator].character << " " << nfa_[position_nfa].transitions[iterator].state << "\n";
    }
    ss >> line;  // Quitamos \n
    if (!ss.eof()) {
      std::cout << "Transitions do not correspond to the given number "
                << "[Line " << count << " of de file]\n";
      exit(2);
    }
    ss.clear();
    ++count;
  }
  return reader_nfa;
}