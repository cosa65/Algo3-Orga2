#include "matriz.h"

Matriz::Matriz(){}

Matriz::Matriz( int tamfilas, int tamcolumnas){

	_array.resize( tamfilas * tamcolumnas );
	_Cfilas = tamcolumnas;
	_Ccolumnas = tamfilas;
}

Matriz::Matriz( vector< vector<int> > filas, int tamfilas, int tamcolumnas){

	_array = filas;	
	_Cfilas = tamcolumnas;
	_Ccolumnas = tamfilas;

}

void Matriz::Definir(int def,int fila, int columna){

	_array[fila - 1][columna - 1] = def;

}

int Matriz::Posicion(int fila, int columna){

	return _array[fila - 1][columna - 1];

}

int Matriz::Cfilas(){
	
	
	return _Cfilas;

}

int Matriz::Ccolumnas(){

	return _Ccolumnas;

}

int Matriz::TamTotal(){

	return (_Cfilas * _Ccolumnas);

}

