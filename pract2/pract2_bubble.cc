#include <sys/resource.h>
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <fstream>

using namespace std;

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
burbuja(int * v, unsigned long talla){

Algoritmo de ordenación burbuja sin ninguna mejora             
*******************************************************************/
void 
burbuja(int * v, unsigned long talla){
int aux;
                                    
for (unsigned long i=1; i<talla; i++)
   for (unsigned long j=0; j<talla-i; j++)
      if (v[j]>v[j+1]){  /*swap*/
         aux=v[j]; 
         v[j]=v[j+1]; 
         v[j+1]=aux;
      }
}

int main() {
	srand(getpid());

	long double t1, t2;

	ofstream salida;
  	salida.open ("salida.txt");

	for(int i=8; i<=16; i++) {
		int numElem = (int) pow(2,i);
		int array[numElem];

		for(int j=0; j<numElem; j++) {
			array[j] = rand();
		}

		t1 = tiempo();
		burbuja(array, numElem);
		t2 = tiempo();

		salida << numElem << "\t" << t2-t1 << endl;
	}

	salida.close();
	return 0;
}


