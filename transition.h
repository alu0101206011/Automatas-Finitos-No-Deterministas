/// @class Transitions
///
/// @brief a class with what each node needs to make a transition
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
    Transition& operator=(const Transition& kOtherTransition);

    /// @brief Overloading of operator ==
    /// @param kOtherTransition  
    bool operator==(const Transition& kOtherTransition) const;

    /// @brief Overloading of operator <
    /// @param kOtherTransition  
    bool operator<(const Transition& kOtherTransition) const;
};
