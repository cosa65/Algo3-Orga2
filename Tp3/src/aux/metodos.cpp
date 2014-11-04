#include "ops.cpp"

//Aca van los 3 metodos enteros, usando las ops de ops.cpp
//Los hago void y por referencia porque no necesitamos guardar la matriz mosaiqueada para el psnr.

void VecinoMasCercano(Matriz& mat){

	Matriz nuevamat(mat.Cfilas(), mat.Ccolumnas());

	for (int i=1; i<=mat.Cfilas(); i++){
		for (int j=1; j<=mat.Ccolumnas(); j++){
			nuevamat.Definir(mat.Posicion(i,j),i,j);
		}
	}


	for (int i=1;i<=mat.Cfilas()/2;i++) {
		for (int j=1;j<=mat.Ccolumnas()/2;j++) {
		    pixel pr=mat.Posicion(i*2-1,j*2-1); // rojo
		    pixel pg=mat.Posicion(i*2-1,j*2); //verde
		    pr.green=pg.green;
		    nuevamat.Definir(pr,i*2-1,j*2-1);
//          mat.Definir(pg,i*2-1,j*2);
		}
		for (int j=1;j<=mat.Ccolumnas()/2;j++) {
		    pixel pg=mat.Posicion(i*2,j*2-1); // verde
		    pixel pb=mat.Posicion(i*2,j*2); //azul
		    pb.green=pg.green;
//          mat.Definir(pg,i*2,j*2-1);
		    nuevamat.Definir(pb,i*2,j*2);
		}
	}
	mat = nuevamat;
}

void InterpBilineal(Matriz& mat){

	Matriz nuevamat(mat.Cfilas(), mat.Ccolumnas());

	for (int i=1; i<=mat.Cfilas(); i++){
		for (int j=1; j<=mat.Ccolumnas(); j++){
			nuevamat.Definir(mat.Posicion(i,j),i,j);
		}
	}


	for (int i=1;i<=mat.Cfilas()/2;i++) {
		for (int j=1;j<=mat.Ccolumnas()/2;j++) {
            pixel pr=mat.Posicion(i*2-1,j*2-1); // rojo
            pr.green=(mat.Posicion(i*2-1,j*2).green+mat.Posicion(i*2-1,j*2-2).green+mat.Posicion(i*2,j*2-1).green+mat.Posicion(i*2-2,j*2-1).green)/4;
            nuevamat.Definir(pr,i*2-1,j*2-1);
		}
		for (int j=1;j<=mat.Ccolumnas()/2;j++) {
            pixel pb=mat.Posicion(i*2,j*2); //azul
            pb.green=(mat.Posicion(i*2,j*2+1).green+mat.Posicion(i*2,j*2-1).green+mat.Posicion(i*2+1,j*2).green+mat.Posicion(i*2-1,j*2).green)/4;
            nuevamat.Definir(pb,i*2,j*2);
		}
	}
	mat = nuevamat;
}

void InterpXDir(Matriz& mat){
	//básicamente:
	//for (int i=0;i<h;i++) {
	//	vector<int> x
	//	VecEnDir (1,0,x bla bla bla)
	//	filtrarImpares? que devuelva una copia del vector dejando solo las posiciones pares
	//	crear un vector p=[0,2,4,6...] (o modificar evaluarenInterpolante para que no sea necesario)
	//	for (int j=1;j<n;j+=2) {
	//		x[j]=evaluarenInterpolante(p,x,j);
	//	y metés x en la matriz. NO podés no trabajar sobre una copia del vector y poner Definir(eso,i,j);
	//	TENES que trabajar sobre una copia de la matriz para poder definir el próximo paso
	//	o bien hacer todo junto punto por punto, pero ahí tendrías que volver a calcular los vectores cada vez
	// Si no hacés todo junto punto por punto:
	//	Algo parecido para la vertical/diagonal/la que sea y la guardás en mat2
	//	for (i,j) {
	//		gradH=abs((i,j+1)-(i,j-1));
	//		gradV=abs((i+1,j)-(i-1,j));
	//		Esta fórmula me gusta, no la borren:
	//		def= (255-gradh)*mat1(i,j) + (255-gradv)*mat2(i,j), escalado de 1 a 255:
	//		escala=(255-gradh)+(255-gradv)=255*2-gradh-gradv
	//		mat.Definir(res/escala, i,j)); gg
	//		otra fórmula: ((255-grH)/255*valH+(255-grV)/255*valV)*255/(grH+grV)
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
