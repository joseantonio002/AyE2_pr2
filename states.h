#ifndef STATES
#define STATES

#include "gridclass.h"
#include "cellclass.h"

class Stateb {
 public:
  virtual Stateb* nextState()=0;
  virtual char getState() const =0;
  virtual void neighbords(int i, int j, const Grid& grid)=0; 
  virtual ~Stateb() {}
};

class StateDead : public Stateb {
 public:
  Stateb* nextState(){Stateb* x = new StateDead; return x;}
  char getState() const {return '-';}
  void neighbords(int i, int j, const Grid& grid){cout << "text";}
  ~StateDead() {}
};


class StateEgg : public Stateb {
 public:
  Stateb* nextState(){Stateb* x = new StateEgg; return x;}
  char getState() const {return 'e';}
  void neighbords(int i, int j, const Grid& grid){cout << "text";}
  ~StateEgg() {}
};

class StateLarva : public Stateb {
 public:
  Stateb* nextState(){Stateb* x = new StateEgg; return x;}
  char getState() const {return 'l';}
  void neighbords(int i, int j, const Grid& grid){cout << "text";}
  ~StateLarva() {}
};

class StatePupa : public Stateb {
 public:
  Stateb* nextState(){Stateb* x = new StateEgg; return x;}
  char getState() const {return 'p';}
  void neighbords(int i, int j, const Grid& grid){cout << "text";}
  ~StatePupa() {}
};

class StateAdult : public Stateb {
 public:
  Stateb* nextState(){Stateb* x = new StateEgg; return x;}
  char getState() const {return 'a';}
  void neighbords(int i, int j, const Grid& grid){cout << "text";}
  ~StateAdult() {}
};

#endif
