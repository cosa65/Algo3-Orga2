Datos cargar(char* in) {
	ifstream archivo;
	archivo.open(in);
	int metodo;
	double c;
	int tipo
	string path;
	double tolerancia;
    	archivo >> metodo;
	archivo >> c;
	archivo >> tipo;
	archivo >> path;
	archivo >> tolerancia;
	Datos d=Datos(metodo,c,tipo,path,tolerancia)
	return d;
}

Matriz Generar(Datos d) {
	ifstream archivo;
	archivo.open(d.path());
	string basura;
	getline (archivo, basura);
	getline (archivo, basura);
	getline (archivo, basura); //acá está m y n en realidad
	getline (archivo, basura);
	
	double src; double dst;
	Matriz mat=Matriz(n,n);
	for (int i=0;i<mat;i++) {
		archivo >> src;
		archivo >> dst;
		mat.Definir(src,dst,1);
	} return mat;
}
