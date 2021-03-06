#include "csc.h"
#include <vector>
#include <iostream>

using namespace std;
struct Datos
{
	Datos(long int metodo, double c, double tolerancia);
	void defNodos(long int n);

	long int _metodo;
	double _c;
	double _tolerancia;
	MatrizE _links;
	long int _nodos;
};

Datos::Datos(long int metodo, double c, double tolerancia){
	_metodo=metodo;
	_c=c;
	_tolerancia=tolerancia;
}

void Datos::defNodos(long int n) {
	_nodos=n;
	_links=MatrizE(n,n);
}
