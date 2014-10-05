#include <iostream>
#include <fstream>

using namespace std;

// ejemplo :   ".\snapper A B C"  A = c, B = tolerancia, C = nombredearchivos.txt


int main(int argc, char *argv[]){

	char *c = argv[1];
	char *tolerancia = argv[2];
	char *nombre = argv[3];


	ifstream nodes;
	nodes.open("nodes");

	unsigned int nodos;

	nodes >> nodos;

	ofstream saltxt;
	saltxt.open(nombre);	
	saltxt << "# Directed graph (each unordered pair of nodes is saved once): " << endl
			<< "# Example shown in the Bryan and Leise." << endl
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
	salin.open("renombrame.in");
	salin << "1 " << c << " 1 " << nombre << " " << tolerancia << endl;

	return 0;

}