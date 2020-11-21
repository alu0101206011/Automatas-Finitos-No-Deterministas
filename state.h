/// @class State
///
/// @brief This class works with states and attributes 
/// behavior.
///
/// @author Anabel Díaz Labrador <alu0101206011@ull.edu.es> 
/// @date 20 Nov 2020

#include "transition.h"

class State {
  public:
    int state_name_;  // state identification
    std::set<Transition> transitions_;  // Set of Transition class

    /// @brief Default constructor
    State(void);

    /// @brief Constructor
    /// @param kStateName
    State(const int& kStateName);

    /// @brief Copy constructor
    /// @param kState
    State(const State& kState);

    /// Default destructor
    ~State (void);

    /// @brief remove all the values of the transition set 
    /// and sets the state_name_ back to its default value 
    void Clear(void);

    /// @brief Returns the next state using the symbol given as parameter
    /// @param symbol
    std::set<int> GetNextState(char symbol) const;

    /// @brief Returns all epsilon transitions
    std::set<int> GetEpsilonTransitions(void);

    /// @brief Returns true if transitions_ has epsilons transitions
    bool HasEpsilonTransitions(void);

    /// @brief Put a new state in transitions_
    /// @param next_state_name
    /// @param symbol
    void SetNextState(int next_state_name, char symbol);

    /// @brief Returns the total number of transitions
    int NumberOfTransitions(void) const;

    /// @brief Returns true if the symbol it has as a parameter is used to make a 
    /// transition
    /// @param symbol
    bool symbolIsUsed (char symbol) const;

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