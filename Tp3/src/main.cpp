#include <iostream>
#include <fstream>
#include "aux/metodos.cpp"
#include <ctime>
#include <math.h>

using namespace std;

void cargar(Matriz& m, vector<unsigned char>& a, char* in) {
	int w=768;
	int h=512;
	ifstream image;
	image.open(in, ios_base::binary);

	int n = 54+(w*h*3);

	char res[n];
	for (int i=0;i<n;i++) {
		res[i] = '0';
	}
	
	image.read(res, n);
	
	for (int i=0;i<54;i++) {
		a[i]=res[i];
	} //el header hay que guardarlo para generar una nueva imagen
	
	for (int i=54;i<n;i+=3) {
		pixel p;
		char x=res[i];
		int ix=(int) x;
		p.blue=(ix+256)*(ix<0)+ix*(ix>0);
		x=res[i+1];
		ix=(int) x;
		p.green=(ix+256)*(ix<0)+ix*(ix>0);
		x=res[i+2];
		ix=(int) x;
		p.red=(ix+256)*(ix<0)+ix*(ix>0); //¿Lo que muestra me corta el borde?
		int ireal=(i-54)/3;
		m.Definir(p,(ireal/w)+1,(ireal%w)+1);
	} 
}

void devolver(Matriz& m, vector<unsigned char>& a, char* out) {
    int w=768;
    int h=512;
    FILE* f;
    unsigned char img[3*w*h+54];

    for (int i=0;i<54;i++) {
        img[i]=a[i];
    }

    for (int i=0;i<h;i++) {
        for (int j=0;j<w;j++) {
            unsigned int r = m.Posicion(i+1,j+1).red;
            unsigned int g = m.Posicion(i+1,j+1).green;
            unsigned int b = m.Posicion(i+1,j+1).blue;
            img[54+(i*w+j)*3+2] = 0;//(char)(r);
            img[54+(i*w+j)*3+1] = (char)(g);
            img[54+(i*w+j)*3+0] = 0;(char)(b);
        }
    }

    f = fopen(out,"wb");
    fwrite(img,1,54+w*h*3,f);
    fclose(f);
}

char* sinb(char* in) {
	char* res=in;
	int i;
	for (i=0;res[i]!='b' || res[i+1]!='.' ;i++) {}
	for (int j=i;res[j]!=0;j++) {
		res[j]=res[j+1];
	} return res;
}

double psnr(Matriz& orig, Matriz& m) {
	int f=m.Cfilas();
	int c=m.Ccolumnas();
	double mse=0;
	for (int i=2;i<f;i++) {
		for (int j=2;j<c;j++) {
			mse+=pow((int)(m.Posicion(i,j).green-orig.Posicion(i,j).green),2);
		}
	} mse=mse/((f-2)*(c-2)); //mse=error cuadrático medio
	return 10*log10(pow(255,2)/mse);
}

int main(int argc, char** argv) {

    Matriz m(512,768);
    vector<unsigned char> header(54);
	cargar(m,header,argv[1]);

	clock_t t;
	t = clock();

	if (*argv[3]=='0') {
		VecinoMasCercano(m);
	} else if (*argv[3]=='1') {
		InterpBilineal(m);
	} else if (*argv[3]=='2') {
		InterpXDir(m);
	} else {
		ElDelPaper(m);
	}

	t = clock() - t;
	ofstream tiempo;
	tiempo.open("Tiempo",ios::app);
	tiempo << "Clocks: "<< (long int)t << " segundos: " << ((float)t)/CLOCKS_PER_SEC << endl;

	IBilinealRB(m);
	devolver(m,header,argv[2]);

	Matriz orig(512,768);
	cargar(orig,header,sinb(argv[1]));

	ofstream psnrdev;
	psnrdev.open("psnr",ios::app);
	psnrdev << psnr(orig,m) << endl;

	return 0;
}
