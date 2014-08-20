#include <vector>

using namespace std;



struct MatrizB
{
public:

MatrizB();

MatrizB(int cantfilas, int cantcolumnasA, int cantcolumnasD);

MatrizB(vector< vector<double> > , int cantfilas, int cantcolumnasA, int cantcolumnasD);

void Definir(double adefinir, int fila, int columna);

void intercambiarFilas(int fila1, int fila2);

void restarFilas(int filaRestada, int filaQueResta, double multFilaARestar);

double Posicion(int fila, int columna);

int Cfilas();

int Ccolumnas();

int TamTotal();


private:

vector<vector<double> > _array;

int _Cfilas;
int _CcolumnasA;
int _CcolumnasD;

};
