//g++ main.cpp -o main
#include <iostream>
#include <fstream>
#include "matriz.cpp"
#include <math.h>
#include "matrizBanda.cpp"
using namespace std;


//va como una operacion de Matriz esta

/*void intercambiarFilas(Matriz mat, int fila1, int fila2){

	double guarda1;

	double guarda2;

	int tamFila = mat.Ccolumnas();

	for(int i = 1; i <= tamFila; i++){

		guarda2 = mat.Posicion(fila1, i);
		guarda2 = mat.Posicion(fila2, i);

		mat.Definir(guarda1, fila2, i);
		mat.Definir(guarda2, fila1, i);

		}

	cout << endl << mat.Posicion(fila1,1) << mat.Posicion(fila1,2) <<mat.Posicion(fila1,3) << endl;
	cout << endl << mat.Posicion(2,1) << mat.Posicion(2,2) <<mat.Posicion(fila1,3) << endl;

}*/

Matriz EliminacionGaussiana (Matriz mat){

	int filas = mat.Cfilas();

	for(int i=1; i<=filas; i++){


		if (mat.Posicion(i, i) == 0){
		//caso que el elemento i de mi fila actual ya valga 0
			for (int y = filas; y >i; y--){
				if (mat.Posicion(y,i) !=0) {
				mat.intercambiarFilas(y,i);
				y = i;
				}
			}

		}
		else{
		//caso que el elemento i de mi fila actual no valga 0

			for(int j=i+1; j<=filas; j++){

				if(mat.Posicion(j,i)!=0){
					double mult = mat.Posicion(j,i) / (mat.Posicion(i,i));
					mat.restarFilas(j, i, mult);
				}

			}

		}

	}
	return mat;
}



bool enSanguijuela (vector <double> vx, vector <double> vy, int x, int y, int r) {
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

Matriz cargar() {
    ifstream archivo;
    string input = "";
    cout << "Ingrese nombre de archivo existente: ";
    getline(cin, input);
    archivo.open(input.c_str());
    int anchoParab;
	int largoParab;
	int h;
    archivo >> anchoParab;
	archivo >> largoParab;
	archivo >> h;
	int ancho=(anchoParab/h)+1;
	int largo=(anchoParab/h)+1;
	Matriz m=Matriz(ancho*largo,ancho*largo);
	m.DefGrandidad(h,anchoParab);
	int radio;
	archivo >> radio;
	double Temp;
	archivo >> Temp;
	int cant;
	archivo >> cant;
	vector<double> Posx(cant);
	vector<double> Posy(cant);
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
				} else if (i==j-1 || i==j+1 || i-j==ancho-1 || j-i==ancho-1) {
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
	x[n-i] = acum;
	} return x;
}

int main()
{
	Matriz matr = cargar();
	matr=EliminacionGaussiana(matr);
	matr.mostrar();
	vector<double> x=ResolucionFosquiMan(matr);
	int h=matr.Granularidad();
	ofstream f2;
	string input = "";
    cout << "Ingrese nombre de archivo de salida: ";
    getline(cin, input);
    f2.open(input.c_str(), ofstream::out);
	for (int i=1;i<matr.Cfilas();i++) {
		int ry=(i-1)/matr.AnchoParab()*h;
		int rx;
		if (i%matr.AnchoParab()==0) {rx = matr.AnchoParab();} else {rx=i%matr.AnchoParab();}
		rx=(rx-1)*h;
		f2<< ry << " " << rx << " " << x[i] << endl;
	} 
	return 0;
}
