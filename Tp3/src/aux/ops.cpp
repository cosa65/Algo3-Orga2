#include"mat.cpp"

uint posEnVectorImaginario(Matriz mat,int posFil, int posCol, int dirfil, int dircol, int &primfil, int &primcol){

	int C, F, res;

	if (dirfil!=0 && dircol !=0){

		if(dircol>0){
			C = posCol; //si quisiera meter dircol>1, podría poner int C =pos/dircol redondeado para abajo?
		} else {
			C = mat.Ccolumnas()+1 - posCol;
		} if (dirfil>0) {
			F = posFil;
		} else {
			F = mat.Cfilas() +1 - posFil;
		}
		int res = C*(C<F) + F*(F<=C);

		primfil = posFil - dirfil*res+dirfil;

		primcol = posCol - dircol*res+dircol;


	} else {

		if(dirfil==0 && dircol==1){
			res = posCol;
			primfil = posFil;
			primcol = 1;

		}

		if(dirfil==0 && dircol==-1){
			res = posCol;
			primfil = posFil;
			primcol = mat.Ccolumnas();
		}

		if(dirfil==1 && dircol==0){
			res = posFil;
			primfil = 1;
			primcol = posCol;
		}

		if(dirfil==-1 && dircol==0){
			res = posFil;
			primfil = mat.Cfilas();
			primcol = posCol;
		}
	}
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
