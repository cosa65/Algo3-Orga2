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
