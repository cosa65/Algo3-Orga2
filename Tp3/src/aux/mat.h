#include <vector>
#include <iostream>

using namespace std;

typedef unsigned int uint;

struct pixel
{

pixel(uint rojoIn, uint verdeIn, uint azulIn);

uint rojo;
uint verde;
uint azul;

};

typedef vector < pixel > fila;

struct Matriz
{
public:

//generador que te crea una matriz de un tamaño, no pide vectores
Matriz( int cantfilas, int cantcolumnas);

//generador que te crea la matriz con los vectores que le pasaste
//Matriz( vector < vector <pixel> > filas, int cantfilas, int cantcolumnas);

void Definir(pixel adefinir, int fila, int columna);

pixel Posicion(int fila, int columna);

int Cfilas();

int Ccolumnas();

int TamTotal();

void mostrar();

uint sumarVec(int x, int y, int dirx, int diry)

private:

vector< vector <pixel> > _array;

int _Cfilas;

int _Ccolumnas;

};

pixel :: pixel(uint rojoIn, uint verdeIn, uint azulIn){

rojo = rojoIn;

verde = verdeIn;

azul = azulIn;

}
