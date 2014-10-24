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

MatrizE( long int Ccolumnas, long int Cfilas);

//generador que te crea la matriz con los vectores que le pasaste
MatrizE( vector< double > valores, long int cantColumnas, long int cantFilas, vector<long int> posvalores, vector<long int> inicioColumnas);

void Definir(double adefinir, long int columna, long int fila);
void DefinirUnos(long int columna, long int fila);
void DefinirCol(double adefinir, long int columna);

double Posicion(long int columna, long int fila);

long int Cfilas();
long int Ccolumnas();

void mostrar();

void divColCte(long int col, double cte);
long int contarCol(long int col);
double contarFila(long int fila);

vector<double> Producto (vector<double>* x);
vector<double> Ptransp (vector<double>* x);

private:

vector <double> _valores;

vector <long int> _posValores;

vector <long int> _inicioColumnas;

long int _Ccolumnas;

long int _Cfilas;

};
