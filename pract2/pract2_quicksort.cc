#include <sys/resource.h>
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <fstream>

using namespace std;

const long NUM_REPETICIONES = 30;

/*****************************************************
Nombre funcion: tiempo(void)
Proposito: Calcular el tiempo de CPU de este proceso
(y sólo de este proceso)
Parametros de entrada: nada
Devuelve: El tiempo empleado en segundos
******************************************************/
long double
tiempo(void){
 struct rusage usage;
 getrusage(RUSAGE_SELF,&usage);
 return( (long double) usage.ru_utime.tv_sec +
	 (long double) usage.ru_utime.tv_usec/1e6 
	 /* + (long double) usage.ru_stime.tv_sec +
         (long double) usage.ru_stime.tv_usec/1e6 */  
       );
}

/******************************************************************
quicksortCentral(int * v, long pi, long pf)

Algoritmo de ordenación Quicksort tomando como pivote el
elemento del vector que ocupa la posición central
*******************************************************************/
void 
quicksortCentral(int * v, long pi, long pf){
long i,j;
int pivote,aux; 
  if (pi<pf){
	i=pi; j=pf;
	pivote=v[(i+j)/2];
	do{
		while (v[i]<pivote) i++;
		while (v[j]>pivote) j--;
		if (i<=j) {
		  aux=v[i]; v[i]=v[j]; v[j]=aux;
		  i++; j--;
		}
	}while (i<=j);
	if (pi<j) quicksortCentral(v,pi,j);
	if (i<pf) quicksortCentral(v,i,pf);
  }
}

int main() {
	srand(getpid());

	long double t1, t2, tm;
	int *array;

	ofstream salida;
  	salida.open ("salida_quicksort.txt");

	for(int i=12; i<=22; i++) {
		int numElem = (int) pow(2,i);
		array = new int[numElem];

		for(int j=0; j<numElem; j++) {
			array[j] = rand();
		}

		tm = 0.0;
		for(int j=0; j<NUM_REPETICIONES; j++) {
			t1 = tiempo();
			quicksortCentral(array, 0, numElem-1);
			t2 = tiempo();

			tm += (t2 - t1); 
		}
		tm = tm/NUM_REPETICIONES;

		salida << numElem << "\t" << tm << endl;
		
		delete array;
	}
	salida.close();
	return 0;
}

