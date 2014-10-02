#include "matriz.h"
#include <vector>
#include <iostream>

using namespace std;

typedef vector<double> fila;

//generador basico, no se usa
//Matriz();

//~Matriz();

//generador que te crea una matriz de un tamaño, no pide vectores

MatrizE::MatrizE(int Cfilas, int Ccolumnas){
	_Cfilas = Cfilas;
	_Ccolumnas = Ccolumnas;
	_inicioFilas.resize(Cfilas);
	for (int i = 0; i<_Cfilas; i++){_inicioFilas[i]=1;}
}

void MatrizE::Definir(double adefinir, int fila, int columna) {

	int size = _valores.size()+1;

	_valores.resize(size);
	_posValores.resize(size);

	for (int i=fila;i<_Cfilas;i++) {
		_inicioFilas[i]++;
	}

	int i =	_inicioFilas[fila-1]-1;
	int j =	_inicioFilas[fila]-1;
	int lugar;
	for (int k=i;k<j;k++) {
		if (_posValores[k]>columna) {
			lugar=k;	
		}
	} 
	for (int k=_valores.size()-1;k>lugar;k--) {
		_valores[k+1]=_valores[k];
		_posValores[k+1]=_posValores[k];		
	} _valores[lugar]=adefinir;
	_posValores[lugar]=columna;
}


double MatrizE::Posicion(int fila, int columna) {

	int i =	_posValores[_inicioFilas[fila-1]-1];

	int j =	_posValores[_inicioFilas[fila]-1];

	for (int k=i;k<j;k++) {
		if (_posValores[k]==columna) {
			return _valores[k];
		}
	} return 0;
}

int MatrizE::Cfilas(){
	return _Cfilas;
}

void MatrizE::mostrar(){
	for (int i=0;i<_Ccolumnas;i++) {
		for (int j=0;j<_Cfilas;j++) {
			cout << Posicion(i,j) << " ";
		} cout << endl;
	}
}
