#include"mat.h"


using namespace std;

Matriz::Matriz( int cantfilas, int cantcolumnas){
	_array.resize(cantfilas); 
	for (int i = 0; i < cantfilas; i++){
		_array[i].resize(cantcolumnas);
		_pos[i]=i;
	}
	_Cfilas = cantfilas;
	_Ccolumnas = cantcolumnas;
}

Matriz::Matriz(vector< vector<pixel> > filas, int cantfilas, int cantcolumnas){

	_array = filas;
	_Cfilas = cantfilas;
	_Ccolumnas = cantcolumnas;

}

void Matriz::Definir( def,int fila, int columna) {
	if (_banda) {
		_array[fila-1][columna-fila+_anchoBanda/2]=def;
	} else {
		_array[fila - 1][columna - 1] = def; 
	}

}

uint Matriz::sumarVec(int x, int y, int dirx, int diry){

	uint res;

	int cols = _Ccolumnas;
	int fils = _Cfilas;

	if(dirx == 1 && diry == 0){

		for (int i=0; int i<Ccolumnas; i++){

				

		}

	}

	return 1;

}
