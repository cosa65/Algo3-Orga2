#include"mat.cpp"

uint posEnVectorImaginario(Matriz mat,int posFil, int posCol, int dirfil, int dircol){
///Crucen los dedos
	int C1, C2;

	if(dirfil==1 && dircol==1){
		C1 = posCol;
		C2 = posFil;
	}

	if(dirfil==1 && dircol==-1){
		C1 = posCol;
		C2 = mat.Cfilas()+1 - posFil;
	}

	if(dirfil==-1 && dircol==1){
		C2 = posFil;
		C1 = mat.Ccolumnas()+1 - posCol;
	}

	if(dirfil==-1 && dircol==-1){
		C1 = mat.Ccolumnas()+1 - posCol;
		C2 = mat.Cfilas()+1 - posFil;
	}

	int res = C1*(C1<C2)+C2*(C2<=C1);

	return res;
}

void calcularInterp(Matriz mat,int x, int y, int dirx, int diry, char color){ //(dirx,diry) tiene las direcciones segun la matriz, no es un vector de x,y de un grafico

	uint res=0;

	int cols = mat.Ccolumnas();
	int fils = mat.Cfilas();

	int i=x;
	int j=y;

	uint XenVec = posEnVectorImaginario(mat, x, y, dirx, diry);
	uint KPAdelante = XenVec + 1 ; //arranca un punto para atras asi no calcula dos veces nada
	uint KPAtras = XenVec -1; //arranca un punto para atras asi no calcula dos veces nada

	while(i<= mat.Cfilas() && j<=mat.Ccolumnas() && i>0 && j>0){
		//sumarcolor(mat.Posicion(i,j), res, color);
		i += dirx;
		j += diry;
	}

	i = x - dirx;
	j = y - diry;

	while(i<= mat.Cfilas() && j<=mat.Ccolumnas() && i>0 && j>0){
	//sumarcolor(mat.Posicion(i,j), res, color);
		i -= dirx;
		j -= diry;
	}

// return res;

}

char color(int fila, int columna) {
    if (fila%2==0) {
        if (columna%2==0) {
            return 'B';
        } return 'G';
    } if (columna%2==0) {
        return 'G';
    } return 'R';
}

int evaluareninterpolante(int x, vector<int> xn, vector<int> yn) {
	int n=xn.size();
	int acum=0;
	for (int i=0;i<n;i++) {
		double semiacum=yn[i];
		for (int j=0;j<n;j++) {
			if (i!=j) {
				semiacum*=(x-xn[j])/(float)(xn[i]-xn[j]);
			}
		} acum+=semiacum;
	} return acum;
}

//Probablemente no haga falta guardar xn
