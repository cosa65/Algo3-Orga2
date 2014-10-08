#include "aux/matriz.h"
#include "aux/Datos.h"
#include "aux/ops.cpp"
#include <fstream>
#include <iostream>

void cargarSNAP (Datos& d, const char* path) {

	ifstream archivo2;
	archivo2.open(path);

	string basura;
	string aCmp = "Nodes:";
	string primerString;
	string segundoString;
	int nodos;
	char numeral = archivo2.peek();
	while(numeral == '#'){
		archivo2 >> primerString;
		archivo2 >> segundoString;
		if (segundoString == aCmp){
			archivo2 >> nodos;
			d.defNodos(nodos);
		}
		getline (archivo2,basura);
		numeral = archivo2.peek();
	}
	int a;
	int b;
	int aant=1; int bant=1; bool listo=false;
	for (int i=0;!listo;i++) {
		aant=a;
		bant=b;
		archivo2 >> a;
		archivo2 >> b;
		if (a!=aant||b!=bant) {
			d.agLink(a,b);
		} else {
			listo=true;
		}
	}

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
	
	cargarSNAP(d,pathEspi);

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
		cout << autoval << '\t' << delta << endl;
		xi=ximas1;
	} 
	return xi;
} 

vector<double> pageRank(Datos& d) {
	MatrizE& matre=d._links; //deja de ser esparsa, hay que mirar el paper que no miré (kanvar) para ver qué onda eso
	int n=matre.Cfilas(); 
	int suma; //Actualizar matriz según algoritmo:
	for (int i=1;i<=n;i++) { //En cada columna, calcular el grado y dividir cada elemento por él
		suma=matre.contarCol(i);
		if (suma>0) {
			matre.divColCte(i,suma);
		} else {
			matre.DefinirCol(1/(double)n,i); //asignar 1/n a todas las filas de los que tienen grado 0
		}
				
	} 
	double aDef;
	Matriz mat(n,n);
	for (int i=1;i<=n;i++) { //multiplicar toda la matriz por c y sumarle (1-c)/n
		for (int j=1;j<=n;j++) {
			aDef = matre.Posicion(i,j)*(d._c)+(1-(d._c))/n;
			mat.Definir(aDef,i,j);
		} 				
	} 
	vector<double> res(mat.Cfilas());
	for (unsigned int i=0;i<res.size();i++) {res[i]=1;}
	res=Potencias(mat,res,d._tolerancia);
	return res;
}

vector<double> HITS(Datos& d) {
	MatrizE& matr=d._links;
	vector<double> x(matr.Cfilas());
	for (unsigned int i=0;i<x.size();i++) {x[i]=1;}
	vector<double> xmas1=x;
	vector<double> y(matr.Cfilas());
	for (unsigned int i=0;i<y.size();i++) {y[i]=1;}
	vector<double> res(matr.Cfilas()*2);
	double delta=d._tolerancia+1;
	porCte(y,1/Norma1(y));
	for (int i=0;delta>d._tolerancia;i++) {

		xmas1=matr.Producto(y);
		porCte(xmas1,1/Norma2(xmas1));
		for (unsigned int j=0;j<x.size();j++) {
			x[j]=xmas1[j]-x[j];
		} delta=Norma2(x);
		x=xmas1;
		y=matr.Ptransp(x);
		porCte(y,1/Norma2(y));

	} for (unsigned int i=0;i<x.size();i++) {
		res[i]=x[i]; 
	} for (unsigned int i=0;i<y.size();i++) {
		res[x.size()+i]=y[i]; 
	} return res;
}

vector<double> InDeg(MatrizE& matr) {
	vector<double> res(matr.Cfilas());
	for (int i=1;i<=matr.Cfilas();i++) {
		res[i-1]=matr.contarCol(i);
	} return res;
}

int main(int argc, char *argv[])
{
	cout << "Cargando...";
	Datos d= cargar(argv[1]);
	cout << " ok" << endl;
	ofstream salida;
	salida.open(argv[2]);
	cout << "Por algún motivo está 2 horas haciendo un vector vacío..." << endl;
	vector<double> res(1);
	cout << "Calculando..." <<endl;
	if (d._metodo==0) {
		res=pageRank(d);
	} else if (d._metodo==1) {
		res=HITS(d);
	} else { //Según el ayudante, devolver el grado de cada pág
		res=InDeg(d._links);
	} for (unsigned int i=0;i<res.size();i++) {
		salida << res[i] << endl; 
	} return 0;
}
