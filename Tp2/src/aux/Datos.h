#include <vector>
#include <iostream>
#include <math.h>
using namespace std;
struct Datos
{
	Datos(int metodo, double c, int tipo, double tolerancia, int nodos, int links);
	void agLink(int src, int dst, int i);
	int _metodo;
	double _c;
	int _tipo;
	double _tolerancia;
	vector<int> _inlinks;
	vector<int> _outlinks;
	int _nodos;
};

Datos::Datos(int metodo, double c, int tipo, double tolerancia, int nodos, int links){
	_metodo=metodo;
	_c=c;
	_tipo=tipo;
	_tolerancia=tolerancia;
	vector<int> A(links);
	vector<int> B(links);
	_inlinks=A;
	_outlinks=B;
	_nodos=nodos;
}

void Datos::agLink(int src, int dst, int i) {
	_inlinks[i]=src;
	_outlinks[i]=dst;
}