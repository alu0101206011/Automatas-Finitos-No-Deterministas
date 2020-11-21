/// @class State
///
/// @brief This class works with states and attributes 
/// behavior.
///
/// @author Anabel Díaz Labrador <alu0101206011@ull.edu.es> 
/// @date 20 Nov 2020

class State {
  public:
    int state_name_;
    std::set<Transition> transitions_;

    State(void);

    State(const int& kStateName);

    /// @brief Copy constructor
    /// @param kState
    State(const State& kState);

    /// Default destructor
    ~State (void);

    /// @brief remove all the values of the transition set 
    /// and sets the state_name_ back to its default value 
    void Clear(void);

    void SetNextState(int next_state_name, char symbol);

    std::set<int> SetNextState(char symbol) const;

    bool hasEpsTransitions(void);

    int NumberOfTransitions(void) const;

    std::vector<int> getEpsTransitions(void) const;

    bool symbolIsUsed (char symbol) const;

    friend std::ostream& operator<<(std::ostream& os, const State& kOtherState);

    State& operator=(const State& kOtherState);

    bool operator==(const State& kOtherState) const;

    bool operator<(const State& kOtherState) const;
};