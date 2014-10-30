//#include <math.h>
#include <cmath>


void porCte(vector<double> &v, double a) {
	for (unsigned long int i=0;i<v.size();i++) {
		v[i]=v[i]*a;
	}
}

double Norma1 (vector<double>& v) {
	unsigned long int lim=v.size();
	double suma=0;
	for (unsigned long int i=0;i<lim;i++) {
		suma+=abs(v[i]);
	} 
	return suma;
}

double Norma2 (vector<double>& v) {
	unsigned long int lim=v.size();
	double suma=0;
	for (unsigned long int i=0;i<lim;i++) {
		suma+=v[i]*v[i];
	} 
	return sqrt(suma);
}

/*double NormaInf (vector<double> v) {
	double res=0;
	unsigned long int lim=v.size();
	for (unsigned long int i=0;i<lim;i++) {
		if (abs(v[i])>res) {
			res=abs(v[i]);
		}
	} 
	return res;
}*/
