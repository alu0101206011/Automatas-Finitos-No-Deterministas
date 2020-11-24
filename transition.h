/// @class Transitions
///
/// @brief a class that saves all transitions in a state
///
/// @author Anabel Díaz Labrador <alu0101206011@ull.edu.es>
/// @date 20 Nov 2020

class Transition {
 public:
  char symbol;    // what the state needs to transition
  int nextState;  // will transit to this state

  /// @brief Initialize all attributes using the following parameters
  Transition(void);

  /// @brief Initialize all attributes using the following parameters
  /// @param nextState
  /// @param userSymbol
  Transition(int nextState, char userSymbol);

  /// @brief Initialize all attributes using the following parameters
  /// @param kNewTransition
  Transition(const Transition& kNewTransition);

  /// @brief Default destructor
  ~Transition(void);

  /// @brief Overloading of operator =
  /// @param kOtherTransition
  /// @return the class object itself
  Transition& operator=(const Transition& kOtherTransition);

  /// @brief Overloading of operator ==
  /// @param kOtherTransition
  /// @return the result of the comparation of symbol and
  /// kOtherTransition.symbol
  bool operator==(const Transition& kOtherTransition) const;

  /// @brief Overloading of operator <
  /// @param kOtherTransition
  /// @return the result of the comparation of symbol and
  /// kOtherTransition.symbol
  bool operator<(const Transition& kOtherTransition) const;
};
