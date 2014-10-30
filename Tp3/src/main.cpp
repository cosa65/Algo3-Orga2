#include <iostream>
#include <ctime>
#include "aux/matriz.h"

using namespace std;

int main(){
	/*clock_t t;
	t = clock();
	ofstream tiempo;
	t = clock() - t;
	tiempo.open("Tiempo");
	tiempo << "Clocks: "<< (long int)t << " segundos: " << ((float)t)/CLOCKS_PER_SEC << endl;*/
	pixel p;
	Matriz m(20,10);
	for (int i=0;i<20;i++) {
		for (int j=0;j<10;j++) {
			p.green=(i+j)*10;
			p.red=i*10;
			p.blue=j*10;
			m.Definir(p,i+1,j+1);
		}
	} m.mostrar();
	m.IBilinealG();
	//m.IBilinealRB();
	m.mostrar();
	return 0;
}




