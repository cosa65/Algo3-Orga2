#include <vector>
#include "matriz.h"
#include <iostream>

using namespace std;

typedef vector<long double> fila;

Matriz::Matriz(){}

Matriz::Matriz( int cantfilas, int cantcolumnas){
	_array.resize(cantfilas); 
	for (int i = 0; i < cantfilas; i++){

		_array[i].resize(cantcolumnas);
	}
	_Cfilas = cantfilas;
	_Ccolumnas = cantcolumnas;
	_indeps.resize(cantfilas);
	_banda=false;
}

Matriz::Matriz( int cantfilas, int cantcolumnas, int semiancho){
	_array.resize(cantfilas); 
	for (int i = 0; i < cantfilas; i++){

		_array[i].resize(semiancho);
		_pos[i]=i;
	}
	_Cfilas = cantfilas;
	_Ccolumnas = cantcolumnas;
	_anchoBanda=semiancho;
	_indeps.resize(cantfilas);
	_banda=true;
}

Matriz::Matriz(vector< vector<long double> > filas, int cantfilas, int cantcolumnas, vector<long double> indeps){

	_array = filas;
	_Cfilas = cantfilas;
	_Ccolumnas = cantcolumnas;
	_indeps = indeps;
	_banda=false;
	

}

void Matriz::Definir(long double def,int fila, int columna) {
	if (_banda) {
		_array[fila-1][columna-fila+_anchoBanda/2]=def;
	} else {
		_array[fila - 1][columna - 1] = def; 
	}

}

void Matriz::DefinirB(long double def,int fila) {

	_indeps[fila - 1] = def; 

}

void Matriz::intercambiarFilas(int fila1, int fila2) {
	if (!_banda) {
		vector<long double> guarda2 = _array[fila2-1];

		_array[fila2-1] = _array[fila1-1];

		_array[fila1-1] = guarda2;

	} else {
		vector<long double> guarda2(_anchoBanda);
		for (int i=1;i<=_anchoBanda;i++){
			guarda2[i-1]=Posicion(fila1,i);
			if (i<fila1+_anchoBanda && i > fila1-_anchoBanda) {
				Definir(Posicion(fila1,i),fila2,i);
			} if (i<fila2+_anchoBanda && i > fila2-_anchoBanda) {
				Definir(guarda2[i-1],fila2,i);
			}
		}
	} long double swap=_indeps[fila1-1];
	 _indeps[fila1-1]=_indeps[fila2-1];
	 _indeps[fila2-1]=swap;
}

void Matriz::restarFilas(int filaRestada, int filaQueResta, long double multFilaARestar){
	if (_banda) {
		for (int i=filaRestada-_anchoBanda/2; i<=filaRestada+_anchoBanda/2 && i<=_Ccolumnas; i++){
			if (i<1) {i=1;}
			Definir(Posicion(filaRestada,i)-Posicion(filaQueResta,i)* multFilaARestar,filaRestada,i);
		}
	} else {
		for (int i=1; i<=_Ccolumnas; i++){
			Definir(Posicion(filaRestada,i)-Posicion(filaQueResta,i)* multFilaARestar,filaRestada,i);
		}
	}
	_indeps[filaRestada-1] = _indeps[filaRestada-1] - (_indeps[filaQueResta-1]* multFilaARestar);

}

long double Matriz::Posicion(int fila, int columna){
	if (_banda) {
		if (columna-fila+_anchoBanda/2>=0 && columna-fila+_anchoBanda/2<_anchoBanda) {
			return _array[fila-1][columna-fila+_anchoBanda/2];
		} else {
			return 0;
		}
	} else {
		return _array[fila - 1][columna - 1];
	}

}

long double Matriz::PosIndep(int fila){

	return _indeps[fila - 1];

}

int Matriz::posSinPivot(int fila){

	return _pos[fila -1];

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

int Matriz::anchoBanda(){

	return _anchoBanda;

}

void Matriz::mostrar() {
    for (int i=1;i<=_Cfilas;i++) {
	    for (int j=1;j<=_Ccolumnas;j++){
           cout << Posicion(i,j) << "\t";
	    }  cout << "|" << _indeps[i-1] <<endl;
    }
}

