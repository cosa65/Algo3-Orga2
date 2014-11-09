#include"mat.h"


using namespace std;

pixel::pixel(){red=0;green=0;blue=0;}
pixel::pixel(uint r, uint g, uint b){red=r;green=g;blue=b;}

Matriz::Matriz(){}

Matriz::Matriz( int cantfilas, int cantcolumnas){
	_array.resize(cantfilas); 
	for (int i = 0; i < cantfilas; i++){
		_array[i].resize(cantcolumnas);
	}
	_Cfilas = cantfilas;
	_Ccolumnas = cantcolumnas;
}

Matriz::Matriz(vector< vector<pixel> > filas, int cantfilas, int cantcolumnas){
	_array = filas;
	_Cfilas = cantfilas;
	_Ccolumnas = cantcolumnas;
}

void Matriz::Definir(pixel def,int fila, int columna) {
	_array[fila - 1][columna - 1] = def; 
}

void Matriz::DefColor(uint def,int fila, int columna, char color) {

    if(color == 'r'){
        _array[fila - 1][columna - 1].red = def;
    } else if(color == 'g'){
        _array[fila - 1][columna - 1].green = def;
    } else if(color == 'b'){
        _array[fila - 1][columna - 1].blue = def;
    }
}


pixel Matriz::Posicion(int fila, int columna){
    if (fila<1 || fila>_Cfilas || columna<1 || columna>_Ccolumnas) {
    	cout << "Error en Matriz::Posicion(), te fuiste del rango de la matriz" << endl;
        return pixel(0,0,0);
    } return _array[fila - 1][columna - 1];
}

uint Matriz::PosColor(int fila, int columna, char color){

    if (fila<1 || fila>_Cfilas || columna<1 || columna>_Ccolumnas) {
    	cout << "Error en Matriz::PosColor(), te fuiste del rango de la matriz" << endl;
        return 0;
    }

    if (color == 'r'){
    	return _array[fila - 1][columna - 1].red;
    } else if (color == 'g'){
    	return _array[fila - 1][columna - 1].green;
    } else if (color == 'b'){
    	return _array[fila - 1][columna - 1].blue;
    }
    return 0; //asi no jode el warning
}

uint Matriz::sumaDePoses(int fila, int columna, char queColorNo){

    if (fila<1 || fila>_Cfilas || columna<1 || columna>_Ccolumnas) {
        cout << "Error en Matriz::PosColor(), te fuiste del rango de la matriz" << endl;
        return 0;
    }

    switch (queColorNo){
        CASE('r'):
            return _array[fila-1][columna-1].green + _array[fila-1][columna-1].blue;
            break;
        CASE('g'):
            return _array[fila-1][columna-1].red + _array[fila-1][columna-1].blue;
            break;
        CASE('b'):
            return _array[fila-1][columna-1].red + _array[fila-1][columna-1].green;
            break;        
    }
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
	        //cout << '(' << i << ',' << j << "):(" << Posicion(i,j).red << ' ' << Posicion(i,j).green << ' ' << Posicion(i,j).blue << ')' << endl;
            cout << Posicion(i,j).green << '\t';
	    } cout << endl;
    } 
}
