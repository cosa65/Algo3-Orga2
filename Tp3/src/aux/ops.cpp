#include"mat.cpp"

bool xFilaEsMejor(Matriz mat, int posFil, int posCol, char color){

	uint xfila = abs(mat.sumaDePoses(posFil,posCol-2,color) - mat.sumaDePoses(posFil,posCol+2,color)); 
	uint xcolumna = abs(mat.sumaDePoses(posFil-2,posCol,color) - mat.sumaDePoses(posFil+2,posCol,color));

	return xfila <= xcolumna;
}

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
			primcol = posCol%dircol;
			if (primcol==0) {primcol=dircol;}
		}
		if (dirfil==0 && dircol<0){
			res = (mat.Ccolumnas()+1)/(-dircol);
			primfil = posFil;
			primcol = mat.Ccolumnas();
		}
		if (dirfil>0 && dircol==0){
			res = posFil/dirfil;
			primfil = posFil%dirfil;
			primcol = posCol;
			if (primfil==0) {primfil=dirfil;}
		}
		if (dirfil<0 && dircol==0){
			res = (mat.Cfilas()+1)/(-dirfil);
			primfil = mat.Cfilas();
			primcol = posCol;
		}
	}
	return res;		
}

void VecEnDir(Matriz& mat,int fil, int col, int dirfil, int dircol, char color, vector<int>& vecres, int &size, int &pos){

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

vector<int> interConSpline(vector<int> vecA){

	int n = vecA.size();
	//vector<uint> vecH (n); COMO ES DE TODOS 2 NO HACE FALTA (STEP 1)
	vector<double> vecAlpha (n);
	for (int i = 1; i < n-1; i++){	//(STEP 2)
		vecAlpha[i] = (3/2) * (double)(vecA[i+1]- vecA[i]) - (3/2) * (double)(vecA[i] - vecA[i-1]);
	}
	vector<double> vecL (n);		//(STEP 3)
	vector<double> vecU (n);
	vector<double> vecZ (n);
	vecL[0] = 1;
	vecU[0] = 0;
	vecZ[0] = 0;
	for (int i = 1; i < n-1; i++){	//(STEP 4)
		vecL[i] = 8 - 2 * vecU[i-1];	//2 * (X_i+1 - X_i-1) = 8	y	H_i-1 = 1
		vecU[i] = 2/vecL[i];		//H_i = 1
		vecZ[i] = (vecAlpha[i] - 2 * vecZ[i-1])/vecL[i];
	}
	vecL[n-1] = 1;		//(STEP 5) En el burden llama n al X_n, pero aca es el tamaño asi q el n seria n-1.
	vecZ[n-1] = 0;
	vector<double> vecB (n);
	vector<double> vecD (n);
	vector<double> vecC (n);
	vecC[n-1] = 0;
	for (int i = n-2; i > -1; i--){	//(STEP 6)
		vecC[i] = vecZ[i] - vecU[i] * vecC[i+1];
		vecB[i] = (double)(vecA[i+1] - vecA[i])/2 - 2*(vecC[i+1]+2*vecC[i])/3;
		vecD[i] = (vecC[i+1] - vecC[i])/6;
	}
	vector<int> vecRes (n-1);//(STEP 7)!
	for (int i = 0; i < n-1; i++){
		vecRes[i] = vecA[i] + vecB[i] + vecC[i] + vecD[i]; //x-xj=1
	}
	return vecRes;
}

int evaluarEnInterLagrange(int x, vector<uint>& xn, vector<uint>& yn) {
	int n=xn.size();
	int acum=0;
	for (int i=0;i<n;i++) {
		double semiacum=yn[i];
		for (int j=0;j<n;j++) {
			if (i!=j) {
				semiacum*=(x-xn[j])/((float)(xn[i])-(float)(xn[j]));
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

void IBilinealRB(Matriz& mat) {
	for (int i=1;i<=mat.Cfilas()/2;i++) {
		for (int j=1;j<=mat.Ccolumnas()/2;j++) {
            pixel pr=mat.Posicion(i*2-1,j*2-1); // rojo
            pixel pg=mat.Posicion(i*2-1,j*2); //verde
            pr.blue=(mat.Posicion(i*2,j*2).blue+mat.Posicion(i*2-2,j*2-2).blue+mat.Posicion(i*2-2,j*2).blue+mat.Posicion(i*2,j*2-2).blue)/4;
            mat.Definir(pr,i*2-1,j*2-1);
            pg.red=(pr.red+mat.Posicion(i*2-1,j*2+1).red)/2;
            pg.blue=(mat.Posicion(i*2,j*2).blue+mat.Posicion(i*2-2,j*2).blue)/2;
	        mat.Definir(pg,i*2-1,j*2);
		}
		for (int j=1;j<=mat.Ccolumnas()/2;j++) {
            pixel pg=mat.Posicion(i*2,j*2-1); // verde
            pixel pb=mat.Posicion(i*2,j*2); //azul
            pg.blue=(pb.blue+mat.Posicion(i*2,j*2-2).blue)/2;
            pg.red=(mat.Posicion(i*2-1,j*2-1).red+mat.Posicion(i*2+1,j*2-1).red)/2;
            mat.Definir(pg,i*2,j*2-1);
            pb.red=(mat.Posicion(i*2-1,j*2-1).red+mat.Posicion(i*2+1,j*2+1).red+mat.Posicion(i*2-1,j*2+1).red+mat.Posicion(i*2+1,j*2-1).red)/4;
            mat.Definir(pb,i*2,j*2);
		}
	}
}
