#include "aux/csr.h"
#include "aux/matriz.h"
#include "aux/Datos.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <cmath>

vector<double> Producto (Matriz& A, vector<double> x) {
	int lim=x.size();
	vector<double> res(lim);
	for (int i=1;i<=lim;i++) {
		double suma=0;
		for (int j=1;j<=lim;j++) {
			suma+=A.Posicion(i,j)*x[j-1];
		} res[i-1]=suma;
	} return res;
} //probablemente haya que hacer una versión para la esparsa

vector<double> Ptransp (Matriz& A, vector<double> x) { //transpuesto, no transepsual
	int lim=x.size();
	vector<double> res(lim);
	for (int i=1;i<=lim;i++) {
		int suma=0;
		for (int j=0;j<lim;j++) {
			suma+=A.Posicion(j,i)*x[j-1]; //¿soy un picarón o no?
		} res[i-1]=suma;
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
		suma+=abs(v[i]);
	} 
	return suma;
}

vector<double> Potencias (Matriz &A, vector<double> xi, double tolerancia) {
	double autoval=0;
	for (int i=0;abs(autoval-1)>=tolerancia;i++) {
		autoval=Norma2(xi);
		porCte(xi,1/autoval);
		xi=Producto(A, xi);
	} return xi;
} 


Datos cargar(char* in) {
	ifstream archivo;
	archivo.open(in);
	int metodo;
	double c;
	int tipo;
	string path;
	double tolerancia;
    	archivo >> metodo;
	archivo >> c;
	archivo >> tipo;
	archivo >> path;
	archivo >> tolerancia;
	const char* pathEspi=path.c_str();
	
	ifstream archivo2;
	archivo2.open(pathEspi);
	string basura;
	int nodos,links;
	getline (archivo2,basura);
	getline (archivo2,basura);
	archivo2 >> basura;
	archivo2 >> basura;
	archivo2 >> nodos;
	archivo2 >> basura;
	archivo2 >> links;
	getline (archivo2,basura);
	getline (archivo2,basura);

	Datos d=Datos(metodo,c,tipo,tolerancia,nodos,links);
	int a,b;
	for (int i=0;i<links;i++) {
		archivo2 >> a;
		archivo2 >> b;
		d.agLink(a,b,i);
	}

	return d;
}

vector<double> pageRank(Datos d, Matriz &matr) {
	//Matriz mat=copiar(matr); 		//deja de ser esparsa, hay que mirar el paper que no miré (kanvar) para ver qué onda eso
	//Actualizar matriz según algoritmo:

	int n=matr.Cfilas();
	int suma=0;
	for (int i=1;i<=n;i++) { //En cada columna, calcular el grado y dividir cada elemento por él
		suma=0;
		for (int j=1;j<=n;j++) {
			suma+=matr.Posicion(j,i);
		} if (suma>0) {
			for (int j=1;j<=n;j++) {
				matr.Definir(matr.Posicion(j,i)/suma,j,i);
			}
		} else {
			for (int j=1;j<=n;j++) {
				matr.Definir(1/n,j,i); //asignar 1/n a todas las filas de los que tienen grado 0
			}
		}				
	} for (int i=1;i<=n;i++) { //multiplicar toda la matriz por c y sumarle (1-c)/n
		for (int j=1;j<=n;j++) {
			matr.Definir(matr.Posicion(i,j)*d._c+(1-d._c)/n,i,j);
		} 				
	}	
	vector<double> res(matr.Cfilas());
	for (unsigned int i=0;i<res.size();i++) {res[i]=1;}
	res=Potencias(matr,res,d._tolerancia);
	return res;
}

Matriz Generar(Datos d) {
	Matriz mat=Matriz(d._nodos,d._nodos);

	for (int i=1;i<=mat.Cfilas();i++) {
		for (int j=1;j<=mat.Ccolumnas();j++) {
			mat.Definir(0,i,j);
		}
	}

	for (unsigned int i=0;i<d._inlinks.size();i++) {
		mat.Definir(1,d._outlinks[i],d._inlinks[i]);
	} return mat;
}

int main(int argc, char *argv[])
{
	Datos d= cargar(argv[1]);
	Matriz matr=Generar(d); //Genera la de CONECTIVIDAD {0,1}^nxn
	///debería decir MatrizE, pero primero testeemos con una que sabemos que está bien
	ofstream salida;
	salida.open(argv[2]);
	if (d._metodo==0) {
		vector<double> res=pageRank(d, matr);
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
		//"éste último consiste en definir el ranking de las páginas utilizando solamente la cantidad de ejes entrantes a cada una de ellas, ordenándolos en forma decreciente."
	} return 0;
}
