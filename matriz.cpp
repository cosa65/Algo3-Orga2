#include "matriz.h"

Matriz::Matriz(){}

Matriz::Matriz( int tamfilas, int tamcolumnas){

	_array.resize( tamfilas * tamcolumnas );
	_Cfilas = tamcolumnas;
	_Ccolumnas = tamfilas;
}

Matriz::Matriz( vector< vector<double> > filas, int tamfilas, int tamcolumnas){

	_array = filas;	
	_Cfilas = tamcolumnas;
	_Ccolumnas = tamfilas;

}

void Matriz::Definir(double def,int fila, int columna){

	_array[fila - 1][columna - 1] = def;

}

void Matriz::intercambiarFilas(int fila1, int fila2){

	vector<double> guarda2 = _array[fila2-1];

	_array[fila2-1] = _array[fila1-1];

	_array[fila1-1] = guarda2;

}

void Matriz::restarFilas(int filaRestada, int filaQueResta, double multFilaARestar){

	for (int i=0; i< _Ccolumnas; i++){
			
			_array[filaRestada-1][i] = _array[filaRestada-1][i] - (_array[filaQueResta-1][i]* multFilaARestar);

		}

}

double Matriz::Posicion(int fila, int columna){

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

