	#include <vector>
#include <iostream>

using namespace std;

typedef vector<double> fila;

struct MatrizE
{
public:

//generador basico, no se usa
MatrizE();

//~Matriz();

//generador que te crea una matriz de un tamaño, no pide vectores

MatrizE( int CFilas, int Ccolumnas);

//generador que te crea la matriz con los vectores que le pasaste
MatrizE( vector< double > valores, int cantfilas, int cantcolumnas, vector<int> posvalores, vector<int> inicioFilas);

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
