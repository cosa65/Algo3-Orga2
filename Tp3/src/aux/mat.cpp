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
    	cout << endl << "Error en Matriz::Posicion(), te fuiste del rango de la matriz" << endl;
        return pixel(0,0,0);
    } return _array[fila - 1][columna - 1];
}

uint Matriz::PosColor(int fila, int columna, char color){

    if (fila<1 || fila>_Cfilas || columna<1 || columna>_Ccolumnas) {
    	cout << endl << "Error en Matriz::PosColor(), te fuiste del rango de la matriz" << endl;
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

int Matriz::Cfilas(){
	return _Cfilas;
}

int Matriz::Ccolumnas(){
	return _Ccolumnas;
}

int Matriz::TamTotal(){
	return (_Cfilas * _Ccolumnas);
}

void Matriz::IBilinealRB() {
//Horizontal
	for (int i=1;i<=_Cfilas/2;i++) {
		for (int j=1;j<=_Ccolumnas/2;j++) {
            pixel pr=Posicion(i*2-1,j*2-1); // rojo
            pixel pg=Posicion(i*2-1,j*2); //verde
            //pr.green=(pg.green+Posicion(i*2-1,j*2-2).green)/2;
            //Definir(pr,i*2-1,j*2-1);
            pg.red=(pr.red+Posicion(i*2-1,j*2+1).red)/2;
	        Definir(pg,i*2-1,j*2-1);
		}
		for (int j=1;j<=_Ccolumnas/2;j++) {
            pixel pg=Posicion(i*2,j*2-1); // verde
            pixel pb=Posicion(i*2,j*2); //azul
            pg.blue=(pb.blue+Posicion(i*2,j*2-2).blue)/2;
            Definir(pg,i*2,j*2-1);
            //pb.green=(pg.green+Posicion(i*2,j*2+1).green)/2;
            //Definir(pb,i*2,j*2);
		}
	}
//Vertical
	for (int j=1;j<=_Ccolumnas/2;j++) {
		for (int i=1;i<=_Cfilas/2;i++) {
            pixel pr=Posicion(i*2-1,j*2-1); // rojo
            pixel pg=Posicion(i*2,j*2-1); //verde
            //pr.green=(pg.green+Posicion(i*2-2,j*2-1).green)/2;
            //Definir(pr,i*2-1,j*2-1);
            pg.red=(pr.red+Posicion(i*2+1,j*2-1).red)/2;
            Definir(pg,i*2,j*2-1);
		}
		for (int i=1;i<=_Cfilas/2;i++) {
            pixel pg=Posicion(i*2-1,j*2); // verde
            pixel pb=Posicion(i*2,j*2); //azul
            pg.blue=(pb.blue+Posicion(i*2-2,j*2).blue)/2;
            Definir(pg,i*2-1,j*2);
            //pb.green=(pg.red+Posicion(i*2+1,j*2).green)/2;
            //Definir(pb,i*2,j*2);
		}
	}
}


/*void Matriz::IDireccional() {
}*/

void Matriz::mostrar() {
    for (int i=1;i<=_Cfilas;i++) {
	   for (int j=1;j<=_Ccolumnas;j++){
	   cout << Posicion(i,j).green << "\t";
	   } cout << endl;
    }
}
