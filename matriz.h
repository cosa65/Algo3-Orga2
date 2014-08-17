#include <vector>

using namespace std;


struct Matriz
{
public:

//generador basico, no se usa
Matriz();

//~Matriz();

//generador que te crea una matriz de una tamaño, no pide vectores
Matriz( int tamfilas, int tamcolumnas);

//generador que te crea la matriz con los vectores que le pasaste
Matriz(vector <vector<int> >, int tamfilas, int tamcolumnas);

int Posicion(int fila, int columna);

void Definir(int, int fila, int columna);

private:

vector< vector<int> > _array;		//	taria bueno que este fuera un puntero a vector< vector<int> > asi no se pasa por copia, pero tira 											segmentation fault si lo es...


};
