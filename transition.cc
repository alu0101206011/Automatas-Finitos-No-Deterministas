//#include <cstdio>
//#include <iostream>
//#include <set>
  
#include "transition.h"

// Default constructor
Transition:: Transition (void): symbol(), nextState(){}
    

Transition::Transition (int nextState, char userSymbol): symbol(userSymbol), 
nextState(nextState) {}

// Default destructor   
Transition::~Transition (void) {
  symbol = '0';
  nextState = -1;
}

// Copy constructor
Transition::Transition (const Transition& kNewTransition) {
  symbol = kNewTransition.symbol;
  nextState = kNewTransition.nextState;
}

// Overloading of operator =
Transition& Transition:: operator= (const Transition& kOtherTransition) {
  symbol = kOtherTransition.symbol;
  nextState = kOtherTransition.nextState;
  return *this;
}

// Overloading of operator ==       
bool Transition:: operator== (const Transition& kOtherTransition) const {
  if (symbol == kOtherTransition.symbol) 
    if (nextState == kOtherTransition.nextState)
      return true;
  return false;
}

// Overloading of operator <    
bool Transition:: operator< (const Transition& kOtherTransition) const {
  if ((symbol <= kOtherTransition.symbol)) 
    return true;
  return false;
}