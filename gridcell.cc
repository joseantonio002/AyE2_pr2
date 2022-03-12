#include "cellclass.h"
#include "gridclass.h"
#include "states.h"
//En el mismo fichero ya que ambas clases son dependientes la una de la otra
//------------------------------------------------------------------
/******** VOY A PONER "NC" EN LAS FUNCIONES QUE NO CAMBIEN******/


//-----------------------------------------------------#include states
void Stateb::vecinity(Position& np, const Position& pos) {
  if(np[1] == pos[1]+1) { //llego al final de una fila, salto a la siguiente
    np = {np[0]+1, np[1]-2};
    return;
  }
  np = {np[0], np[1]+1};
  if(np == pos) {
    np = {np[0], np[1]+1};
  }
}

//STATEDEAD
void StateDead::neighbords(Position pos, const Grid& grid) {
  Position np = {pos[0]-1, pos[1]-1};
  nadults = 0;
  for(int i = 0; i < 8; i++) {
    if(grid.getCell(np).get_state() == 'a') {
      nadults += 1;
    }
    vecinity(np, pos);
  }
}

Stateb* StateDead::nextState() {
  Stateb* p = new StateDead;
  if(nadults >= 2) {
    p = new StateEgg;
  }
  return p;
}

//----------
//STATEEGG
void StateEgg::neighbords(Position pos, const Grid& grid) {
  Position np = {pos[0]-1, pos[1]-1};
  negg = 0; nlarva = 0;
  for(int i = 0; i < 8; i++) {
    if(grid.getCell(np).get_state() == 'l') {
      nlarva += 1;
    }
    else if(grid.getCell(np).get_state() == 'e') {
      negg += 1;
    }
    vecinity(np, pos);
  }
}

Stateb* StateEgg::nextState() {
  Stateb* p = new StateLarva;
  if(nlarva > negg) {
    p = new StateDead;
  }
  return p;
}
//-----------
//STATELARVA
void StateLarva::neighbords(Position pos, const Grid& grid) {
  Position np = {pos[0]-1, pos[1]-1};
  eggpupad = 0; nlarva = 0;
  for(int i = 0; i < 8; i++) {
    if(grid.getCell(np).get_state() == 'l') {
      nlarva += 1;
    }
    else if(grid.getCell(np).get_state() == 'e' || grid.getCell(np).get_state() == 'p' || grid.getCell(np).get_state() == 'a') {
      eggpupad += 1;
    }
    vecinity(np, pos);
  }
}

Stateb* StateLarva::nextState() {
  Stateb* p = new StatePupa;
  if(nlarva > eggpupad) {
    p = new StateDead;
  }
  return p;
}
//-----------
//STATEPUPA
void StatePupa::neighbords(Position pos, const Grid& grid) {
  Position np = {pos[0]-1, pos[1]-1};
  other = 0; nlarva = 0;
  for(int i = 0; i < 8; i++) {
    if(grid.getCell(np).get_state() == 'l') {
      nlarva += 1;
    }
    else{
      other += 1;
    }
    vecinity(np, pos);
  }
}

Stateb* StatePupa::nextState() {
  Stateb* p = new StateAdult;
  if(nlarva > other) {
    p = new StateDead;
  }
  return p;
}
//-----------
//STATEADULT
void StateAdult::neighbords(Position pos, const Grid& grid) {
  Position np = {pos[0]-1, pos[1]-1};
  isadult = false;
  for(int i = 0; i < 8; i++) {
    if(grid.getCell(np).get_state() == 'a') {
      isadult = true;
    }
    vecinity(np, pos);
  }
}

Stateb* StateAdult::nextState() {
  Stateb* p = new StateDead;
  if(isadult) {
    p = new StateEgg;
  }
  return p;
}
//-----------
//--------------------------------------------------------------------





//--------------------------------------------#include grid
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
        grid[i][j].set_state(new StateWall);
      }
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

void Grid::generatealive(vector<Position> v, vector<char> states) { //susceptible a cambio preguntar profe pregunta del bloc de notas
  Position p;
  Stateb* base;
  for(int i = 0; i < states.size(); i++) {
    p = v[i];
    switch (states[i]) {
    case 'e':
      base = new StateEgg;
      break;
    case 'l':
      base = new StateLarva;
      break;
    case 'p':
      base = new StatePupa;
      break; 
    case 'a':
      base = new StateAdult;
      break; 
    default:
      cerr << "Estado no válido" << endl;
      exit(EXIT_FAILURE);
      break;
    }
    grid[p[0]][p[1]].set_state(base);
  }
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





//-------------------------------------------#include cell
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

char Cell::get_state() const {
  return state->getState();
}

std::ostream& operator<<(std::ostream& stream, const Cell& cell) {
  stream << cell.state->getState();
  return stream;
}

void Cell::neighbords(const Grid& grid) { //devuelve células vecinas vivas
  state->neighbords(position, grid);
  nextstate = state->nextState();
}

void Cell::updateState() {
  state = nextstate;
  nextstate = NULL;
}
//----------------------------------------------------------------------------
