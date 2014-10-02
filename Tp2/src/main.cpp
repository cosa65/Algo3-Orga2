#include "aux/matriz.h"
#include "aux/Datos.h"
#include <fstream>
#include <iostream>
#include <math.h>

vector<double> Producto (Matriz& A, vector<double> x) {
	int lim=x.size();
	vector<double> res(lim);
	for (int i=0;i<lim;i++) {
		int suma=0;
		for (int j=0;j<lim;j++) {
			suma+=A.Posicion(i,j)*x[j];
		} res[i]=suma;
	} return res;
}

vector<double> Ptransp (Matriz& A, vector<double> x) { //transpuesto, no transepsual
	int lim=x.size();
	vector<double> res(lim);
	for (int i=0;i<lim;i++) {
		int suma=0;
		for (int j=0;j<lim;j++) {
			suma+=A.Posicion(j,i)*x[j]; //¿soy un picarón o no?
		} res[i]=suma;
	} return res;
}

void porCte(vector<double> &v, double a) {
	for (unsigned int i=0;i<v.size();i++) {
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
	for (unsigned int i=0;i<d._inlinks.size();i++) {
		mat.Definir(d._inlinks[i],d._outlinks[i],1);
	} return mat;
}

int main(int argc, char *argv[])
{
	Datos d= cargar(argv[1]);
	Matriz matr=Generar(d); //Genera la de CONECTIVIDAD {0,1}^nxn
	ofstream salida;
	salida.open(argv[2]);
	if (d._metodo==0) {
		//Actualizar matriz según algoritmo:
		//En cada columna, calcular el grado y dividir cada elemento por él
		//asignar 1/n a todas las filas de los que tienen grado 0
		//multiplicar toda la matriz por c y sumarle (1-c)*n
		//deja de ser esparsa, hay que mirar el paper que no miré (kanvar) para ver qué onda eso
		vector<double> res(matr.Cfilas());
		int autoval;
		int k=10000; //esto seguro que hay que ver qué onda la tolerancia, es la parte que me falta cachar
		res=Potencias(matr,res,k,autoval);
		for (unsigned int i=0;i<res.size();i++) {
			salida << res[i] << endl; 
		}
	} else if (d._metodo==1) {
		vector<double> x(matr.Cfilas());
		vector<double> y(matr.Cfilas());
		for (int i=0;i<10000;i++) {
			x=Ptransp(matr,y);
			porCte(x,1/Norma2(x));
			y=Producto(matr,x);
			porCte(y,1/Norma2(y));
		} for (unsigned int i=0;i<x.size();i++) {
			salida << x[i] << endl; 
		} for (unsigned int i=0;i<y.size();i++) {
			salida << y[i] << endl; 
		}
	} else {
		//éste último consiste en definir el ranking de las páginas utilizando solamente la cantidad de ejes entrantes a cada una de ellas, ordenándolos en forma decreciente. 
	} return 0;
}
