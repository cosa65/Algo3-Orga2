#include <vector>
#include "matriz.h"
#include <iostream>

using namespace std;

typedef vector<double> fila;

Matriz::Matriz(){}

Matriz::Matriz( int cantfilas, int cantcolumnas){
	_array.resize(cantfilas); 
	for (int i = 0; i < cantfilas; i++){
		_array[i].resize(cantcolumnas);
	}
	_Cfilas = cantfilas;
	_Ccolumnas = cantcolumnas;
}

Matriz::Matriz(vector< vector<double> > filas, int cantfilas, int cantcolumnas){
	_array = filas;
	_Cfilas = cantfilas;
	_Ccolumnas = cantcolumnas;
}

void Matriz::Definir(double def,int fila, int columna) {
	_array[fila - 1][columna - 1] = def; 
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

void Matriz::mostrar() {
	for (int i=1;i<=_Cfilas;i++) {
		for (int j=1;j<=_Ccolumnas;j++){
           		cout << Posicion(i,j) << "\t";
		} cout << endl;
	}
}
