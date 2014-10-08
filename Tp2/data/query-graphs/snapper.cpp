#include <iostream>
#include <fstream>

using namespace std;

// ejemplo :   ".\snapper a b"  a = c, b = tolerancia


int main(int argc, char *argv[]){

	char *c = argv[1];
	char *tolerancia = argv[2];

	ifstream nodes;
	nodes.open("nodes");

	unsigned int nodos;

	nodes >> nodos;

	ofstream saltxt;
	saltxt.open("salida.txt");	
	saltxt << "# Directed graph (each unordered pair of nodes is saved once): " << endl
			<< "# Example snapped." << endl
			<< "# Nodes: " << nodos << " Edges: " << endl
			<< "# FromNodeId	ToNodeId" << endl;

	ifstream adj_list;
	adj_list.open("adj_list");

	while (nodos != 0){
		int nodoAc;
		adj_list >> nodoAc;

		string basura;
		adj_list >> basura;

		int link;
		adj_list >> link;
		while(link != -1){
			saltxt << nodoAc << "   " << link << endl;
			adj_list >> link;
		}
		nodos--;
	}

	saltxt << endl;

	ofstream salin;
	salin.open("salida.in");
	if (c[0]=='-') {
		salin << "0 " << c << " 1 " << "salida.txt " << tolerancia << endl;
	} else {
		salin << "1 " << c << " 1 " << "salida.txt " << tolerancia << endl;
	} return 0;

}
