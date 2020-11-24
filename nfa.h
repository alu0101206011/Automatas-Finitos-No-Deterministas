/// @class NFA
///
/// @brief Non-Deterministic Finite Automaton class
///
/// @author Anabel Díaz Labrador <alu0101206011@ull.edu.es> 
/// @date 23 Nov 2020

#include "state.h"

class NFA {
  private:
    std::set<char> alphabet_;  //The alphabet of NFA
    std::set<State> set_states_;  // Set of states of NFA
    int initial_state_;  // The start state
    std::set<State> accepted_states_;  // Only the accepted states are here
  public:
    /// @brief Initialize all attributes using the following parameters
    /// @param kFile
    NFA(const std::string& kFile, int& open_file);

    std::set<char> get_alphabet(void) const;
    std::set<State> get_set_states(void) const;
    int get_initital_state(void) const;
    std::set<State> get_accepted_states(void) const;

    void set_alphabet(const std::set<char>& kNewAlphabet);
    void set_set_states(const std::set<char>& kNewStates);
    void set_initial_state(const int kNewInitialState);
    void set_accepted_states(const std::set<char>& kNewAcceptedStates);
    
    /// @brief If the string belongs to the alphabet
    /// @param kAnalyzeWord  
    /// @return true if string belongs to the alphabet
    bool BelongToAlphabet(const std::string& kAnalyzeWord);

    /// @brief Write using ostream the result of the search of accepted strings
    /// in NFA
    /// @param os
    /// @param kAnalyzeWord
    void WriteResultSearch(std::ostream& os, const std::string& kAnalyzeWord);

    /// @brief Write the NFA construction
    void Write(std::ostream& os);

    private:
    /// @brief Initializes the attributes of the NFA class given an input
    /// stream source
    /// @param newNFA
    /// @return reader to be able to close the string
    std::ifstream& CreateNFA(std::ifstream& newNFA);

    /// @brief Recursive method that returns true if the string is an accepted 
    /// string
    /// @param kAnalyzeWord
    /// @param current_identifier
    /// @return If is an accepted string or not
    bool AnalyzeString(const std::string& kAnalyzeWord, 
                             int current_identifier);

    /// @brief Returns state given its ID number
    /// @param identifier
    /// @return
    State GetState(int identifier) const;
};