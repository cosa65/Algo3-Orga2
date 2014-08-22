

using namespace std;

typedef vector<double> fila;

struct Matriz
{
public:

//generador basico, no se usa
Matriz();

//~Matriz();

//generador que te crea una matriz de una tamaño, no pide vectores
Matriz( int cantfilas, int cantcolumnas);

//generador que te crea la matriz con los vectores que le pasaste
Matriz(vector <vector<double> >, int cantfilas, int cantcolumnas, vector<double>);

void Definir(double adefinir, int fila, int columna);

void DefinirB(double def,int fila);

void intercambiarFilas(int fila1, int fila2);

void restarFilas(int filaRestada, int filaQueResta, double multFilaARestar);

double Posicion(int fila, int columna);

double PosIndep(int fila);

int Cfilas();

int Ccolumnas();

int TamTotal();

void mostrar();

private:

vector< vector<double> > _array;		//	taria bueno que este fuera un puntero a vector< vector<double> > asi no se pasa por copia, pero tira 											segmentation fault si lo es...
int _Cfilas;

int _Ccolumnas;

vector<double> _indeps;

};
