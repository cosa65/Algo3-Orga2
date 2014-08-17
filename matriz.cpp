#include "matriz.h"

Matriz::Matriz(){}

Matriz::Matriz( vector< vector<int> > filas, int tamfilas, int tamcolumnas){

	_array = filas;	

}

int Matriz::Posicion(int fila, int columna){

	return _array[fila][columna];

}
