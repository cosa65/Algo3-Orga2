#include <vector>
//#include "aux/matriz.cpp"
#include <iostream>

using namespace std;

typedef vector<long double> fila;

struct Matriz
{
public:

//generador basico, no se usa
Matriz();

//~Matriz();

//generador que te crea una matriz de una tamaño, no pide vectores
Matriz( int cantfilas, int cantcolumnas);

Matriz( int cantfilas, int cantcolumnas, int semiancho);

//generador que te crea la matriz con los vectores que le pasaste
Matriz( vector< vector<long double> > filas, int cantfilas, int cantcolumnas, vector<long double> indeps, vector<int> pos);

void Definir(long double adefinir, int fila, int columna);

void DefinirB(long double def,int fila);

void DefinirP(int def,int fila);

void intercambiarFilas(int fila1, int fila2);

void restarFilas(int filaRestada, int filaQueResta, long double multFilaARestar);

long double Posicion(int fila, int columna);

long double PosIndep(int fila);

int posSinPivot(int fila);

int Cfilas();

int Ccolumnas();

int TamTotal();

void mostrar();

bool esBanda();

private:

vector< vector<long double> > _array;		//	taria bueno que este fuera un puntero a vector< vector<long double> > asi no se pasa por copia, pero tira 											segmentation fault si lo es...
int _Cfilas;

int _Ccolumnas;

vector<long double> _indeps;

vector<int> _pos;

bool _banda;

int _anchoBanda;

};

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
	_banda=false;
}

Matriz::Matriz( int cantfilas, int cantcolumnas, int semiancho){
	_array.resize(cantfilas); 
	_pos.resize(cantfilas);
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

Matriz::Matriz( vector< vector<long double> > filas, int cantfilas, int cantcolumnas, vector<long double> indeps, vector<int> pos){

	_array = filas;
	_Cfilas = cantfilas;
	_Ccolumnas = cantcolumnas;
	_indeps = indeps;
	_pos = pos;
	_banda=false;
	

}

void Matriz::Definir(long double def,int fila, int columna) {
	if (_banda) {
		_array[fila-1][columna-fila+_anchoBanda]=def;
	} else {
		_array[fila - 1][columna - 1] = def; 
	}

}

void Matriz::DefinirB(long double def,int fila) {

	_indeps[fila - 1] = def; 

}

void Matriz::DefinirP(int def,int fila){
	_pos[fila-1] = def;
}

void Matriz::intercambiarFilas(int fila1, int fila2) { ///Ojo a las permutaciones y ojo a la banda.

	vector<long double> guarda2 = _array[fila2-1];

	_array[fila2-1] = _array[fila1-1];

	_array[fila1-1] = guarda2;

	long double swap=_indeps[fila1-1];
	_indeps[fila1-1]=_indeps[fila2-1];
	_indeps[fila2-1]=swap;

	int swapP = _pos[fila1-1];
	_pos[fila1-1]=_pos[fila2-1];
	_pos[fila2-1]=swapP;
}

void Matriz::restarFilas(int filaRestada, int filaQueResta, long double multFilaARestar){
	if (_banda) {
		for (int i=filaRestada-_anchoBanda; i<=filaRestada+_anchoBanda || i<=_Ccolumnas; i++){
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
		if (columna-fila+_anchoBanda>0 && columna-fila+_anchoBanda<_anchoBanda) {
			return _array[fila-1][columna-fila+_anchoBanda];
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

bool Matriz::esBanda(){
	return _banda;
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

