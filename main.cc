#include <iostream>
#include "cellclass.h"
#include "gridclass.h"
#include <vector>
#include <string>
#include <sstream>
using namespace std;



int main() {
  int nfilas, ncolumnas, nturnos;
  cout << "Introduce las filas de la matriz" << endl;
  cin >> nfilas;
  cout << "Introduce las columnas de la matriz" << endl;
  cin >> ncolumnas;
  cout << "Introduce los turnos del juego" << endl;
  cin >> nturnos;
  if(nfilas < 0 || ncolumnas < 0 || nturnos < 0) {
    cout << "No se permiten negativos" << endl;
    return 1;
  }
  cin.ignore(); //Para que no detecte el enter como el getline del while
  Grid grid(nfilas, ncolumnas);
  cout << "Introduce posiciones de células vivas (poscionx espacio posiciony) empezando en 1, pulsa ENTER cuando termines" << endl;
  int x,y;
  Position p;
  vector<Position> ps;
  string s;
  while (std::getline(cin, s) && !s.empty()) {
    std::stringstream ss(s);
    ss >> x >> y;
    if (!ss || x < 0 || y < 0)
      cout << "Par invalido" << endl;
    else 
      p[0] = x; p[1] = y;
      ps.push_back(p);
  }
  grid.generatealive(ps);
  cout << "Turno 0: " << endl;
  grid.show();
  cout << endl;
  for(int i = 1; i <= nturnos; i++) {
    cout << "Turno: " << i << endl;
    grid.nextgen();
    grid.show();
    cout << endl;
  }

  return 0;
}
