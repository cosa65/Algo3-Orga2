#include <vector>
#include <iostream>
#include <math.h>
using namespace std;
struct Datos
{
	Datos(int metodo, double c, double tolerancia);
	void DefLinks(int a);
	void agLink(int src, int dst, int i);

	int _metodo;
	double _c;
	double _tolerancia;
	vector<int> _inlinks;
	vector<int> _outlinks;
	int _nodos;
};

Datos::Datos(int metodo, double c, double tolerancia){
	_metodo=metodo;
	_c=c;
	_tolerancia=tolerancia;
	_nodos=0;
}

void Datos::DefLinks(int links) {
	vector<int> A(links);
	vector<int> B(links);
	_inlinks=A;
	_outlinks=B;
}


void Datos::agLink(int src, int dst, int i) {
	_inlinks[i]=src;
	_outlinks[i]=dst;
}
