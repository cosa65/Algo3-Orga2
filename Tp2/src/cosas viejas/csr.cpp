#include "csr.h"
#include <vector>
#include <iostream>

using namespace std;

typedef vector<double> fila;

//generador basico, no se usa
//Matriz();

//~Matriz();

//generador que te crea una matriz de un tamaño, no pide vectores

MatrizE::MatrizE(int Cfilas, int Ccolumnas){
	_Cfilas = Cfilas;
	_Ccolumnas = Ccolumnas;
	_inicioFilas.resize(Cfilas+1);
	for (int i = 0; i<=_Cfilas; i++){_inicioFilas[i]=1;}
}

void MatrizE::Definir(double adefinir, int fila, int columna) {
	if (adefinir>0) {
		int size = _valores.size()+1;

		_valores.resize(size);
		_posValores.resize(size);

		int i =	_inicioFilas[fila-1]-1;
		int j = _inicioFilas[fila];
		int lugar=j-1;
		for (int k=i;k<j;k++) {
			if (_posValores[k]>columna) {
				lugar=k;
				k=j;	
			}
		} 
	
		for (int k=size-1;k>lugar;k--) {
			_valores[k]=_valores[k-1];
			_posValores[k]=_posValores[k-1];		
		} _valores[lugar]=adefinir;
		_posValores[lugar]=columna;

		for (int i=fila;i<=_Cfilas;i++) {
			_inicioFilas[i]++;
		}
	} 
}

void MatrizE::Redefinir(double valor, int fila, int columna) {
	int i =	_inicioFilas[fila-1]-1;
	int j =	_inicioFilas[fila]-1;
	for (int k=i;k<j;k++) {
		if (_posValores[k]==columna) {
			_valores[k]=valor;
		}
	} 
}

double MatrizE::Posicion(int fila, int columna) {

	int i =	_inicioFilas[fila-1]-1;

	int j =	_inicioFilas[fila]-1;

	for (int k=i;k<j;k++) {
		if (_posValores[k]==columna) {
			return _valores[k];
		}
	} return 0;
}

/*void MatrizE::divFila(int fila, int valor) {
	int i =	_inicioFilas[fila-1]-1;
	int j =	_inicioFilas[fila]-1;
	for (int k=i;k<j;k++) {
		_valores[k]=_valores[k]/valor;
	} 
}*/

int MatrizE::Cfilas(){
	return _Cfilas;
}

void MatrizE::mostrar(){
	for (int i=1;i<=_Ccolumnas;i++) {
		for (int j=1;j<=_Cfilas;j++) {
			cout << Posicion(i,j) << " ";
		} cout << endl;
	}
}

vector<double> MatrizE::Producto (vector<double> x) {
	int lim=x.size();
	vector<double> res(lim);
	for (int i=1;i<=lim;i++) {
		double suma=0;
		for (int j=1;j<=lim;j++) {
			suma+=Posicion(i,j)*x[j-1];
		} res[i-1]=suma;
	} return res;
}

vector<double> MatrizE::Ptransp (vector<double> x) { //transpuesto, no transepsual
	int lim=x.size();
	vector<double> res(lim);
	for (int i=1;i<=lim;i++) {
		double suma=0;
		for (int j=1;j<=lim;j++) {
			suma+=Posicion(j,i)*x[j-1]; //¿soy un picarón o no?
		} res[i-1]=suma;
	} return res;
}
