#include "aux/matriz.h"
#include "aux/csr.h"
#include "aux/Datos.h"
#include "aux/ops.cpp"
#include <fstream>
#include <iostream>
#include <math.h>
#include <cmath>

void cargarSNAP (Datos& d, const char* path) {

	ifstream archivo2;
	archivo2.open(path);

	string basura;
	int nodos,links;
	getline (archivo2,basura);
	getline (archivo2,basura);
	archivo2 >> basura;
	archivo2 >> basura;
	archivo2 >> nodos;
	d._nodos=nodos;
	archivo2 >> basura;
	archivo2 >> links;
	d.DefLinks(links);
	getline (archivo2,basura);
	getline (archivo2,basura); //mejorar esto para que corra todos los tests
	int a,b;
	for (int i=0;i<links;i++) {
		archivo2 >> a;
		archivo2 >> b;
		d.agLink(a,b,i);
	}

}

void cargarToronto (Datos& d, const char* path) {
	ifstream archivo2;
	archivo2.open(path);
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
	Datos d=Datos(metodo,c,tolerancia);

	const char* pathEspi=path.c_str();
	
	if (tipo==0) {
		cargarSNAP(d,pathEspi);
	} else {
		cargarToronto(d,pathEspi);
	}
	return d;
}

vector<double> Potencias (Matriz &A, vector<double> xi, double tolerancia) {
	double autoval=0; double delta=tolerancia+1;
	for (int i=0;delta>tolerancia;i++) {
		autoval=Norma1(xi);
		porCte(xi,1/autoval);
		vector<double> ximas1=A.Producto(xi);
		for (unsigned int j=0;j<xi.size();j++) {
			xi[j]=xi[j]-ximas1[j];
		}
		delta=Norma2(xi);
		xi=ximas1;
	} 
	return xi;
} 

vector<double> pageRank(Datos& d, MatrizE &matre) {
	int n=matre.Cfilas(); //deja de ser esparsa, hay que mirar el paper que no miré (kanvar) para ver qué onda eso
	int suma=0; //Actualizar matriz según algoritmo:
	for (int i=1;i<=n;i++) { //En cada columna, calcular el grado y dividir cada elemento por él
		suma=0;
		for (int j=1;j<=n;j++) {
			suma+=matre.Posicion(j,i);
		} if (suma>0) {
			for (int j=1;j<=n;j++) {
				if (matre.Posicion(j,i)>0) {
					matre.Redefinir(matre.Posicion(j,i)/suma,j,i); //esto es mucho mejor si guardamos por columna
				}
			}
		} else {
			for (int j=1;j<=n;j++) {
				matre.Definir(1/n,j,i); //asignar 1/n a todas las filas de los que tienen grado 0
			}
		}				
	} Matriz mat(n,n);
	for (int i=1;i<=n;i++) { //multiplicar toda la matriz por c y sumarle (1-c)/n
		for (int j=1;j<=n;j++) {
			mat.Definir(matre.Posicion(i,j)*d._c+(1-d._c)/n,i,j);
		} 				
	} mat.mostrar();
	vector<double> res(mat.Cfilas());
	for (unsigned int i=0;i<res.size();i++) {res[i]=1;}
	res=Potencias(mat,res,d._tolerancia);
	return res;
}

vector<double> HITS(Datos& d, MatrizE& matr) {
	vector<double> x(matr.Cfilas());
	for (unsigned int i=0;i<x.size();i++) {x[i]=1;}
	vector<double> xmas1=x;
	vector<double> y(matr.Cfilas());
	for (unsigned int i=0;i<y.size();i++) {y[i]=1;}
	vector<double> res(matr.Cfilas()*2);
	double delta=d._tolerancia+1;
	for (int i=0;delta>d._tolerancia;i++) {
		porCte(y,1/Norma1(y));
		xmas1=matr.Ptransp(y);
		porCte(xmas1,1/Norma1(xmas1));
		for (unsigned int j=0;j<x.size();j++) {
			x[j]=xmas1[j]-x[j];
		} delta=Norma2(x);
		x=xmas1;
		y=matr.Producto(x);

	} for (unsigned int i=0;i<x.size();i++) {
		res[i]=x[i]; 
	} for (unsigned int i=0;i<y.size();i++) {
		res[x.size()+i]=y[i]; 
	} return res;
}

MatrizE Generar(Datos& d) {
	MatrizE mat=MatrizE(d._nodos,d._nodos);

	for (unsigned int i=0;i<d._inlinks.size();i++) {
		mat.Definir(1,d._outlinks[i],d._inlinks[i]);
	} return mat;
}

int main(int argc, char *argv[])
{
	Datos d= cargar(argv[1]);
	MatrizE matr=Generar(d); //Genera la de CONECTIVIDAD {0,1}^nxn
	ofstream salida;
	salida.open(argv[2]);
	vector<double> res(matr.Cfilas());
	if (d._metodo==0) {
		res=pageRank(d, matr);
	} else if (d._metodo==1) {
		res=HITS(d,matr);
	} else { //"IN-DEG consiste en definir el ranking de las páginas utilizando solamente la cantidad de ejes entrantes a cada una de ellas, ordenándolos en forma decreciente."
		for (int i=1;i<=matr.Cfilas();i++) {
			int suma=0;
			for (int j=1;j<=matr.Cfilas();j++) {
				suma+=matr.Posicion(i,j);
			} res[i-1]=suma;
		}
	} for (unsigned int i=0;i<res.size();i++) {
		salida << res[i] << endl; 
	} return 0;
}
