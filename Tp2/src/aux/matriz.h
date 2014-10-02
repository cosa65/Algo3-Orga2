#include <vector>
#include <iostream>

using namespace std;

typedef vector<double> fila;

struct Matriz
{
public:

//generador basico, no se usa
Matriz();

//~Matriz();

//generador que te crea una matriz de un tamaño, no pide vectores

Matriz( int CFilas, int Ccolumnas);

//generador que te crea la matriz con los vectores que le pasaste
Matriz( vector< vector<double> > filas, int cantfilas, int cantcolumnas, vector<double> indeps, vector<int> pos);

void Definir(double adefinir, int fila, int columna);

double Posicion(int fila, int columna);

int Cfilas();

void mostrar();

private:

vector <double> _valores;

vector <int> _posValores;

vector <int> _inicioFilas;

int _Cfilas;

int _Ccolumnas;

};
