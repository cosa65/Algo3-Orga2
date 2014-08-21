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

	mat = Matriz(as, 3, 3, a);

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

	













	

