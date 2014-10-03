#include "csc.h"
#include <vector>
#include <iostream>

using namespace std;

typedef vector<double> Columna;

//generador basico, no se usa
//Matriz();

//~Matriz();

//generador que te crea una matriz de un tamaño, no pide vectores

MatrizE::MatrizE(int CColumnas, int CFilas){
	_CColumnas = CColumnas;
	_CFilas = CFilas;
	_inicioColumnas.resize(CColumnas+1);
	for (int i = 0; i<=_CColumnas; i++){_inicioColumnas[i]=1;}
}

void MatrizE::Definir(double adefinir, int Fila, int Columna) {
	if (adefinir>0) {
		int size = _valores.size()+1;

		_valores.resize(size);
		_posValores.resize(size);

		int i =	_inicioColumnas[Columna-1]-1;
		int j = _inicioColumnas[Columna];
		int lugar=j-1;
		for (int k=i;k<j;k++) {
			if (_posValores[k]>Fila) {
				lugar=k;
				k=j;	
			}
		} 
	
		for (int k=size-1;k>lugar;k--) {
			_valores[k]=_valores[k-1];
			_posValores[k]=_posValores[k-1];		
		} _valores[lugar]=adefinir;
		_posValores[lugar]=Fila;

		for (int i=Columna;i<=_CColumnas;i++) {
			_inicioColumnas[i]++;
		}
	} 
}

void MatrizE::Redefinir(double valor, int Fila, int Columna) {
	int i =	_inicioColumnas[Columna-1]-1;
	int j =	_inicioColumnas[Columna]-1;
	for (int k=i;k<j;k++) {
		if (_posValores[k]==Fila) {
			_valores[k]=valor;
		}
	} 
}

double MatrizE::Posicion(int Fila, int Columna) {

	int i =	_inicioColumnas[Columna-1]-1;

	int j =	_inicioColumnas[Columna]-1;

	for (int k=i;k<j;k++) {
		if (_posValores[k]==Fila) {
			return _valores[k];
		}
	} return 0;
}

int MatrizE::Cfilas(){
	return _CColumnas;
}

void MatrizE::mostrar(){
	for (int i=1;i<=_CFilas;i++) {
		for (int j=1;j<=_CColumnas;j++) {
			cout << Posicion(i,j) << " ";
		} cout << endl;
	}
}

void MatrizE::divColCte(int col, double cte){
	int i =	_inicioColumnas[col-1]-1;
	int j =	_inicioColumnas[col]-1;
	for (int k=i;k<j;k++) {
		_valores[k]=_valores[k]/cte;
	} 
}

int MatrizE::contarCol(int col){
	int i =	_inicioColumnas[col-1]-1;
	int j =	_inicioColumnas[col]-1;
	return j-i;
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
