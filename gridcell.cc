#include "cellclass.h"
#include "gridclass.h"
#include "states.h"
//En el mismo fichero ya que ambas clases son dependientes la una de la otra
//------------------------------------------------------------------
/******** VOY A PONER "NC" EN LAS FUNCIONES QUE NO CAMBIEN******/

Grid::Grid(int row, int colum) { //NC
  nrowo = row;
  ncolo = colum;
  row = 2 + row;  //Paredes
  colum = 2 + colum; //Paredes
  grid = new Cell*[row];
  for(int i = 0; i < row; i++) {
    grid[i] = new Cell[colum];
  }
  Position p;
  for(int i = 0; i < row; i++) {
    p[0] = i;
    for(int j = 0; j < colum; j++) {
      p[1] = j;
      grid[i][j].set_position(p);
      /*if(i == 0 || j == 0 || i == row-1 || j == colum-1) { //células pared nunca se llegan a apuntar
        grid[i][j].set_state();
      }*/ //simplemente ignoramos las células pared a la hora de generatealive, se quedan sin estado
    }
  }
  nrow = row;
  ncol = colum;
}

void Grid::show() const { 
  for(int i = 1; i <= nrowo; i++) {
    for(int j = 1; j <= ncolo; j++) {
      cout << grid[i][j];
    }
    cout << endl;
  }
}

const Cell& Grid::getCell(Position pos) const { //NC
  return grid[pos[0]][pos[1]];
}

void Grid::generatealive(vector<Position> v, vector<int> states) { //susceptible a cambio preguntar profe pregunta del bloc de notas
  Position p;
  Stateb* base;
  for(int i = 0; i < states.size(); i++) {
    p = v[i];
    switch (states[i]) {
    case 1:
      base = new StateEgg;
      break;
    case 2:
      base = new StateLarva;
      break;
    case 3:
      base = new StatePupa;
      break; 
    case 4:
      base = new StateAdult;
      break; 
    default:
      cerr << "Estado no válido" << endl;
      exit(EXIT_FAILURE);
      break;
    }
  }
  grid[p[0]][p[1]].set_state(base);
}

void Grid::nextgen() {
  for(int i = 1; i <= nrowo; i++) { //recorre solo las celulas del interior no las pared
    for(int j = 1; j <= ncolo; j++) {
        grid[i][j].neighbords(*this);
      }
    }
  for(int i = 1; i <= nrowo; i++) { 
    for(int j = 1; j <= ncolo; j++) {
        grid[i][j].updateState();
    }
  }
  show();
}
//---------------------------------------------------------------------------------------------------------------
#include "cellclass.h"

Cell::Cell() { 
  position[0] = -1;
  position[1] = -1;
  state = new StateDead;
}

void Cell::set_position(Position pos) { //NC
  position = pos;
}

Position Cell::get_position() const{ //NC
  return position;
}

void Cell::set_state(Stateb* x) {
  state = x;
}

Stateb* Cell::get_state() const {
  return state;
}

//¿sobrecargar operador en cada clase?
std::ostream& operator<<(std::ostream& stream, const Cell& cell) {
  stream << cell.state->getState();
  return stream;
}

int Cell::neighbords(const Grid& grid) { //devuelve células vecinas vivas
  return -1;
}

void Cell::updateState() {
  state = nextstate;
  delete nextstate;
}
