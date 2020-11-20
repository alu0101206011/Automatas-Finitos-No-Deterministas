/// @struct Transitions
///
/// @brief a struct with what each node needs to make a transition
struct Transition {
  char character;  // what the state needs to transition
  int state = -1;  // will transit to this state
};

/// @struct Node
///
/// @brief struct what represents the states of NFA
struct State {
  int state = -1;
  bool accepting;  // If is true is a accepting state of NFA
  bool initial;
  std::vector<Transition> transitions;  // Different transitions available the state has
};

/// @class NFA
///
/// @brief Non-Deterministic Finite Automaton class
class NFA {
  private:
    std::vector<State> nfa_;

  public:
    NFA(const std::string& file);



    void Write();

};

/*
forall (q ∈T) do
begin
push(q)
epsilon − clausura(T) := T;
while (not pila vacia) do
begin
p := pop();
for (cada estado u con una arista desde p a u etiquetada con epsilon) do
if u ∈/ epsilon − clausura(T) then
begin
epsilon − clausura(T) := epsilon − clausura(T) ∪ {u}
push(u);
end;
end;

*/