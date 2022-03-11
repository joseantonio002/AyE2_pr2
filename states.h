#ifndef STATES
#define STATES

#include "gridclass.h"
#include "cellclass.h"

class Stateb {
 public:
  virtual Stateb* Stateb::nextState()=0;
  virtual char Stateb::getState() const =0;
  virtual void Stateb::neighbords(int i, int j, const Grid& grid)=0; 

};

class StateDead : public Stateb {
 public:
  Stateb* StateDead::nextState();
  char StateDead::getState() const {return '-';};
  void StateDead::neighbords(int i, int j, const Grid& grid); 

};


class StateEgg : public Stateb {
 public:
  Stateb* StateEgg::nextState();
  char StateEgg::getState() const {return 'e';};
  void StateEgg::neighbords(int i, int j, const Grid& grid); 

};

class StateLarva : public Stateb {
 public:
  Stateb* StateLarva::nextState();
  char StateLarva::getState() const {return 'l';};
  void StateLarva::neighbords(int i, int j, const Grid& grid); 



};

class StatePupa : public Stateb {
 public:
  Stateb* StatePupa::nextState();
  char StatePupa::getState() const {return 'p';};
  void StatePupa::neighbords(int i, int j, const Grid& grid); 


};

class StateAdult : public Stateb {
 public:
  Stateb* StateAdult::nextState();
  char StateAdult::getState() const {return 'a';};
  void StateAdult::neighbords(int i, int j, const Grid& grid); 


};



#endif
