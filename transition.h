/// @class Transitions
///
/// @brief a class with what each node needs to make a transition

class Transition {
    public: 
        char symbol; // what the state needs to transition
        int nextState; // will transit to this state
        
        // Default constructor
        Transition (void);
        
        // Constructor al que se le pasa como parámetro el ID del siguiente estado, y el símbolo.
        Transition (int nextState, char userSymbol);
        
        // Constructor de copia al que se le pasa la nueva transiición.
        Transition (const Transition& kNewTransition);
        
        // Destructor de la clase.
        ~Transition (void);
        

        Transition& operator= (const Transition& kOtherTransition);
        
        // Sobrecarga del operador ==.
        bool operator== (const Transition& kOtherTransition) const;
        
        // Sobrecarga del operador <.
        bool operator< (const Transition& kOtherTransition) const;
};