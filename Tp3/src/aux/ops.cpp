#include"mat.cpp"

uint posEnVectorImaginario(Matriz& mat,int posFil, int posCol, int dirfil, int dircol, int &primfil, int &primcol){

	int C, F, res;

	if (dirfil!=0 && dircol !=0){

		if (dircol>0){
			C = posCol/dircol; 
		} else {
			C = (mat.Ccolumnas()+1 - posCol)/(-dircol);
		} if (dirfil>0) {
			F = posFil/dirfil;
		} else {
			F = (mat.Cfilas() +1 - posFil)/(-dirfil);
		}
		
		int res = C*(C<F) + F*(F<=C);

		primfil = posFil - dirfil*(res-1);
		primcol = posCol - dircol*(res-1);


	} else {

		if (dirfil==0 && dircol>0){
			res = posCol/dircol;
			primfil = posFil;
			primcol = 1;
		}
		if (dirfil==0 && dircol<0){
			res = (mat.Ccolumnas()+1)/(-dircol);
			primfil = posFil;
			primcol = mat.Ccolumnas();
		}
		if (dirfil>0 && dircol==0){
			res = posFil/dirfil;
			primfil = 1;
			primcol = posCol;
		}
		if (dirfil<0 && dircol==0){
			res = (mat.Cfilas()+1)/(-dirfil);
			primfil = mat.Cfilas();
			primcol = posCol;
		}
	}
	return res;		
}

void VecEnDir(Matriz& mat,int fil, int col, int dirfil, int dircol, char color, vector<uint>& vecres, int &size, int &pos){

	int i, j;

	pos = posEnVectorImaginario(mat, fil, col, dirfil, dircol, i, j);

	if (dirfil==0){
		size=((mat.Ccolumnas()+1)-1)/dircol;
	} else if (dircol==0) {
		size=((mat.Cfilas()+1)-1)/dirfil;
	} else {
		int sizef=((mat.Cfilas()+1)-1)/dirfil;
		int sizec=((mat.Ccolumnas()+1)-1)/dircol;
		size=sizef*(sizef<sizec)+sizec*(sizec<=sizef);
	}
	size=(-(size<0)+(size>=0))*size;
	
	vecres.resize(size);
	
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

int evaluarEnInterLagrange(int x, vector<uint>& xn, vector<uint>& yn) {
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

float grad(Matriz& mat, int i, int j, char color) {
	float res=0;
	if (color=='r') {
		res+=mat.Posicion(i+2,j).red;
		res+=mat.Posicion(i-2,j).red;
		res+=mat.Posicion(i,j+2).red;
		res+=mat.Posicion(i,j-2).red;
		return mat.Posicion(i,j).red-res/4;
	} else if (color == 'b') {
		res+=mat.Posicion(i+2,j).blue;
		res+=mat.Posicion(i-2,j).blue;
		res+=mat.Posicion(i,j+2).blue;
		res+=mat.Posicion(i,j-2).blue;
		return mat.Posicion(i,j).blue-res/4;
	} else {
		cout << "Error" << endl;
	} return 0;
}
