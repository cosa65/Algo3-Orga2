#include <iostream>
#include "matriz.cpp"
using namespace std;
//esots tests va a haber que borrarlos, es para ver que ande bien la matriz
int main()
{
//--------------------------------------
//Test Al Pedo(andaa)

	vector<int> a(3);
	a[1] = 1;
	a[2] = 2;
	a[3] = 3;

	vector<int> b(3);
	b[4];
	b[5];
	b[6];

	vector<int> c(3);
	b[7];
	b[8];
	b[9];

	vector< vector<int> > as(9);
	
	as[1] = a;
	as[2] = b;

	Matriz mat;

	mat = Matriz(as, 3, 2);

//---------------------------------------
	
	cout << mat.Posicion(1,1) << mat.Posicion(1,2) <<mat.Posicion(1,3) << endl;
	cout << mat.Posicion(2,1) << mat.Posicion(2,2) <<mat.Posicion(2,3) << endl;
	//cout << mat.Posicion(3,1) << mat.Posicion(3,2) <<mat.Posicion(3,3) << endl;
	
//---------------------------------------

	return 0;
}
