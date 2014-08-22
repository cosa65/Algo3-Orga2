#include <vector>
#include "matriz.h"

Matriz::Matriz(){}

Matriz::Matriz( int cantfilas, int cantcolumnas){
	_array.resize(cantfilas); 
	_pos.resize(cantfilas);
	for (int i = 0; i < cantfilas; i++){

		_array[i].resize(cantcolumnas);
		_pos[i]=i;
	}
	_Cfilas = cantfilas;
	_Ccolumnas = cantcolumnas;
	_indeps.resize(cantfilas);
	
}

Matriz::Matriz( vector< vector<double> > filas, int cantfilas, int cantcolumnas, vector<double> indeps, vector<int> pos){

	_array = filas;
	_Cfilas = cantfilas;
	_Ccolumnas = cantcolumnas;
	_indeps = indeps;
	_pos = pos;
	

}

void Matriz::Definir(double def,int fila, int columna) {

	_array[fila - 1][columna - 1] = def; 

}

void Matriz::DefinirB(double def,int fila) {

	_indeps[fila - 1] = def; 

}

void Matriz::DefinirP(int def,int fila){
	_pos[fila-1] = def;
}

void Matriz::intercambiarFilas(int fila1, int fila2) { ///Ojo a las permutaciones.
	vector<double> guarda2 = _array[fila2-1];

	_array[fila2-1] = _array[fila1-1];

	_array[fila1-1] = guarda2;

	double swap=_indeps[fila1-1];
	_indeps[fila1-1]=_indeps[fila2-1];
	_indeps[fila2-1]=swap;
	int swapP = _pos[fila1-1];
	_pos[fila1-1]=_pos[fila2-1];
	_pos[fila2-1]=swapP;
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

double Matriz::PosIndep(int fila){

	return _indeps[fila - 1];

}

void Matriz::DefGrandidad(int grano, int pustula) {
	_h = grano;
	_ancho = pustula;
}

int Matriz::Granularidad() {
	return _h;
}

int Matriz::AnchoParab(){
	return _ancho;
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

