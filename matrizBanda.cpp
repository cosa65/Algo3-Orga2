#include "matrizBanda.h"
#include <vector>

MatrizB::MatrizB(){}

MatrizB::MatrizB(int cantfilas, int cantcolumnasA, int cantcolumnasD){
	_Cfilas = cantfilas;
	_CcolumnasA = cantcolumnasA;
	_CcolumnasD = cantcolumnasD;
}

MatrizB::MatrizB( vector< vector<double> > filas, int cantfilas, int cantcolumnasA, int cantcolumnasD){
	_Cfilas = cantfilas;
	_CcolumnasA = cantcolumnasA;
	_CcolumnasD = cantcolumnasD;
	_array = filas;	
}


void MatrizB::Definir(double def,int fila, int columna){
	_array[fila-1][columna-fila+_CcolumnasA]=def;
}

/*void MatrizB::intercambiarFilas(int fila1, int fila2){

	vector<double> guarda2 = _array[fila2-1];
	_array[fila2-1] = _array[fila1-1];
	_array[fila1-1] = guarda2;

}

void MatrizB::restarFilas(int filaRestada, int filaQueResta, double multFilaARestar){

	for (int i=0; i< _Ccolumnas; i++){
			
			_array[filaRestada-1][i] = _array[filaRestada-1][i] - (_array[filaQueResta-1][i]* multFilaARestar);

		}

}*/

double MatrizB::Posicion(int fila, int columna){

	return _array[fila-1][columna-fila+_CcolumnasA];

}

int MatrizB::Cfilas(){	
	return _Cfilas;
}

int MatrizB::Ccolumnas(){
	return _CcolumnasA+_CcolumnasD;
}

int MatrizB::TamTotal(){
	return (_Cfilas*Ccolumnas());
}

