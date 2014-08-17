//g++ main.cpp -o main
#include <iostream>
#include "matriz.cpp"
using namespace std;


//podria ir como una operacion de Matriz esta, pero como en realidad es algo que esta mas relacionado con la EG me parecio ponerlo mejor aca, pero si despues optimizamos seria mejor moverla a la struct

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
//estos tests va a haber que borrarlos, es para ver que ande bien la matriz
int main()
{
//--------------------------------------
//Test crear matrices

	vector<double> a(3);
	a[0] = 1;
	a[1] = 2;
	a[2] = 3;

	vector<double> b(3);
	b[0] = 4;
	b[1] = 5;
	b[2] = 6;

	vector<double> c(3);
	c[0] = 7;
	c[1] = 8;
	c[2] = 9;

	vector< vector<double> > as(3);
	
	as[0] = a;
	as[1] = b;
	as[2] = c;

	Matriz mat;

	mat = Matriz(as, 3, 3);

//---------------------------------------
cout<< endl <<"test observador posicion (las posiciones se cuentan desde 1)";
	cout << mat.Posicion(1,1) << mat.Posicion(1,2) <<mat.Posicion(1,3) << endl;
	cout << mat.Posicion(2,1) << mat.Posicion(2,2) <<mat.Posicion(2,3) << endl;
	cout << mat.Posicion(3,1) << mat.Posicion(3,2) <<mat.Posicion(3,3) << endl;
	
//---------------------------------------
cout << endl <<"test definir";
	mat.Definir(2,1,1);
	cout << endl << "definir la pos 1,1 nueva como:" << mat.Posicion(1,1) << endl;
	mat.Definir(1,1,1);

//---------------------------------------
cout << endl << "test observadores simples";

	cout << "filas: " << mat.Cfilas() << endl << "columnas: " << mat.Ccolumnas() << endl << "tamaño: " << mat.TamTotal() << endl;

//---------------------------------------
cout << endl <<"test intercambiarFilas" ;

	mat.intercambiarFilas(2, 1);
	cout << endl << mat.Posicion(1,1) << mat.Posicion(1,2) <<mat.Posicion(1,3) << endl;
	cout << endl << mat.Posicion(2,1) << mat.Posicion(2,2) <<mat.Posicion(2,3) << endl;

	mat.intercambiarFilas(2, 1);

//---------------------------------------
//cout << endl << "test restarFilas, anda pero quiero tener la mat como antes" ;

	

	/*mat.restarFilas(2, 1, 1);
	cout << endl << mat.Posicion(1,1) << mat.Posicion(1,2) <<mat.Posicion(1,3) << endl;
	cout << endl << mat.Posicion(2,1) << mat.Posicion(2,2) <<mat.Posicion(2,3) << endl;*/


//---------------------------------------
cout << endl <<"test EliminacionGaussiana"<< endl;

	mat = 	EliminacionGaussiana(mat);
	
	cout << mat.Posicion(1,1) << mat.Posicion(1,2) <<mat.Posicion(1,3) << endl;
	cout << mat.Posicion(2,1) << mat.Posicion(2,2) <<mat.Posicion(2,3) << endl;
	cout << mat.Posicion(3,1) << mat.Posicion(3,2) <<mat.Posicion(3,3) << endl;

//---------------------------------------















	

	return 0;
}
