  
/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Computabilidad y algoritmia
///
/// @author Anabel Díaz Labrador <alu0101206011@ull.edu.es> 
/// @date 10 Nov 2020
/// @brief implementation of class Automata
/// 
/// @see https://en.wikipedia.org/wiki/Automata_theory
/// 
/// To compile: make 
/// To clean files: make clean

#include <iostream> 
#include <fstream>
#include <set>
#include <vector>

#include "nfa.h"

void ErrorMessage(const int);

int main(int argc, char *argv[]) {
  if (argc != 4 && argc != 2) { ErrorMessage(1); }
  if ((std::string)argv[1] == "--help" || (std::string)argv[1] == "-h")
    if (argc == 2) {
      ErrorMessage(2);
    } else {
      ErrorMessage(1);
    }

  std::ifstream reader(argv[1]);
  if (!reader) 
    ErrorMessage(3);
  if(reader.eof()) 
    ErrorMessage(4);

  NFA nfa(argv[1]);
  nfa.Write();

  

 return 0;
}

// Show error messages in terminal
void ErrorMessage(const int kError) {
  if (kError == 1) {
    std::cerr << "Invalid arguments to function.\n" 
              << "Write ./nfa_simulation --help for more info\n";
    exit(1);
  } else if (kError == 2) {
    std::cerr << "Usage: ./nfa_simulation input.nfa input.txt output.txt\n\n"
              << "input.nfa File with behaviour of nfa, that contains:\n"
              << "\tLine 1: Total number of states of NFA.\n"
              << "\tLine 2: Initial state of NFA\n"
              << "\tBelow is a line for each of the states. Each line will "
              << "contain the following numbers, separated from each other "
              << "by blanks:\n "
              << "\t\t- State identification number. The automata states "
              << "are represented by natural numbers. For these numbers "
              << "\n\t\twe must start with 0 until the total "
              << "number of states - 1.\n\t\t"
              << "- Accepting state. Boolean expresion that represents "
              << "whether the state is an accepting state or not.\n\t\t"
              << "- Number of transitions the state has.\n\t\t"
              << "- Next, for each of the transitions, and using spaces by "
              << "blanks as separators, the following information will be "
              << "detailed:\n\t\t\t"
              << "- Input symbol required for the transition to occur. To "
              << "represent the empty string (do not consume input "
              << "\n\t\t\tsymbol) will use the character '~' (ASCII code 126)."
              << "\n\t\t\t- Transition destination state.\n\n"
              << "input.txt Contains a series of strings (one string per line)"
              << " over the NFA alphabet specified in the input.nfa file\n"
              << "\noutput.txt Have to write the same strings from the input "
              << "file followed by a text -- Si / No indicative of the "
              << "acceptance \n(or not) of the string in question.\n"
              << "\nFor OPTION:\n" 
              << "\t-h,--help\t\tShow this help message\n";
    exit(1);
  } else if (kError == 3) {
    std::cerr << "Error: file could not be opened\n" 
              << "Write ./nfa_simulation --help for more info\n";
    exit(1);
  } else if (kError == 4) {
    std::cerr << "Error input.nfa cannot be empty\n"
              << "Write ./nfa_simulation --help for more info\n";
  }
}