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

class StateEgg : public Stateb {


};

class StateLarva : public Stateb {




};

class StatePupa : public Stateb {




};


class StateDead : public Stateb {





};


#endif