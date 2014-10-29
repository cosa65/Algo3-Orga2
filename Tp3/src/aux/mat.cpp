#include"mat.h"


using namespace std;

void sumarcolor(pixel in, uint &res, char color){
	if(color == 'r'){res += res.red;}
	if(color == 'g'){res += res.green;}
	if(color == 'b'){res += res.blue;}
}

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


