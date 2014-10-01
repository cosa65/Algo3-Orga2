#include "aux/matriz.h"
#include "aux/Datos.h"
#include <fstream>
#include <iostream>
#include <math.h>

vector<double> Producto (Matriz& A, vector<double> x) {
	int lim=x.size();
	vector<double> res; //= vector<double> (lim);
	res.resize(lim);
	for (int i=0;i<lim;i++) {
		int suma=0;
		for (int j=0;j<lim;j++) {
			suma+=A.Posicion(i,j);
		} res[i]=suma;
	} return res;
}

void porCte(vector<double> &v, double a) {
	for (int i=0;i<v.size();i++) {
		v[i]=v[i]*a;
	}
}

double Norma2 (vector<double> v) {
	unsigned int lim=v.size();
	double suma=0;
	for (unsigned int i=0;i<lim;i++) {
		suma+=v[i];
	} 
	return sqrt(suma);
}

vector<double> Potencias (Matriz &A, vector<double> xi, int k, int autoval) {
	for (int i=0;i<k;i++) {
		xi=Producto(A, xi);
		autoval=Norma2(xi);
		porCte(xi,1/autoval);
	} return xi;
}

Datos cargar(char* in) {
	ifstream archivo;
	archivo.open(in);
	int metodo;
	double c;
	int tipo;
	char *path;
	double tolerancia;
    	archivo >> metodo;
	archivo >> c;
	archivo >> tipo;
	archivo >> path;
	archivo >> tolerancia;
	
	ifstream archivo2;
	archivo2.open(path);
	string basura;
	int nodos,links;
	getline (archivo2, basura);
	getline (archivo2, basura);
	archivo2 >> basura;
	archivo2 >> nodos;
	archivo2 >> basura;
	archivo2 >> links;
	getline (archivo2, basura);

	Datos d=Datos(metodo,c,tipo,tolerancia,nodos,links);
	int a,b;
	for (int i=0;i<links;i++) {
		archivo2 >> a;
		archivo2 >> b;
		d.agLink(a,b,i);
	}

	return d;
}

Matriz Generar(Datos d) {
	Matriz mat=Matriz(d._nodos,d._nodos);
	for (int i=0;i<d._inlinks.size();i++) {
		mat.Definir(d._inlinks[i],d._outlinks[i],1);
	} return mat;
}

int main(int argc, char *argv[])
{
	Datos d= cargar(argv[1]);
	Matriz matr=Generar(d);
	return 0;
}
