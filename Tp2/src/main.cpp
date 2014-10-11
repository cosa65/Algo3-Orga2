//#include "aux/matriz.h"
#include <time.h>
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
		if (i%3000==0) {
			cout << i << endl;
		}
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

vector<double> pageRank(Datos& d) {
	MatrizE& matre=d._links; 
	int n=matre.Cfilas(); 
	int suma; 
	for (int i=1;i<=n;i++) { //En cada columna, calcular el grado y dividir cada elemento por él
		suma=matre.contarCol(i);
		if (suma>0) {
			matre.divColCte(i,suma);
		}
	}
	double inv=1/(double)n;
	vector<double> xi(n) ; for (int i=0;i<n;i++) {xi[i]=inv;}
	vector<double> yi(n);
//	vector<double> v(n) ; for (int i=0;i<n;i++) {v[i]=inv;}
	ofstream normas;
	normas.open("Normas",ios_base::app);
	double w=d._tolerancia+1;
	int k=0;
	while (w>d._tolerancia) {
		if (k%100==0) {cout << k<<endl;k++;}
		cout << k << endl;k++;
		yi=matre.Producto(&(xi));
		
		porCte(yi,d._c); //c*P^T*x
		w=Norma1(xi)-Norma1(yi);

		for (int j=0;j<n;j++) {
			yi[j]+=w*inv; //y+=wv
		} 
		for (int i=0;i<n;i++)  {
			xi[i]=xi[i]-yi[i];
		} 
		w=Norma2(xi);
		normas << w << endl;
		w=Norma1(yi);
		for (int j=0;j<n;j++) {
			xi[j]=yi[j]/w; 
		}
	} return xi;
}

vector<double> HITS(Datos& d) {
	MatrizE& matr=d._links;
	int n=matr.Cfilas(); 
	vector<double> x(n);
	for (int i=0;i<n;i++) {x[i]=1;}
	vector<double> xmas1=x;
	vector<double> ymas1=x;
	vector<double> y(matr.Cfilas());
	for (int i=0;i<n;i++) {y[i]=1;}
	vector<double> res(n*2);
	double delta=d._tolerancia+1;double deltay;
	porCte(y,1/Norma1(y));
	ofstream normas;
	normas.open("Normas",ios_base::app);
	while (delta>d._tolerancia) {
		xmas1=matr.Producto(&(y));

		porCte(xmas1,1/Norma2(xmas1));
		for (int j=0;j<n;j++) {
			x[j]=xmas1[j]-x[j];
		} delta=Norma2(x);

		normas << delta << '\t';
		x=xmas1;

		ymas1=matr.Ptransp(&(x));

		porCte(ymas1,1/Norma2(ymas1));
		for (int j=0;j<n;j++) {
			y[j]=ymas1[j]-y[j];
		} deltay=Norma2(y);
		y=ymas1;
		normas << deltay << endl;

	} for (int i=0;i<n;i++) {
		res[i]=x[i]; 
		res[n+i]=y[i]; 
	} return res;
}

vector<double> InDeg(MatrizE& matr) {
	vector<double> res(matr.Ccolumnas());
	for (int i=1;i<=matr.Ccolumnas();i++) {
		res[i-1]=matr.contarFila(i);
	} return res;
}

int main(int argc, char *argv[])
{
	remove("Normas");
	clock_t t;
	cout << "Cargando...";
	Datos d= cargar(argv[1]);
	cout << " ok" << endl;
	ofstream salida;
	salida.open(argv[2]);
	vector<double> res(1);
	cout << "Calculando...";
	t = clock();
	if (d._metodo==0) {
		res=pageRank(d);
	} else if (d._metodo==1) {
		res=HITS(d);
	} else { //Devolver el grado de cada pág
		res=InDeg(d._links);
	} cout << " ok" << endl;
	for (unsigned int i=0;i<res.size();i++) {
		salida << res[i] << endl; 
	} 
		
	ofstream tiempo;
	t = clock() - t;
	tiempo.open("Tiempo");
	tiempo << "Clocks: "<< (int)t << " segundos: " << ((int)t)/CLOCKS_PER_SEC << endl;

	if (argc==4) { //No sé si es la mejor forma de hacerlo, pero es mejor que tener 5 txt iguales.
		double ces[5];
		ces[0]=0.5;ces[1]=0.7;ces[2]=0.85;ces[3]=0.95;
		for (int i=0;i<=3;i++) {
			t = clock();			
			d._c=ces[i];
			res=pageRank(d);
			for (unsigned int i=0;i<res.size();i++) {
				salida << res[i] << endl; 
			} t = clock() - t;
			tiempo << "Clocks: "<< (int)t << " segundos: " << ((int)t)/CLOCKS_PER_SEC << endl;
		}
	}

	return 0;

}
