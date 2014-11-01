#include "ops.cpp"

//Aca van los 3 metodos enteros, usando las ops de ops.cpp
//Querés conservar la matriz original porque así no hay que cargarla de nuevo? No es mala, pero por ahí es mejor pasar por referencia y copiar adentro de la función si la vamos a modificar.

Matriz VecinoMasCercano(Matriz mat){
	//corto y pego o ponemos mat.vecinomascercano?
	return mat;
}

Matriz InterpBilineal(Matriz mat){

	return mat;
}

Matriz InterpXDir(Matriz mat){
	//básicamente:
	//for (int i=0;i<h;i++) {
	//	vector<int> x
	//	VecEnDir (1,0,x bla bla bla)
	//	filtrarImpares? que devuelva una copia del vector dejando solo las posiciones pares
	//	crear un vector p=[0,2,4,6...] (o modificar evaluarenInterpolante para que no sea necesario)
	//	for (int j=1;j<n;j+=2) {
	//		x[j]=evaluarenInterpolante(p,x,j);
	//	y metés x en la matriz. También podés no trabajar sobre una copia del vector y poner Definir(eso,i,j);
	//	pero de todas formas deberías trabajar sobre una copia de la matriz para poder definir el próximo paso
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
	return mat;	
}

Matriz ElDelPaper(Matriz mat){
	return mat;
}
