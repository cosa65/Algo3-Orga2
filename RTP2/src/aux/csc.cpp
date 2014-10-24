#include "csc.h"
#include <vector>
#include <iostream>

using namespace std;

typedef vector<double> Columna;

//generador basico, no se usa
MatrizE::MatrizE(){}

//~Matriz();

//generador que te crea una matriz de un tamaño, no pide vectores

MatrizE::MatrizE(long int Ccolumnas, long int Cfilas){
	_Ccolumnas = Ccolumnas;
	_Cfilas = Cfilas;
	_inicioColumnas.resize(Ccolumnas+1);
	for (long int i = 0; i<=_Ccolumnas; i++){_inicioColumnas[i]=0;}
}

void MatrizE::Definir(double adefinir, long int fila, long int columna) {
	if (adefinir>0) {
		long int size = _valores.size()+1;

		_valores.resize(size);
		_posValores.resize(size);

		long int i = _inicioColumnas[columna];
		long int j = _inicioColumnas[columna+1];
		long int lugar=j;
		for (long int k=i;k<j+1;k++) {
			if (_posValores[k]>fila) {
				lugar=k;
				k=j+1;	
			}
		} 
	
		for (long int k=size-1;k>lugar;k--) {
			_valores[k]=_valores[k-1];
			_posValores[k]=_posValores[k-1];		
		} _valores[lugar]=adefinir;
		_posValores[lugar]=fila;

		for (long int i=columna+1;i<=_Ccolumnas;i++) {
			_inicioColumnas[i]++;
		}
	} 
}

void MatrizE::DefinirCol(long int col, vector<long int>* filas) {
	long int cant = filas->size();
	long int size = _valores.size()+cant;

	_valores.resize(size);
	_posValores.resize(size);

	long int i = _inicioColumnas[col];
	long int j = _inicioColumnas[col+1];

	for (long int k=size-1;k>j+cant;k--) {
		_valores[k]=_valores[k-cant];
		_posValores[k]=_posValores[k-cant];		
	} 

	for (long int k=0;k<cant;k++) {
		_valores[i+k]=1;
		_posValores[i+k]=(*filas)[k];
	}

	for (long int i=col+1;i<=_Ccolumnas;i++) {
		_inicioColumnas[i]+=cant;
	}	
}

double MatrizE::Posicion(long int fila, long int columna) {

	long int i = _inicioColumnas[columna];

	long int j = _inicioColumnas[columna+1];

	for (long int k=i;k<j;k++) {
		if (_posValores[k]==fila) {
			return _valores[k];
		}
	} return 0;
}

long int MatrizE::Cfilas(){
	return _Cfilas;
}

long int MatrizE::Ccolumnas(){
	return _Ccolumnas;
}

void MatrizE::mostrar(){
	for (long int i=0;i<_Cfilas;i++) {
		for (long int j=0;j<_Ccolumnas;j++) {
			cout << Posicion(i,j) << " ";
		} cout << endl;
	}
}

void MatrizE::divColCte(long int col, double cte){
	long int i = _inicioColumnas[col];
	long int j = _inicioColumnas[col+1];
	for (long int k=i;k<j;k++) {
		_valores[k]=_valores[k]/cte;
	} 
}

long int MatrizE::contarCol(long int col){
	long int i = _inicioColumnas[col];
	long int j = _inicioColumnas[col+1];
	return j-i;
}

double MatrizE::contarFila(long int fila){
	double suma =0;
	for (long int i=0; i<_Ccolumnas; i++){
		if (_posValores[i]==fila){
			suma+=_valores[i];
		}
	}
	return suma;
}

vector<double> MatrizE::Producto (vector<double>* x) {
	long int tam=x->size();
	vector<double> res(tam);
	for (long int i=0;i<tam;i++) {
		res[i]=0;
	}
	for (long int k=0;k<_Ccolumnas;k++) {
		for (long int i=_inicioColumnas[k];i<_inicioColumnas[k+1];i++) {
			res[_posValores[i]]+=_valores[i]*(*x)[k];
		}
	}
 return res;
}

vector<double> MatrizE::Ptransp (vector<double>* x) { //transpuesto, no transepsual
	long int tam=x->size();
	vector<double> res(tam);
	for (long int k=0;k<_Ccolumnas;k++) {
		double suma=0;
		for (long int i=_inicioColumnas[k];i<_inicioColumnas[k+1];i++) {
			suma+=_valores[i]*(*x)[_posValores[i]];
		} res[k]=suma;
	} return res;
}
