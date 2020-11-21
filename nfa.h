
struct Transition {
  char character;  
  int state = -1;  
};

/// @struct Node
///
/// @brief struct what represents the states of NFA
struct State {
  int state = -1;
  bool accepting;  // If is true is a accepting state of NFA
  bool initial;
  std::set<Transition> transitions;  // Different transitions available the state has
};

/// @class NFA
///
/// @brief Non-Deterministic Finite Automaton class
class NFA {
  private:
    std::set<char> Alphabet;
    std::vector<State> nfa_;

  public:

    /// @brief Initialize all attributes using the following parameters
    /// @param kFile
    NFA(const std::string& kFile, int open_file);

    

    void Write();

    private:
    std::ifstream& CreateNFA (std::ifstream& newNFA);

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