void MatrizE::DefinirCol(double adefinir, int columna) {
	if (adefinir>0) {

		int size = _valores.size()+_Cfilas;

		_valores.resize(size);
		_posValores.resize(size);

		int i =	_inicioColumnas[columna-1]-1;
		int j = _inicioColumnas[columna]-1;
	
		for (int k=size-1;k>j+_Cfilas-1;k--) {
			_valores[k]=_valores[k-_Cfilas];
			_posValores[k]=_posValores[k-_Cfilas];		
		} 

		for (int k=0;k<_Cfilas;k++) {
			_valores[i+k]=adefinir;
			_posValores[i+k]=k+1;
		}
		for (int k=columna;k<=_Ccolumnas;k++) {
			_inicioColumnas[k]+=_Cfilas;

		}
	} 
}

void MatrizE::DefinirUnos(long int fila, long int columna) {
	long int size = _valores.size()+1;

	_valores.resize(size);
	_posValores.resize(size);

	long int i =	_inicioColumnas[columna-1]-1;
	long int j = _inicioColumnas[columna];
	long int lugar=j-1;
	for (long int k=i;k<j;k++) {
		if (_posValores[k]>fila) {
			lugar=k;
			k=j;	
		}
	} 

	for (long int k=size-1;k>lugar;k--) {
		_posValores[k]=_posValores[k-1];		
	} _valores[size-1]=1;
	_posValores[lugar]=fila;

	for (long int i=columna;i<=_Ccolumnas;i++) {
		_inicioColumnas[i]++;
	}
}
