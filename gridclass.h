#ifndef GRID_
#define GRID_

#include <iostream>
#include <vector>
#include "cellclass.h"
#include "states.h"
using namespace std;


class Grid {
  public:
    Grid(int row, int colum);
    const Cell& getCell(Position pos) const;
    void show() const;
    void generatealive(vector<Position> v, vector<int> states);
    void nextgen();
  private:
    Cell** grid;
    int nrow;
    int ncol;
    int nrowo; //número de filas y columnas originales, sin sumarle 2
    int ncolo;
};



#endif
