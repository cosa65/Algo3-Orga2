#include "matriz.h"

Matriz::Matriz(){}

Matriz::Matriz( int tamfilas, int tamcolumnas){

	_array.resize( tamfilas * tamcolumnas );

}

Matriz::Matriz( vector< vector<int> > filas, int tamfilas, int tamcolumnas){

	_array = filas;	

}

int Matriz::Posicion(int fila, int columna){

	return _array[fila - 1][columna - 1];

}

void Matriz::Definir(int def,int fila, int columna){

	_array[fila - 1][columna - 1] = def;

}
