#include <iostream>
#include "matriz.cpp"
using namespace std;

int main()
{
//--------------------------------------
//Test Al Pedo(andaa)

	vector<int> a (3);
	a[1] = 1;
	a[2] = 2;
	a[3] = 3;

	vector<int> b (3);
	b[4];
	b[5];
	b[6];

	vector<int> c (3);
	b[7];
	b[8];
	b[9];

	vector< vector<int> > as (3);
	
	as[1] = a;
	as[2] = b;

	Matriz(as, 3, 2);

	//cout<< as[1][1] << endl;
//---------------------------------------


	return 0;
}
