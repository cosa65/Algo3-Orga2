#include"mat.cpp"

uint posEnVectorImaginario(Matriz mat,int posFil, int posCol, int dirfil, int dircol, int &primfil, int &primcol){
///Crucen los dedos
	int C, F;

	if(dirfil==1 && dircol==1){
		C = posCol;
		F = posFil;
	}

	if(dirfil==-1 && dircol==1){
		C = posCol;
		F = mat.Cfilas()+1 - posFil;
	}

	if(dirfil==1 && dircol==-1){
		F = posFil;
		C = mat.Ccolumnas()+1 - posCol;
	}

	if(dirfil==-1 && dircol==-1){
		C = mat.Ccolumnas()+1 - posCol;
		F = mat.Cfilas()+1 - posFil;
	}


	int res = C*(C<F) + F*(F<=C);

	primfil = posFil - dirfil*res+dirfil;
	cout << res << endl;
	cout << "primfil " << primfil << endl;

	primcol = posCol - dircol*res+dircol;

	cout << "primcol " << primcol << endl;

	return res;					
}

void VecEnDir(Matriz mat,int col, int fil, int dirfil, int dircol, char color, vector<uint> &vecres, int &size, int &pos){

	int i, j;

	pos = posEnVectorImaginario(mat, col, fil, dirfil, dircol, i, j);

	if(mat.Ccolumnas() > mat.Cfilas()){
		vecres.resize(mat.Ccolumnas());
	} else {
		vecres.resize(mat.Cfilas());
	}
	
	int posVec = 0;

	while(i<= mat.Cfilas() && j<=mat.Ccolumnas() && i>0 && j>0){

		vecres[posVec] = mat.PosColor(i,j,color);

		i+=dirfil;
		j+=dircol; 

		posVec++;

	}

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
