#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

unsigned long calls_pow2_1, calls_pow2_2, calls_pow2_3, calls_pow2_4;

/*
El resultado de pow2_1 es la gráfica que muestra un coste lineal (la lila).
Esto se debe a que la función solamente realiza una llamada recursiva, por 
lo tanto el numero de llamadas es proporcional a n.
*/
unsigned long pow2_1(unsigned n){
    calls_pow2_1++;
    
    if(n == 0) {
        return 1;
    }
    else {
        return 2 * pow2_1(n-1);
    }
}

/*
El resultado de pow2_2 es la gráfica con forma escalonada.
Esta es mas lenta que la primera porque aunque las llamadas recursivas
reducen la talla a la mitad, se realizan 2 llamadas (esas 2 generar otras 2 cada una, etc.), 
por lo que el número de llamadas recursivas aumenta exponencialmente.
*/
unsigned long pow2_2(unsigned n){
    calls_pow2_2++;

    if(n == 0) {
        return 1;
    }
    else if(n%2 == 0) {
        return pow2_2(n/2) * pow2_2(n/2);
    }
    else {
        return 2 * pow2_2(n/2) * pow2_2(n/2);
    }
}

/*
Esta es la función mas rápida de las 4. Esto se debe, en primer lugar a que
se reduce la talla del problema en la mitad y, además, solo se hace una llamada
recursiva, ya que se guarda el valor de ésta para realizar el cálculo r x r.
Su coste por lo tanto es logarítmico.
*/
unsigned long pow2_3(unsigned n){
    calls_pow2_3++;

    if(n == 0) {
        return 1;
    }
    else if(n%2 == 0) {
        unsigned long r = pow2_3(n/2);
        return r*r;
    }
    else {
        unsigned long r = pow2_3(n/2);
        return 2*r*r;
    }
}

/*
Esta función es la más lenta de todas, porque en cada iteración se realizan 2 llamadas
y además se reduce solamente en 1 la talla. El coste de esta función será exponencial (2^n).
Es tan elevado y ralentiza tanto la ejecución que se deja de ejecutar para n>32.
*/
unsigned long pow2_4(unsigned n){
    calls_pow2_4++;
    
    if(n == 0) {
        return 1;
    }
    else {
        return pow2_4(n-1) + pow2_4(n-1);
    }
}

int main(void){
    unsigned long sol,res;

    cout << "n     pow2_1  pow2_2  pow2_3  pow2_4" << endl;

    for (unsigned i=0; i<= 500; i+=2){
        
        sol = (unsigned long) powl(2,i);
        cout << i << "\t";
    
        calls_pow2_1=0;
        calls_pow2_2=0;
        calls_pow2_3=0;
        calls_pow2_4=0;

        res=pow2_1(i);
        if (res!=sol){cout << "Error in pow2_1(n): incorrect result"; exit(1);}

        res=pow2_2(i);
        if (res!=sol){cout << "Error in pow2_2(n): incorrect result"; exit(1);}

        res=pow2_3(i);
        if (res!=sol){cout << "Error in pow2_3(n): incorrect result"; exit(1);}

        /* pow2_4 can not be computed with (not so) big values of n...*/  
        if (i<=32){	
          res=pow2_4(i);
          if (res!=sol){cout << "Error in pow2_4(n): incorrect result"; exit(1);}
        }

        cout << calls_pow2_1 << "\t"; 
        cout << calls_pow2_2 << "\t"; 
        cout << calls_pow2_3 << "\t";
        if (calls_pow2_4) 
		cout  << calls_pow2_4;
        cout  << endl;
    }
}

