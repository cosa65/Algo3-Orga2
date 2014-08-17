#include <vector>

using namespace std;


struct Matriz
{
public:

//~Matriz();

Matriz(vector <vector<int> >, int tamfilas, int tamcolumnas);

private:

vector< vector<int> > _array;		//	taria bueno que este fuera un puntero a vector< vector<int> > asi no se pasa por copia, pero tira 											segmentation fault si lo es...


};
