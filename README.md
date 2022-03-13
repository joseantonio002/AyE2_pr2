# Práctica 2 Algoritmos y estructuras de datos avanzadas
## Cómo funciona la práctica:
Tenemos tres clases, grid cell y states; La clase grid contiene una matriz 
de células creada dinámicamente, a la tabla se accede desde la posición (1, 1) ya
que la primera y última fila son "paredes". 
La clase state tiene una clase base con métodos virtuales y diferentes clases hijas 
que son los estados que toman las células, si queremos añadir nuevos estados solo tenemos
que añadir una nueva clase y definir sus métodos neighbords que calcula lo que hace falta
para un cambio de estado y nexstate que devuelve un nuevo estado dependiendo de los valores anteriores, esto se hace así ya que si en el mismo neighbord devolvieramos el estado a la hora
de recorrer grid se sobreescribiría antes de hacer los cambios a sus células vecinas.




[funciones virtuales](https://www.geeksforgeeks.org/virtual-function-cpp/)
[Explicación poliformismo](https://www.codingame.com/playgrounds/51214/manejo-dinamico-de-memoria-y-polimorfismo-practica-4/polimorfismo)
Mas enlaces:
https://stackoverflow.com/questions/3065154/undefined-reference-to-vtable
https://www.geeksforgeeks.org/virtual-destructor/
