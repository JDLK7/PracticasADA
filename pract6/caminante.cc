//Jose Domenech Leal 
//20097305C

#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>

using namespace std;

bool t = false;
bool p = false;
bool ignoreRecursive = false;
string fichero;

bool comprobarArgumentos(int argc, char** argv) {
    if(argc == 1) {
        cout << "El programa debe ejecutarse con los siguientes argumentos:" << endl;
        cout << "caminante [-t] [-p] [--ignore-recursive] -f fichero_entrada" << endl;

        return false;
    }

    bool f = false;

    for(int i=1; i<argc; i++) {
        if(strcmp(argv[i], "-f") == 0 && (i+1)<argc) {
            f = true;
            fichero = argv[i+1];
        }
    }

    if(f == false) {
        cout << "El argumento \"-f fichero entrada\" es obligatorio." << endl;
        cout << "caminante [-t] [-p] [--ignore-recursive] -f fichero_entrada" << endl;
        
        return false;
    }

    for(int i=1; i<argc; i++) {
        if(strcmp(argv[i], "-t"))
            t = true;
        if(strcmp(argv[i], "-p"))
            p = true;
        if(strcmp(argv[i], "--ignore-recursive"))
            ignoreRecursive = true;
    }

    return true;
}
/*
void imprimirMatriz(int n, int m, int **mapa) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            cout << mapa[i][j] << "-";
        }
        cout << endl;
    }
}
*/
void leerMapa(ifstream &f, int &n, int &m, int **mapa) {
    string linea;

    if(f.is_open()) {
        if(getline(f, linea)) {
            n = atoi(linea.substr(0, linea.find(" ")+1).c_str());
            m = atoi(linea.substr(linea.find(" ")+1).c_str());
            mapa = new int*[n];
            for(int i=0; i<n; i++) {
                mapa[i] = new int[m];
            }
        }
        else {
            cout << "El fichero está vacío." << endl;
            exit(1);
        }

        int pos;

        for(int i=0; i<n; i++) {
            getline(f, linea);
            for(int j=0; j<m; j++) {                
                if(j == m-1) {
                    mapa[i][j] = atoi(linea.substr(0).c_str());
                }
                else {
                    pos = linea.find(" ");
                    
                    mapa[i][j] = atoi(linea.substr(0, pos).c_str());
                }
                
                linea = linea.substr(pos+1);
            }
        }

        f.close();
    }
    else {
        cout << "Fallo al abrir el archivo." << endl;
        exit(1);
    }
}

int minimo(int a, int b, int c) {
    if(a<b && a<c)
        return a;
    if(b<a && b<c)
        return b;
    if(c<a && c<b)
        return c;
}

int recursivaSinAlmacen(int n, int m, int **mapa) {
    if(n==0 && m==0) {
        return mapa[n][m];
    }
    
    return minimo(recursivaSinAlmacen(n, m-1, mapa), recursivaSinAlmacen(n-1, m, mapa), recursivaSinAlmacen(n-1, m-1, mapa));
}

void liberarMemoria(int n, int m, int **mapa) {
    for(int i=0; i<n; i++) {
        delete [] mapa[i];
    }
    delete [] mapa;
}

int main(int argc, char** argv) {
    if(!comprobarArgumentos(argc, argv))
        return 1;
    
    ifstream f (fichero);
    int **mapa;
    int n, m;

    leerMapa(f, n, m, mapa);
    //imprimirMatriz(n, m, mapa);

    if(!ignoreRecursive) {
        cout << "Recursive: " << recursivaSinAlmacen(n, m, mapa);
    }

    liberarMemoria(n, m, mapa);

    return 0;
}