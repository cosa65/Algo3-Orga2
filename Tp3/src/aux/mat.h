#include <vector>
#include <iostream>

using namespace std;

typedef unsigned int uint;

struct pixel
{

pixel();
pixel(uint rojoIn, uint verdeIn, uint azulIn);

uint red;
uint green;
uint blue;

};



typedef vector < pixel > fila;

struct Matriz
{
public:

//generador basico, no se usa
Matriz();

//~Matriz();

//generador que te crea una matriz de un tamaño, no pide vectores
Matriz( int cantfilas, int cantcolumnas);

//generador que te crea la matriz con los vectores que le pasaste
Matriz( vector< vector<pixel> > filas, int cantfilas, int cantcolumnas);

void Definir(pixel adefinir, int fila, int columna);

void DefColor(uint adefinir, int fila, int columna, char color);

pixel Posicion(int fila, int columna);

uint PosColor(int fila, int columna, char color);

int Cfilas();

int Ccolumnas();

int TamTotal();

void mostrar();

private:

vector< vector<pixel> > _array;

int _Cfilas;

int _Ccolumnas;

};
