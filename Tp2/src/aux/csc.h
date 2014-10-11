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

MatrizE( int Ccolumnas, int Cfilas);

//generador que te crea la matriz con los vectores que le pasaste
MatrizE( vector< double > valores, int cantColumnas, int cantFilas, vector<int> posvalores, vector<int> inicioColumnas);

void Definir(double adefinir, int columna, int fila);
void DefinirUnos(int columna, int fila);
void DefinirCol(double adefinir, int columna);

double Posicion(int columna, int fila);

int Cfilas();
int Ccolumnas();

void mostrar();

void divColCte(int col, double cte);
int contarCol(int col);
double contarFila(int fila);

vector<double> Producto (vector<double>* x);
vector<double> Ptransp (vector<double>* x);

private:

vector <double> _valores;

vector <int> _posValores;

vector <int> _inicioColumnas;

int _Ccolumnas;

int _Cfilas;

};
