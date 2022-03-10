#include "cellclass.h"
#include "gridclass.h"
//En el mismo fichero ya que ambas clases son dependientes la una de la otra
//------------------------------------------------------------------
#include "gridclass.h"
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
      if(i == 0 || j == 0 || i == row-1 || j == colum-1) { //células pared
        grid[i][j].set_state(-1);
      }
    }
  }
  nrow = row;
  ncol = colum;
}

void Grid::show() const { //NC
  for(int i = 0; i < nrow; i++) {
    for(int j = 0; j < ncol; j++) {
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
  for(int i = 0; i < states.size(); i++) {
    p = v[i];
    grid[p[0]][p[1]].set_state(states[i]); //suponiendo que setstate transforma el número en puntero a estado correspondiente
  }
}

void Grid::nextgen() {
  vector<Position> vectorpos;
  Position ps;
  int neighbords;
  for(int i = 1; i <= nrowo; i++) { //recorre solo las celulas del interior no las pared
    for(int j = 1; j <= ncolo; j++) {
      ps = {i,j};
      neighbords = grid[i][j].neighbords(*this);
      if(grid[i][j].get_state() == 0) { //comprobar si cambia de estado y si cambia guardar posición
        if(neighbords == 3) {
          vectorpos.push_back(ps);
        }
      }
      else {
        if(neighbords != 2 && neighbords != 3) {
          vectorpos.push_back(ps);
        }
      }
    }
  }

  for(Position p : vectorpos) {
    grid[p[0]][p[1]].updateState();
  }
}
//---------------------------------------------------------------------------------------------------------------
#include "cellclass.h"


Cell::Cell() { 
  position[0] = -1;
  position[1] = -1;
  state = 0;
}

void Cell::set_position(Position pos) { //NC
    position = pos;
}

Position Cell::get_position() const{ //NC
  return position;
}

void Cell::set_state(State x) {
  state = x;
}

State Cell::get_state() const {
  return state;
}

std::ostream& operator<<(std::ostream& stream, const Cell& cell) {
  if(cell.state == 0) stream << '-';
  else if(cell.state == -1) stream << '+'; //celulas muro
  else stream << 'x';
  return stream;
}

int Cell::neighbords(const Grid& grid) { //devuelve células vecinas vivas
  if(state == -1) {
    cerr << "Célula no válida" << endl;
    exit(EXIT_FAILURE);
  }

  int nalive = 0;
  Position ps = {position[0]-1, position[1]-1};
  for(int i = 0; i < 3; i++) { //comprueba fila de arriba de la célula
    if(grid.getCell(ps).get_state() == 1) nalive += 1;
    ps = {ps[0], ps[1]+1};
  }

  ps = {ps[0]+1, ps[1]-3}; //comprueba misma fila de la célula
  if(grid.getCell(ps).get_state() == 1) nalive += 1;
  ps = {ps[0], ps[1]+2};
  if(grid.getCell(ps).get_state() == 1) nalive += 1;

  ps = {ps[0]+1, ps[1]-2};
  for(int i = 0; i < 3; i++) { //comprueba fila de abajo
    if(grid.getCell(ps).get_state() == 1) nalive += 1;
    ps = {ps[0], ps[1]+1};
  }

  return nalive;
}
void Cell::updateState() {
    if(state == 0) state = 1;
    else state = 0;
}
