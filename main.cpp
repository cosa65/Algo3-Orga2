//g++ main.cpp -o main
#include <iostream>
#include "matriz.cpp"
using namespace std;
//esots tests va a haber que borrarlos, es para ver que ande bien la matriz
int main()
{
//--------------------------------------
//Test Al Pedo(andaa)

	vector<int> a(3);
	a[0] = 1;
	a[1] = 2;
	a[2] = 3;

	vector<int> b(3);
	b[0] = 4;
	b[1] = 5;
	b[2] = 6;

	vector<int> c(3);
	c[0] = 7;
	c[1] = 8;
	c[2] = 9;

	vector< vector<int> > as(3);
	
	as[0] = a;
	as[1] = b;
	as[2] = c;

	Matriz mat;

	mat = Matriz(as, 3, 2);

//---------------------------------------
	
	cout << mat.Posicion(1,1) << mat.Posicion(1,2) <<mat.Posicion(1,3) << endl;
	cout << mat.Posicion(2,1) << mat.Posicion(2,2) <<mat.Posicion(2,3) << endl;
	cout << mat.Posicion(3,1) << mat.Posicion(3,2) <<mat.Posicion(3,3) << endl;
	
//---------------------------------------

	return 0;
}
