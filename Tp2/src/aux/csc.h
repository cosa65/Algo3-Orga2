#include <vector>
#include <iostream>

using namespace std;

typedef vector<double> Columna;

struct MatrizE
{
public:

//generador basico, no se usa
MatrizE();

//~Matriz();

//generador que te crea una matriz de un tamaño, no pide vectores

MatrizE( int CColumnas, int CFilas);

//generador que te crea la matriz con los vectores que le pasaste
MatrizE( vector< double > valores, int cantColumnas, int cantFilas, vector<int> posvalores, vector<int> inicioColumnas);

void Definir(double adefinir, int Columna, int Fila);
void Redefinir(double adefinir, int Columna, int Fila);

double Posicion(int Columna, int Fila);

int Cfilas();

void mostrar();

void divColCte(int col, double cte);
int contarCol(int col);

vector<double> Producto (vector<double> x);
vector<double> Ptransp (vector<double> x);

private:

vector <double> _valores;

vector <int> _posValores;

vector <int> _inicioColumnas;

int _CColumnas;

int _CFilas;

};