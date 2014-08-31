#include <vector>
//#include "aux/Parabrisas[cpp"
#include <iostream>
#include <math.h>

using namespace std;

struct Parabrisas
{
public:

//generador basico, no se usa
Parabrisas();

//~Parabrisas();

Parabrisas(int largo, int ancho, long double h, int radio, int temp, int cantidad);

void agSanguijuela(long double x, long double y, int i);
void elimSanguijuela(int i);
void elimSanguijuelaMasCercana();
vector<long double> SangX();
vector<long double> SangY();
int largo();
int radio();
int ancho();
long double h();
int temp();
int cantidad();

private:

vector <long double> _sangx;
vector <long double> _sangy;		
int _largo;
int _ancho;
int _radio;
long double _h;
int _temp;
int _k;

};

Parabrisas::Parabrisas(){}

Parabrisas::Parabrisas(int largo, int ancho, long double h, int radio, int temp, int cantidad){
	
	vector<long double> A(cantidad);
	vector<long double> B(cantidad);
	_sangx=A;
	_sangy=B;
	_largo=largo;
	_ancho=ancho;
	_radio=radio;
	_h=h;
	_temp=temp;
	_k=cantidad;
	
}

void Parabrisas::agSanguijuela(long double x,long double y, int i) {

	_sangx[i]=x; 
	_sangy[i]=y;

}

void Parabrisas::elimSanguijuela(int i) {
	for (int j=i;j<_k;j++) {
		_sangx[i]=_sangx[i+1];
		_sangy[i]=_sangy[i+1]; //Resize es necesario?
	} _k--;
}

void Parabrisas::elimSanguijuelaMasCercana() {
	double centrox=_ancho/2;
	double centroy=_largo/2;
	double dmin=_ancho+_largo;
	double dist;
	int smin;
	for (int i=1;i<_k;i++){
		dist=sqrt(pow((_sangx[i]-centrox),2)+pow((_sangx[i]-centrox),2));
		if (dist<=dmin) {
			dmin=dist;
			smin=i;
		}
	} elimSanguijuela(smin);
}

vector <long double> Parabrisas::SangX() {

	return _sangx;

}

vector <long double> Parabrisas::SangY() {

	return _sangy;

}

int Parabrisas::largo(){

	return _largo;

}

int Parabrisas::ancho(){

	return _ancho;

}

int Parabrisas::radio(){

	return _radio;

}

long double Parabrisas::h(){

	return _h;

}

int Parabrisas::temp(){

	return _temp;

}

int Parabrisas::cantidad(){

	return _k;

}
