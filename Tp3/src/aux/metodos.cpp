#include "ops.cpp"

//Aca van los 3 metodos enteros, usando las ops de ops.cpp

void VecinoMasCercano(Matriz& mat){
	for (int i=1;i<=mat.Cfilas()/2;i++) {
		for (int j=1;j<=mat.Ccolumnas()/2;j++) {
   		    mat.DefColor(mat.PosColor(i*2-1,j*2,'g'),i*2-1,j*2-1,'g');
		}
		for (int j=1;j<=mat.Ccolumnas()/2;j++) {
		    mat.DefColor(mat.PosColor(i*2,j*2-1,'g'),i*2,j*2,'g');
		}
	}
}

void InterpBilineal(Matriz& mat){
	for (int i=1;i<=mat.Cfilas()/2;i++) {
		for (int j=1;j<=mat.Ccolumnas()/2;j++) { //red
            unsigned int res=(mat.PosColor(i*2-1,j*2,'g')+mat.PosColor(i*2-1,j*2-2,'g')+mat.PosColor(i*2,j*2-1,'g')+mat.PosColor(i*2-2,j*2-1,'g'))/4;
            mat.DefColor(res,i*2-1,j*2-1,'g');
		}
		for (int j=1;j<=mat.Ccolumnas()/2;j++) { //blue
            unsigned int res=(mat.PosColor(i*2,j*2+1,'g')+mat.PosColor(i*2,j*2-1,'g')+mat.PosColor(i*2+1,j*2,'g')+mat.PosColor(i*2-1,j*2,'g'))/4;
            mat.DefColor(res,i*2,j*2,'g');
		}
	}
}

void InterpXDir(Matriz& mat){
	int size, pos;
	vector<int> vecDirH;
	for (int i=1;i<mat.Cfilas();i++) {
		//Fila Impar

		VecEnDir(mat, i, 2, 0, 2, 'g', vecDirH, size, pos);			

		vector<int> vecRes = interConSpline(vecDirH); //pr está en la pos 1
		for (int j = 2; j<mat.Ccolumnas()/2; j++){	//Defino el valor green para los red (con direccion horizontal) 
			mat.DefColor((unsigned int)(vecRes[j-2]), i, j*2-1,'g');
		}
		i++; //Fila Par
		VecEnDir(mat, i, 1, 0, 2, 'g', vecDirH, size, pos);
		vecRes = interConSpline(vecDirH);
		for (int j = 1; j<mat.Ccolumnas()/2; j++){	//Defino el valor green para los blue (con direccion horizontal)
			mat.DefColor((unsigned int)(vecRes[j-1]), i, j*2,'g');
		}
	}//Acá ya estan definidos todos los valores green en los b y r con la dirH
	vector<int> vecDirV;
	for (int j=1;j<mat.Ccolumnas();j++) {
		//Columna Impar
		VecEnDir(mat, 2, j, 2, 0, 'g', vecDirV, size, pos);
		vector<int> vecRes = interConSpline(vecDirV);
		for (int i = 2; i<mat.Cfilas()/2; i++){	//Defino el valor green para los red (con direccion vertical)
			int gradH=abs(((int)mat.PosColor((i*2-1),j+1,'g'))-((int)mat.PosColor((i*2-1),j-1,'g')));
			int gradV=abs(((int)mat.PosColor((i*2-1)+1,j,'g'))-((int)mat.PosColor((i*2-1)-1,j,'g')));

			int prH = (int)mat.PosColor(i*2-1, j,'g'); //blue
			int prV=(vecRes[i-2]);

//Fórmula 1
			int escala=(255-gradH)+(255-gradV);//=255*2-gradh-gradv
			int res = (((255-gradH)*prH + (255-gradV)*prV)/escala);

//Fórmula 2
//			int escala=(gradH+1)+(1+gradV);//=255*2-gradh-gradv
//			unsigned int res = (unsigned int)(((gradV+1)*prH + (gradH+1)*prV)/escala);

//Fórmula 3
//          		int res = (unsigned int)((gradV>gradH)*prH+(gradV<=gradH)*prV);
			
			saturar(res);

			mat.DefColor((unsigned int)res, i*2-1, j,'g');
		}
		j++; //columna par
		VecEnDir(mat, 1, j, 2, 0, 'g', vecDirV, size, pos);
		vecRes = interConSpline(vecDirV);
		for (int i = 1; i<mat.Cfilas()/2; i++){	//Defino el valor green para los blue (con direccion vertical)

			int gradH=abs(((int)mat.PosColor((i*2),j+1,'g'))-((int)mat.PosColor((i*2),j-1,'g')));
			int gradV=abs(((int)mat.PosColor((i*2)+1,j,'g'))-((int)mat.PosColor((i*2)-1,j,'g')));

			int prH = (int)mat.PosColor(i*2, j,'g'); //blue
			int prV = (vecRes[i-1]);

			int escala=(255-gradH)+(255-gradV);//=255*2-gradh-gradv
			int res = (((255-gradH)*prH + (255-gradV)*prV)/escala);
			
//			int escala=(gradH+1)+(1+gradV);//=255*2-gradh-gradv
//			int res = (unsigned int)(((gradV+1)*prH + (gradH+1)*prV)/escala);

//          		int res= (unsigned int)((gradV>gradH)*prH+(gradV<=gradH)*prV);
			
			saturar(res);
			
			mat.DefColor((unsigned int)res, i*2, j,'g');
		}
	}//Acá ya estan definidos todos los valores green en los b y r con las dos Dir
}

void ElDelPaper(Matriz& mat){

	float alpha=0.5;
	for (int i=1;i<=mat.Cfilas()/2;i++) {
		for (int j=1;j<=mat.Ccolumnas()/2;j++) {
            pixel pr=mat.Posicion(i*2-1,j*2-1); // rojo
            pr.green=(mat.PosColor(i*2-1,j*2,'g')+mat.PosColor(i*2-1,j*2-2,'g')+mat.PosColor(i*2,j*2-1,'g')+mat.PosColor(i*2-2,j*2-1,'g'))/4;
			pr.green+=alpha*(grad(mat,i*2-1,j*2-1,'r'));
			if ((int)(pr.green)>255) {pr.green=255;}
			if ((int)(pr.green)<0) {pr.green=0;}
            mat.Definir(pr,i*2-1,j*2-1);
		}
		for (int j=1;j<=mat.Ccolumnas()/2;j++) {
			
			
			
            pixel pb=mat.Posicion(i*2,j*2); //azul
            pb.green=(mat.PosColor(i*2,j*2+1,'g')+mat.PosColor(i*2,j*2-1,'g')+mat.PosColor(i*2+1,j*2,'g')+mat.PosColor(i*2-1,j*2,'g'))/4;
			pb.green+=alpha*(grad(mat,i*2,j*2,'b'));
			if ((int)(pb.green)>255) {pb.green=255;}
			if ((int)(pb.green)<0) {pb.green=0;}
		    mat.Definir(pb,i*2,j*2);
		}
	}
}
