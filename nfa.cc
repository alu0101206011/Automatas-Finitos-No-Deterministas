#include <iostream> 
#include <fstream>
#include <sstream>
#include <vector>

#include "nfa.h"

NFA::NFA(const std::string& file) {
  int total_states_number, initial_state;
  std::ifstream reader(file);
  std::string line;
  bool initial = false;
  std::stringstream ss;
  std::getline(reader, line, '\n');
  if (line.size() - 1 != 1) {
    std::cerr << "Las dos primeras lineas del fichero debe tener solo 1 elemento.\n";
    exit(1);
  }
  ss << line;
  ss >> total_states_number;

  std::getline(reader, line, '\n');
  if (line.size() - 1 != 1) {
    std::cerr << "Las dos primeras lineas del fichero debe tener solo 1 elemento.\n";
    exit(1);
  }
  initial_state = stoi(line);
  nfa_.resize(total_states_number);
  int position_nfa = 0, size_transitions = 0, count = 3;
  while (!reader.eof()) {
    std::getline(reader, line, '\n');
    if (line.size() - 1 < 3) {
      std::cerr << "El nodo de la linea " << count << " del fichero debe tener"
                << " mas argumentos.\n";
      exit(2);
    }
    std::cout << line << "\n";
    ss << line;
    ss >> position_nfa >> nfa_[position_nfa].accepting >> size_transitions;
    nfa_[position_nfa].transitions.resize(size_transitions);
    for (unsigned iterator = 0; iterator < size_transitions; iterator++) {
      ss >> nfa_[position_nfa].transitions[iterator].character;
      ss >> nfa_[position_nfa].transitions[iterator].state;
      if (ss.eof()) {
        std::cout << "no se corresponden alas transiciones con el numero dado.\n";
        exit(1);        
      }
      std::cout << nfa_[position_nfa].transitions[iterator].character << " " << nfa_[position_nfa].transitions[iterator].state << "\n";
    }
    ss >> line;  // Quitamos \n
    if (!ss.eof()) {
      std::cout << "no se corresponden las transiciones con el numero dado.\n";
      exit(1);
    }
    ss.clear();
    ++count;
  }
  reader.close();
}

void NFA::Write() {
/*    for (Transition hola : nfa_[3].transitions)
    std::cout << hola.character << "-" << hola.state << "->";
  std::cout << "\n";  */
}