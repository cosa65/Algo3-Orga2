vector<double> Potencias (Matriz &A, vector<double> xi, double tolerancia) {
	double autoval=0; double delta=tolerancia+1;
	for (int i=0;delta>tolerancia;i++) {
		autoval=Norma1(xi);
		porCte(xi,1/autoval);
		vector<double> ximas1=A.Producto(xi);
		for (unsigned int j=0;j<xi.size();j++) {
			xi[j]=xi[j]-ximas1[j];
		}
		delta=Norma2(xi);
		cout << autoval << '\t' << delta << endl;
		xi=ximas1;
	} 
	return xi;
} 


vector<double> pageRank(Datos& d) {
	MatrizE& matre=d._links; //deja de ser esparsa, hay que mirar el paper que no miré (kanvar) para ver qué onda eso
	int n=matre.Cfilas(); 
	int suma; //Actualizar matriz según algoritmo:
	for (int i=1;i<=n;i++) { //En cada columna, calcular el grado y dividir cada elemento por él
		suma=matre.contarCol(i);
		if (suma>0) {
			matre.divColCte(i,suma);
		} else {
			matre.DefinirCol(1/(float)n,i); //asignar 1/n a todas las filas de los que tienen grado 0
		}
				
	} Matriz mat(n,n);
	for (int i=1;i<=n;i++) { //multiplicar toda la matriz por c y sumarle (1-c)/n
		for (int j=1;j<=n;j++) {
			mat.Definir(matre.Posicion(i,j)*d._c+(1-d._c)/n,i,j);
		} 				
	} 
	vector<double> res(mat.Cfilas());
	for (unsigned int i=0;i<res.size();i++) {res[i]=1;}
	res=Potencias(mat,res,d._tolerancia);
	return res;
}
