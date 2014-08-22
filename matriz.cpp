#include <vector>
#include "matriz.h"

Matriz::Matriz(){}

Matriz::Matriz( int cantfilas, int cantcolumnas){
	_array.resize(cantfilas); ///OJO que no es un array plano, es un array de arrays, esto no funciona así
	for (int i = 0; i < cantfilas; i++){

	_array[i].resize(cantcolumnas);

	}
	_Cfilas = cantfilas;
	_Ccolumnas = cantcolumnas;
	_indeps.resize(cantfilas);
	
}

Matriz::Matriz( vector< vector<double> > filas, int cantfilas, int cantcolumnas,vector<double> indeps){

	_array = filas;
	_Cfilas = cantfilas;
	_Ccolumnas = cantcolumnas;
	_indeps = indeps;

}

void Matriz::Definir(double def,int fila, int columna) {

	_array[fila - 1][columna - 1] = def; ///Creo que si el lugar estaba vacío se rompe, si no no sé por qué tira seg. fault.

}

void Matriz::intercambiarFilas(int fila1, int fila2) {

	vector<double> guarda2 = _array[fila2-1];

	_array[fila2-1] = _array[fila1-1];

	_array[fila1-1] = guarda2;

	double swap=_indeps[fila1-1];
	_indeps[fila1-1]=_indeps[fila2-1];
	_indeps[fila2-1]=swap;
}

void Matriz::restarFilas(int filaRestada, int filaQueResta, double multFilaARestar){

	for (int i=0; i< _Ccolumnas; i++){
		_array[filaRestada-1][i] = _array[filaRestada-1][i] - (_array[filaQueResta-1][i]* multFilaARestar);
	}
	_indeps[filaRestada-1] = _indeps[filaRestada-1] - (_indeps[filaQueResta-1]* multFilaARestar);

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
           cout << Posicion(i,j) << " ";
	    }  cout << "|" << _indeps[i-1] <<endl;
    }
}

