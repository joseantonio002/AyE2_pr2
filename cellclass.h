#ifndef CELL
#define CELL

#include <iostream>
#include <array>
#include <cstdlib>
class Grid; //forward declaration, no hacer include ya que se llamarian una clase a la otra
class Stateb;
using namespace std;
typedef int State;
typedef std::array<int, 2> Position;

class Cell {
 public:
  Cell();
  void updateState(); //método para actualizar el estado de una cécula (utiliza neighbords en su interior)
  int neighbords(const Grid& grid); //método para hallar la vecindad (número de células vecinas vivas)
  char get_state() const;
  void set_state(Stateb* x);
  Position get_position() const;
  void set_position(Position pos);
  friend std::ostream& operator<<(std::ostream& stream, const Cell& cell);
 private:
  Stateb* state;
  Stateb* nextstate;
  Position position;
};




#endif
