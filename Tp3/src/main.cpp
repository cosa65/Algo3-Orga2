#include <iostream>
#include <fstream>
#include "aux/metodos.cpp"
#include <ctime>

using namespace std;

void cargar(Matriz& m, vector<unsigned char>& a, char* in) {
	int w=768;
	int h=512;
	ifstream image;
	image.open(in, ios_base::binary);

	int n = 54+(w*h*3);

	unsigned char res[n]; //= new char[n];
	for(int i = 0; i < n; i++)
	res[i] = '0';

	image.read(res, n); //hasta acá, gracias gugl

	for (int i=0;i<54;i++) {
		a[i]=res[i];
	} //el header hay que guardarlo para generar una nueva imagen

	for (int i=54;i<n;i+=3) {
		pixel p;
	//	uint ix= (uint)res[i];
		//int ix=(int) x;
		p.blue=(uint)res[i];	//(ix+256)*(ix<0)+ix;
	//	uint ix= (uint)res[i+1];

		p.green=(uint)res[i+1]; //(ix+256)*(ix<0)+ix;
	//	x=res[i+2];
	//	ix=(int) x;
		p.red=(uint)res[i+2]; //(ix+256)*(ix<0)+ix; //¿Little endian o lo que muestra me corta el borde?
		cout << p.red << ' ' << p.green << ' '<<p.blue << endl;
        int ireal=(i-54)/3;
        m.Definir(p,(ireal/h)+1,(ireal%h)+1);
	} 
}

void devolver(Matriz& m, vector<unsigned char>& a, char* out) {
    int w=768;
    int h=512;
    FILE *f;
    unsigned char img[3*w*h+54];

    for (int i=0;i<54;i++) {
        img[i]=a[i];
    }

    for (int i=0;i<w;i++) {
        for (int j=0;j<h;j++) {
            int r = m.Posicion(i+1,j+1).red;
            int g = m.Posicion(i+1,j+1).green;
            int b = m.Posicion(i+1,j+1).blue;
            img[54+(i+j*w)*3+2] = (unsigned char)(r); // estará bien que esté al vesre? ver http://stackoverflow.com/questions/2654480/writing-bmp-image-in-pure-c-c-without-other-libraries
            img[54+(i+j*w)*3+1] = (unsigned char)(g);
            img[54+(i+j*w)*3+0] = (unsigned char)(b);
        }
    }

    f = fopen(out,"wb");
    fwrite(img,1,54+w*h*3,f);
    fclose(f);
}



int main(int argc, char** argv) {
	/*clocklock_t t;
	t = clock();*/

    Matriz m(768,512);
    vector<unsigned char> header(54);
	cargar(m,header,argv[1]);
    devolver(m,header,argv[2]); //podemos usar argv[3] para el método*/


	//posEnVectorImaginario(m, 1 , 2, 1, 1, padelante, primfil, primcol);

	//cout << "(" << primfil << "," << primcol << ")" << endl;

	/*ofstream tiempo;
	t = clock() - t;
	tiempo.open("Tiempo");
	tiempo << "Clocks: "<< (long int)t << " segundos: " << ((float)t)/CLOCKS_PER_SEC << endl;*/

    /*pixel p;
	Matriz m(20,10);
	for (int i=0;i<20;i++) {
		for (int j=0;j<10;j++) {
			p.green=(i+j)*10;
			p.red=i*10;
			p.blue=j*10;
			m.Definir(p,i+1,j+1);
		}
	} m.mostrar();
	m.IBilinealG();
	//m.IBilinealRB();
	m.mostrar();*/

	return 0;
}
