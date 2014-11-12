#include "ops.cpp"

//Aca van los 3 metodos enteros, usando las ops de ops.cpp

void VecinoMasCercano(Matriz& mat){
	for (int i=1;i<=mat.Cfilas()/2;i++) {
		for (int j=1;j<=mat.Ccolumnas()/2;j++) {
		    pixel pr=mat.Posicion(i*2-1,j*2-1); // rojo
		    pixel pg=mat.Posicion(i*2-1,j*2); //verde
		    pr.green=pg.green;
		    mat.Definir(pr,i*2-1,j*2-1);
		}
		for (int j=1;j<=mat.Ccolumnas()/2;j++) {
		    pixel pg=mat.Posicion(i*2,j*2-1); // verde
		    pixel pb=mat.Posicion(i*2,j*2); //azul
		    pb.green=pg.green;
		    mat.Definir(pb,i*2,j*2);
		}
	}
}

void InterpBilineal(Matriz& mat){
	for (int i=1;i<=mat.Cfilas()/2;i++) {
		for (int j=1;j<=mat.Ccolumnas()/2;j++) {
            pixel pr=mat.Posicion(i*2-1,j*2-1); // rojo
            pr.green=(mat.Posicion(i*2-1,j*2).green+mat.Posicion(i*2-1,j*2-2).green+mat.Posicion(i*2,j*2-1).green+mat.Posicion(i*2-2,j*2-1).green)/4;
            mat.Definir(pr,i*2-1,j*2-1);
		}
		for (int j=1;j<=mat.Ccolumnas()/2;j++) {
            pixel pb=mat.Posicion(i*2,j*2); //azul
            pb.green=(mat.Posicion(i*2,j*2+1).green+mat.Posicion(i*2,j*2-1).green+mat.Posicion(i*2+1,j*2).green+mat.Posicion(i*2-1,j*2).green)/4;
            mat.Definir(pb,i*2,j*2);
		}
	}
}
/*
void interXDirBis(Matriz &mat){

	for (int i=1;i<mat.Cfilas();i++) {
		//Fila Impar
		if(xFilaEsMejor(i,2,'g')){
			VecEnDir(mat, i, 2, 0, 2, 'g', vecDirH, size, pos);
		} else {
			VecEnDir(mat, i, 2, 2, 0, 'g', vecDirH, size, pos);			
		}

		vector<int> vecRes = interConSpline(vecDirH); //pr está en la pos 1
		for (int j = 2; j<mat.Ccolumnas()/2; j++){	//Defino el valor green para los red (con direccion horizontal) 
			pixel pr = mat.Posicion(i, j*2-1); //rojo
			pr.green = (unsigned int)(vecRes[j-2])/2;
			if (pr.green<10) {cout << '(' << i << ',' << j*2-1 << ')';}
			mat.Definir(pr, i, j*2-1);
		}
		i++; //Fila Par
		if(xFilaEsMejor(i,1,'g')){
			VecEnDir(mat, i, 1, 0, 2, 'g', vecDirH, size, pos);
		} else {
			VecEnDir(mat, i, 1, 2, , 'g', vecDirH, size, pos);
		}
		vecRes = interConSpline(vecDirH);
		for (int j = 1; j<mat.Ccolumnas()/2; j++){	//Defino el valor green para los blue (con direccion horizontal)
			pixel pb = mat.Posicion(i, j*2); //blue
			pb.green = (unsigned int)(vecRes[j-1])/2;
			mat.Definir(pb, i, j*2);
		}
	}
}*/
void InterpXDir(Matriz& mat){
	int size, pos;
	vector<int> vecDirH;
	for (int i=1;i<mat.Cfilas();i++) {
		//Fila Impar

		VecEnDir(mat, i, 2, 0, 2, 'g', vecDirH, size, pos);			

		vector<int> vecRes = interConSpline(vecDirH); //pr está en la pos 1
		for (int j = 2; j<mat.Ccolumnas()/2; j++){	//Defino el valor green para los red (con direccion horizontal) 
			pixel pr = mat.Posicion(i, j*2-1); //rojo
			pr.green = (unsigned int)(vecRes[j-2]);
			mat.Definir(pr, i, j*2-1);
		}
		i++; //Fila Par
		VecEnDir(mat, i, 1, 0, 2, 'g', vecDirH, size, pos);
		vecRes = interConSpline(vecDirH);
		for (int j = 1; j<mat.Ccolumnas()/2; j++){	//Defino el valor green para los blue (con direccion horizontal)
			pixel pb = mat.Posicion(i, j*2); //blue
			pb.green = (unsigned int)(vecRes[j-1]);
			mat.Definir(pb, i, j*2);
		}
	}//Acá ya estan definidos todos los valores green en los b y r con la dirH
	vector<int> vecDirV;
	for (int j=1;j<mat.Ccolumnas();j++) {
		//Columna Impar
		VecEnDir(mat, 2, j, 2, 0, 'g', vecDirV, size, pos);
		vector<int> vecRes = interConSpline(vecDirV);
		for (int i = 2; i<mat.Cfilas()/2; i++){	//Defino el valor green para los red (con direccion vertical)
			int gradH=abs(((int)mat.Posicion((i*2-1),j+1).green)-((int)mat.Posicion((i*2-1),j-1).green));
			int gradV=abs(((int)mat.Posicion((i*2-1)+1,j).green)-((int)mat.Posicion((i*2-1)-1,j).green));
			pixel pr = mat.Posicion(i*2-1, j); //rojo

			int prH=(int)pr.green;
			int prV=(vecRes[i-2]);

//Fórmula Espineta (da 39,74)
			int escala=(255-gradH)+(255-gradV);//=255*2-gradh-gradv
			pr.green = (unsigned int)(((255-gradH)*prH + (255-gradV)*prV)/escala);

//Fórmula Rouli (da 39,84)
//			int escala=(gradH+1)+(1+gradV);//=255*2-gradh-gradv
//			pr.green = (unsigned int)(((gradV+1)*prH + (gradH+1)*prV)/escala);

//Quedándose con el mejor (da 39,29, aunque el cuello del loro queda mejor)
//          pr.green = (unsigned int)((gradV>gradH)*prH+(gradV<=gradH)*prV);
			
			if ((int)(pr.green)>255) {pr.green=255;}
			if ((int)(pr.green)<0) {pr.green=0;}

			mat.Definir(pr, i*2-1, j);
		}
		j++; //columna par
		VecEnDir(mat, 1, j, 2, 0, 'g', vecDirV, size, pos);
		vecRes = interConSpline(vecDirV);
		for (int i = 1; i<mat.Cfilas()/2; i++){	//Defino el valor green para los blue (con direccion vertical)

			int gradH=abs(((int)mat.Posicion((i*2),j+1).green)-((int)mat.Posicion((i*2),j-1).green));
			int gradV=abs(((int)mat.Posicion((i*2)+1,j).green)-((int)mat.Posicion((i*2)-1,j).green));
			pixel pb = mat.Posicion(i*2, j); //blue

			int prH=(int)pb.green;
			int prV=(vecRes[i-1]);

			int escala=(255-gradH)+(255-gradV);//=255*2-gradh-gradv
			pb.green = (unsigned int)(((255-gradH)*prH + (255-gradV)*prV)/escala);
			
//			int escala=(gradH+1)+(1+gradV);//=255*2-gradh-gradv
//			pb.green = (unsigned int)(((gradV+1)*prH + (gradH+1)*prV)/escala);


//          pb.green = (unsigned int)((gradV>gradH)*prH+(gradV<=gradH)*prV);
			
			if ((int)(pb.green)>255) {pb.green=255;}
			if ((int)(pb.green)<0) {pb.green=0;}
			mat.Definir(pb, i*2, j);
		}
	}//Acá ya estan definidos todos los valores green en los b y r con las dos Dir
}

void ElDelPaper(Matriz& mat){

	float alpha=0.5;
	for (int i=1;i<=mat.Cfilas()/2;i++) {
		for (int j=1;j<=mat.Ccolumnas()/2;j++) {
            pixel pr=mat.Posicion(i*2-1,j*2-1); // rojo
            pr.green=(mat.Posicion(i*2-1,j*2).green+mat.Posicion(i*2-1,j*2-2).green+mat.Posicion(i*2,j*2-1).green+mat.Posicion(i*2-2,j*2-1).green)/4;
			pr.green+=alpha*(grad(mat,i*2-1,j*2-1,'r'));
			if ((int)(pr.green)>255) {pr.green=255;}
			if ((int)(pr.green)<0) {pr.green=0;}
            mat.Definir(pr,i*2-1,j*2-1);
		}
		for (int j=1;j<=mat.Ccolumnas()/2;j++) {
            pixel pb=mat.Posicion(i*2,j*2); //azul
            pb.green=(mat.Posicion(i*2,j*2+1).green+mat.Posicion(i*2,j*2-1).green+mat.Posicion(i*2+1,j*2).green+mat.Posicion(i*2-1,j*2).green)/4;
			pb.green+=alpha*(grad(mat,i*2,j*2,'b'));
			if ((int)(pb.green)>255) {pb.green=255;}
			if ((int)(pb.green)<0) {pb.green=0;}
		        mat.Definir(pb,i*2,j*2);
		}
	}
}
