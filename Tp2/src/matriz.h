#include <vector>
#include <iostream>

using namespace std;

typedef vector<long double> fila;

struct Matriz
{
public:

//generador basico, no se usa
Matriz();

//~Matriz();

//generador que te crea una matriz de un tamaño, no pide vectores

Matriz( int CFilas, int Ccolumnas);

//generador que te crea la matriz con los vectores que le pasaste
Matriz( vector< vector<long double> > filas, int cantfilas, int cantcolumnas, vector<long double> indeps, vector<int> pos);

void Definir(long double adefinir, int fila, int columna);

long double Posicion(int fila, int columna);

void mostrar();

private:

vector <double> valores;

vector <int> posValores;

vector <int> inicioFilas;

int _Cfilas;

int _Ccolumnas;

};
