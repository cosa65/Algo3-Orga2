#include "csc.h"
#include <vector>
#include <iostream>

using namespace std;

typedef vector<double> Columna;

//generador basico, no se usa
MatrizE::MatrizE(){}

//~Matriz();

//generador que te crea una matriz de un tamaño, no pide vectores

MatrizE::MatrizE(int Ccolumnas, int Cfilas){
	_Ccolumnas = Ccolumnas;
	_Cfilas = Cfilas;
	_inicioColumnas.resize(Ccolumnas+1);
	for (int i = 0; i<=_Ccolumnas; i++){_inicioColumnas[i]=1;}
}

void MatrizE::Definir(double adefinir, int fila, int columna) {
	if (adefinir>0) {
		int size = _valores.size()+1;

		_valores.resize(size);
		_posValores.resize(size);

		int i =	_inicioColumnas[columna-1]-1;
		int j = _inicioColumnas[columna];
		int lugar=j-1;
		for (int k=i;k<j;k++) {
			if (_posValores[k]>fila) {
				lugar=k;
				k=j;	
			}
		} 
	
		for (int k=size-1;k>lugar;k--) {
			_valores[k]=_valores[k-1];
			_posValores[k]=_posValores[k-1];		
		} _valores[lugar]=adefinir;
		_posValores[lugar]=fila;

		for (int i=columna;i<=_Ccolumnas;i++) {
			_inicioColumnas[i]++;
		}
	} 
}

void MatrizE::DefinirCol(double adefinir, int columna) {
	if (adefinir>0) {

		int size = _valores.size()+_Cfilas;

		_valores.resize(size);
		_posValores.resize(size);

		int i =	_inicioColumnas[columna-1]-1;
		int j = _inicioColumnas[columna]-1;
	
		for (int k=size-1;k>j+_Cfilas-1;k--) {
			_valores[k]=_valores[k-_Cfilas];
			_posValores[k]=_posValores[k-_Cfilas];		
		} 

		for (int k=0;k<_Cfilas;k++) {
			_valores[i+k]=adefinir;
			_posValores[i+k]=k+1;
		}
		for (int k=columna;k<=_Ccolumnas;k++) {
			_inicioColumnas[k]+=_Cfilas;

		}
	} 
}


double MatrizE::Posicion(int fila, int columna) {

	int i =	_inicioColumnas[columna-1]-1;

	int j =	_inicioColumnas[columna]-1;

	for (int k=i;k<j;k++) {
		if (_posValores[k]==fila) {
			return _valores[k];
		}
	} return 0;
}

int MatrizE::Cfilas(){
	return _Cfilas;
}

int MatrizE::Ccolumnas(){
	return _Ccolumnas;
}

void MatrizE::mostrar(){
	for (int i=1;i<=_Cfilas;i++) {
		for (int j=1;j<=_Ccolumnas;j++) {
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

double MatrizE::contarFila(int fila){
	double suma =0;
	for (int i=0; i<_Ccolumnas; i++){
		if(_posValores[i]==fila){
			suma+=_valores[i];
		}
	}
	return suma;
}

vector<double> MatrizE::Producto (vector<double> x) {
	int tam=x.size();
	vector<double> res(tam);
	for (int i=0;i<tam;i++) {
		res[i]=0;
	}
	for (int k=0;k<_Ccolumnas;k++) {
		for (int i=_inicioColumnas[k];i<_inicioColumnas[k+1];i++) {
			res[_posValores[i-1]-1]+=_valores[i-1]*x[k];
		}
	}
 return res;
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
