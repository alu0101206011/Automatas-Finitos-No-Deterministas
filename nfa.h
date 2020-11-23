/// @class NFA
///
/// @brief Non-Deterministic Finite Automaton class
///
/// @author Anabel Díaz Labrador <alu0101206011@ull.edu.es> 
/// @date 20 Nov 2020

#include "state.h"

class NFA {
  private:
    std::set<char> alphabet_;
    std::set<State> nfa_;
    int initial_state_;
    std::set<State> accepted_states_;
  public:
    /// @brief Initialize all attributes using the following parameters
    /// @param kFile
    NFA(const std::string& kFile, int open_file);

    /// @brief Returns state given its ID number
    /// @param identifier
    State GetState(int identifier) const;

    /// @brief Returns true if the string belongs to the alphabet
    /// @param kAnalyzeWord    
    bool BelongToAlphabet(const std::string& kAnalyzeWord);

    /// @brief 
    /// @param kAnalyzeWord
    /// @param current_id
    bool AnalyzeString(std::string& kAnalyzeWord, int current_id);

    /// @brief Write the NFA 
    void Write();

    private:
    /// @brief
    /// @param newNFA
    std::ifstream& CreateNFA(std::ifstream& newNFA);
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