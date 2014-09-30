#include "aux/matriz.h"
#include <math.h>

vector<double> Producto (Matriz& A, vector<double> x) {
	int lim=x.size();
	vector<double> res = vector<double> (lim);
	for (i=0;i<lim;i++) {
		int suma=0;
		for (j=0;j<lim;j++) {
			suma+=A.Posicion(i,j);
		} res[i]=suma;
	}
}

void porCte(vector<double>& v, double a) {
	for (i=0;i<v.size;i++) {
		v[i]=v[i]/a;
	}
}

double Norma2 (vector<double> v) {
	int lim=v.size()
	double suma=0;
	for (int i=0;i<lim;i++) {
		suma+=v[i];
	} return sqrt(suma);
}

vector<double> Potencias (Matriz A&, vector<double> xi, int k) {
	for (int i=0;i<k;i++) {
		xi=producto(A, xi);
		porCte(Axi,1/Norma2(Axi));
	} return xi;
}

Datos cargar(char* in) {
	ifstream archivo;
	archivo.open(in);
	int metodo;
	double c;
	int tipo
	string path;
	double tolerancia;
    	archivo >> metodo;
	archivo >> c;
	archivo >> tipo;
	archivo >> path;
	archivo >> tolerancia;
	Datos d=Datos(metodo,c,tipo,path,tolerancia)
	return d;
}

Matriz Generar(Datos d) {
	ifstream archivo;
	archivo.open(d.path());
	string basura;
	getline (archivo, basura);
	getline (archivo, basura);
	getline (archivo, basura); //acá está m y n en realidad
	getline (archivo, basura);
	
	double src; double dst;
	Matriz mat=Matriz(n,n);
	for (int i=0;i<mat;i++) {
		archivo >> src;
		archivo >> dst;
		mat.Definir(src,dst,1);
	} return mat;
}

int main(int argc, char *argv[])
{
	Datos d= cargar(argv[1]);
	Matriz matr=matr.Generar(d);
	} return 0;
}
