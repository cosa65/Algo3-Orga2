//g++ main.cpp -o main
#include <iostream>
#include <fstream>
#include "matriz.cpp"
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

bool determinado (Matriz m, int x, int y) {
	return true;
}

Matriz cargar() {
    ifstream test;
    string input = "";
    cout << "  Ingrese nombre de test existente: ";
    getline(cin, input);
    test.open(input.c_str());
    int anchoParab;
	int largoParab;
	int h;
    test >> anchoParab;
	test >> largoParab;
	test >> h;
	int ancho=(anchoParab/h)+1;
	int largo=(anchoParab/h)+1;
	Matriz m=Matriz(ancho*largo,ancho*largo);
	int radio;
	test >> radio;
	cout << endl << "radio:" <<radio << endl;	//esto sale despues
	double Temp;
	test >> Temp;
	cout << "Temp:" << Temp << endl;			//esto sale despues
	int cant;
	test >> cant;
	cout << "cant:" << cant << endl;			//esto sale despues
	double Posx[cant];
	double Posy[cant];
	for (int i=0;i<cant;i++) {
		test >> Posx[i];
		Posx[i]=Temp; 			//X de las sanguijuelas
		test >> Posy[i];
		Posy[i]=Temp; 			//Y de las sanguijuelas
	}


	for (int i=1;i<=ancho*largo;i++) {
	int y=(i-1)/ancho+1; 	// x e y son el lugar del vector incógnita al que corresponde la fila i
	int x;
	if (i%ancho==0) {x = ancho;} else {x=i%ancho;}
	if (determinado(m,x,y)) {
		for (int j=1;j<=ancho*largo;j++) {
			if (i==j) {
                   cout << i;
                   cout << j;
				m.Definir(1,i,j);
			} else {
				m.Definir(0,i,j);
			}
		}
	} 	else {
		for (int j=1;j<=ancho*largo;j++) {
			if (i==j) {
				m.Definir(-1,i,j);
			} else if (i==j-1 || i==j+1 || i-j==ancho-1 || i-j==ancho-2) {
				m.Definir(0.25,i,j);
			} else {
				m.Definir(0,i,j);
			}
		}
		} m.mostrar(); return m;
	}
}


int main()
{
	cargar();
	return 0;
}
