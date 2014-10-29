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
