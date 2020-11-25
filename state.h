/// @class State
///
/// @brief This class works with states and attributes
/// behavior.
///
/// @author Anabel Díaz Labrador <alu0101206011@ull.edu.es>
/// @date 20 Nov 2020

#include "transition.h"

class State {
 private:
  int state_name_;  // state identification
  std::set<Transition> transitions_;  // Set of Transition class
 public:
  /// @brief Default constructor
  State(void);

  /// @brief Constructor
  /// @param kStateName
  State(const int& kStateName);

  /// @brief Copy constructor
  /// @param kState
  State(const State& kState);

  /// @brief Default destructor
  ~State(void);

  int get_state_name(void) const;
  std::set<Transition> get_transitions(void) const;

  void set_state_name(const int kNewStateName);
  void set_state_name(const int kNewStateName, const int kUpperRange,
                      const int kNumLine);
  void set_transitions(const std::set<Transition>& NewTransitions);

  /// @brief remove all the values of the transition set
  /// and sets the state_name_ back to its default value
  void Clear(void);

  /// @param symbol
  /// @return The next state using the symbol given as parameter
  std::set<int> GetNextState(char symbol) const;

  /// @brief Method to get epsilon transitions of the state
  /// @return set with all epsilon transitions of this state
  std::set<int> GetEpsilonClosure(void);

  /// @brief Check if the current state has epsilon transitions
  /// @return True if transitions_ has epsilons transitions
  bool HasEpsilonTransitions(void);

  /// @brief Put a new state in transitions_
  /// @param next_state_name
  /// @param symbol
  void SetNextState(int next_state_name, char symbol);

  /// @brief Method to access to the total number of transition of this state
  /// @return The total number of transitions
  int NumberOfTransitions(void) const;

  /// @brief Method to know if this symbol is used to make a transition
  /// @param symbol
  /// @return True if the symbol it has as a parameter is used to make a
  /// transition
  bool SymbolIsUsed(char symbol) const;

  /// @brief Overloading of operator =
  /// @param kOtherState
  State& operator=(const State& kOtherState);

  /// @brief Overloading of operator ==
  /// @param kOtherState
  bool operator==(const State& kOtherState) const;

  /// @brief Overloading of operator <
  /// @param kOtherState
  bool operator<(const State& kOtherState) const;

  /// @brief Friend function used to overload operator <<
  /// @param os
  /// @param kOtherState
  friend std::ostream& operator<<(std::ostream& os, const State& kOtherState);
};