#include "csc.h"
#include <vector>
#include <iostream>

using namespace std;
struct Datos
{
	Datos(int metodo, double c, double tolerancia);
	void defNodos(int n);
	void agLink(int src, int dst);

	int _metodo;
	double _c;
	double _tolerancia;
	MatrizE _links;
	int _nodos;
};

Datos::Datos(int metodo, double c, double tolerancia){
	_metodo=metodo;
	_c=c;
	_tolerancia=tolerancia;
}

void Datos::defNodos(int n) {
	_nodos=n;
	_links=MatrizE(n,n);
}

void Datos::agLink(int src, int dst) {
	_links.Definir(1,dst,src);
}
