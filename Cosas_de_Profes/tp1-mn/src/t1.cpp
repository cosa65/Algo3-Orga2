//g++ main.cpp -o main
#include <iostream>
#include <fstream>
#include "aux/matriz.h"
#include <math.h>
//#include "matrizBanda.cpp"
using namespace std;

Matriz EliminacionGaussiana (Matriz mat){

	int filas = mat.Cfilas();

	for(int i=1; i<=filas; i++){


		if (mat.Posicion(i, i) == 0){
		//casoA: que el elemento i de mi fila actual ya valga 0
			for (int y = filas; y >i; y--){
				if (mat.Posicion(y,i) !=0) {
				mat.intercambiarFilas(y,i);
				y = i;
				}
			}

		}
		//pivoteo parcial (TIRAN NaN cuando pongo esto!), debe tardar bastante mas que el casoA
		/*for (int y = filas; y >i; y--){
			if (mat.Posicion(y,i) > mat.Posicion(i,i)) {
			mat.intercambiarFilas(y,i);
			y = i;
			}
		}*/
		
		//caso que el elemento i de mi fila actual no valga 0
		for(int j=i+1; j<=filas; j++){
			if(mat.Posicion(j,i)!=0){
				long double mult = mat.Posicion(j,i) / (mat.Posicion(i,i));
				mat.restarFilas(j, i, mult);
			}
		}

	}
	return mat;
}



bool enSanguijuela (vector <long double> vx, vector <long double> vy, int x, int y, int r) {
	for(int i=0;i<vx.size();i++) {
		if (sqrt((vx[i]-x)*(vx[i]-x)+(vy[i]-y)*(vy[i]-y)) <= r) { ///La distancia debe ser menor al radio
			return true;
		}
	} return false;
}

bool esBorde (int l, int a, int x, int y) {
	if (x==a || y==l || x==1 || y==1) {
		return true;
	} return false;
}

Matriz cargar(char* in) {
    ifstream archivo;
    archivo.open(in);
    int anchoParab;
	int largoParab;
	int h;
    	archivo >> anchoParab;
	archivo >> largoParab;
	archivo >> h;
	int ancho=(anchoParab/h)+1;
	int largo=(anchoParab/h)+1;
	Matriz m=Matriz(ancho*largo,ancho*largo);
	m.DefGranulidad(h,anchoParab);
	int radio;
	archivo >> radio;
	long double Temp;
	archivo >> Temp;
	int cant;
	archivo >> cant;
	vector<long double> Posx(cant);
	vector<long double> Posy(cant);
	for (int i=0;i<cant;i++) {
		archivo >> Posx[i]; 			//X de las sanguijuelas
		archivo >> Posy[i];			//Y de las sanguijuelas
	}
		// fin carga de argumentos

	for (int i=1;i<=ancho*largo;i++) {
		int y=(i-1)/ancho+1; 	// x e y son el lugar del vector incógnita al que corresponde la fila i
		int x;
		if (i%ancho==0) {x = ancho;} else {x=i%ancho;}
		if (enSanguijuela(Posx,Posy,(x-1)*h,(y-1)*h,radio) || esBorde (ancho,largo,x,y)) {
			for (int j=1;j<=ancho*largo;j++) { ///Defino la fila con un 1 en la diagonal
				if (i==j) {	
					m.Definir(1,i,j);
				} else {					
					m.Definir(0,i,j);
				} if (esBorde(ancho,largo,x,y)) {
					m.DefinirB(-100,i);
				} else {
					m.DefinirB(Temp,i);
				}
			}
		} else {
			for (int j=1;j<=ancho*largo;j++) { 
				if (i==j) {
					m.Definir(-1,i,j); ///Defino la fila con un -1 en la diagonal...
				} else if (i==j-1 || i==j+1 || i-j==ancho || j-i==ancho) {
					m.Definir(0.25,i,j); /// ...y 1/4 en las columnas de las celdas adyacentes del parabrisas.
				} else { 
					m.Definir(0,i,j);
				} m.DefinirB(0,i); ///Agrega un 0 en los términos independientes
			} 
		}
	}
	return m;
}

vector<double> ResolucionFosquiMan (Matriz mat){
	int n = mat.Cfilas();
	vector<double> x(n);
	for (int i=0; i < n; i++ ){
		double acum=mat.PosIndep(n-i);
		for(int j=n-i+1; j <=n; j++) {
			acum=acum-mat.Posicion(n-i, j)*x[j];
		}
	x[n-i-1] = acum;
	} return x;
}

void devolver (Matriz matr, vector<double> x, char* out) {
	int h=matr.Granularidad();
	int ap=matr.AnchoParab();
	ofstream f2;
    	f2.open(out);
	for (int i=1;i<=matr.Cfilas();i++) {
		/*int ry=((i-1)/(ap/h+1))*h; 
		int rx;
		if (i%(ap/h+1)==0) {rx = (ap/h+1);} else {rx=i%(ap/h+1);}
		rx=(rx-1)*h;*/ // todo esto era al pedo, miren test1.expected
		int ry=((i-1)/(ap/h+1)); 
		int rx=((i-1)%(ap/h+1));
		f2<< ry << "\t" << rx << "\t" << x[i-1] << endl;
	} 
}

int main(int argc, char *argv[])
{



	//for(int testI=1; testI< argc; testI+=2){

	{Matriz matr = cargar(argv[1]);
	matr=EliminacionGaussiana(matr);
	vector<double> x=ResolucionFosquiMan(matr);
	devolver(matr,x,argv[2]);}

	//}

	return 0;
}
