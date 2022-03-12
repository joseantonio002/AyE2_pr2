#ifndef STATES
#define STATES

#include "gridclass.h"
#include "cellclass.h"

class Stateb {
 public:
  virtual Stateb* nextState()=0;
  virtual char getState() const =0;
  virtual void neighbords(Position pos, const Grid& grid)=0; 
  void vecinity(Position& np, const Position& pos); //usar cuando miramos la vencidad en el bucle for
  virtual ~Stateb() {}
};

class StateWall : public Stateb {
 public:
  Stateb* nextState(){Stateb* x = new StateWall; return x;}
  char getState() const {return '+';}
  void neighbords(Position pos, const Grid& grid) {}
  ~StateWall() {}
 
};

class StateDead : public Stateb {
 public:
  Stateb* nextState();
  char getState() const {return '-';}
  void neighbords(Position pos, const Grid& grid);
  ~StateDead() {}
 private:
  int nadults;
 
};


class StateEgg : public Stateb {
 public:
  Stateb* nextState();
  char getState() const {return 'e';}
  void neighbords(Position pos, const Grid& grid);
  ~StateEgg() {}
 private:
  int nlarva;
  int negg;
};

class StateLarva : public Stateb {
 public:
  Stateb* nextState(){Stateb* x = new StateEgg; return x;}
  char getState() const {return 'l';}
  void neighbords(Position pos, const Grid& grid){cout << "text";}
  ~StateLarva() {}
 private:
  int nlarva;
  int eggpupad;
};

class StatePupa : public Stateb {
 public:
  Stateb* nextState();
  char getState() const {return 'p';}
  void neighbords(Position pos, const Grid& grid);
  ~StatePupa() {}
 private:
  int nlarva;
  int other;
};

class StateAdult : public Stateb {
 public:
  Stateb* nextState();
  char getState() const {return 'a';}
  void neighbords(Position pos, const Grid& grid);
  ~StateAdult() {}
 private:
  bool isadult;
};

#endif
