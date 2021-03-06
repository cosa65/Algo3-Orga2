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
Matriz( int cantfilas, int cantcolumnas);

//generador que te crea la matriz con los vectores que le pasaste
Matriz( vector< vector<double> > filas, int cantfilas, int cantcolumnas);

void Definir(double adefinir, int fila, int columna);

double Posicion(int fila, int columna);

int Cfilas();

int Ccolumnas();

int TamTotal();

void mostrar();

vector<double> Producto (vector<double> x);

private:

vector< vector<double> > _array;

int _Cfilas;

int _Ccolumnas;

};
