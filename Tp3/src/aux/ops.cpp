#include"mat.cpp"

uint sumarVec(Matriz mat,int x, int y, int dirx, int diry, char color){

	uint res=0;

	int cols = _Ccolumnas;
	int fils = _Cfilas;

	int i=x;
	int j=y;

	while(i<=_Ccolumnas && j<=_Ccolumnas){

		sumarcolor(mat.Posicion(i,j), res, color);

		
		
	}

	return 0;

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
	for int (i=0;i<n;i++) {
		double semiacum=yn[i];
		for (int j=0;j<n;j++) {
			if (i!=j) {
				semiacum*=(x-xn[j])/(float)(xn[i]-xn[j]);
			}
		} acum+=semiacum;
	} return acum;
}

//Probablemente no haga falta guardar xn
