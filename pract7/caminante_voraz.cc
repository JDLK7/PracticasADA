//Jose Domenech Leal 
//20097305C

#include <iostream>
#include <string.h>
#include <sstream>
#include <iterator>
#include <fstream>
#include <vector>

using namespace std;

bool p = false;
string fichero;

const int NUM_MOVIMIENTOS = 3;

bool comprobarArgumentos(int argc, char** argv) {
    if(argc == 1) {
        cout << "El programa debe ejecutarse con los siguientes argumentos:" << endl;
        cout << "caminante [-p] -f fichero_entrada" << endl;

        return false;
    }

    bool f = false;

    for(int i=1; i<argc && !f; i++) {
        if(strcmp(argv[i], "-f") == 0 && (i+1)<argc) {
            f = true;
            fichero = argv[i+1];
        }
    }

    if(f == false) {
        cout << "El argumento \"-f fichero entrada\" es obligatorio." << endl;
        cout << "caminante [-p] -f fichero_entrada" << endl;
        
        return false;
    }

    for(int i=1; i<argc; i++)
        if(strcmp(argv[i], "-p") == 0)
            p = true;

    return true;
}

void imprimirMatriz(int n, int m, const vector<vector<int>> &camino) {
    if(p) {
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                bool encontrado = false;
                for(int k=0; k<camino.size() && !encontrado; k++) {
                    if(camino[k][0]==i && camino[k][1]==j) {
                        encontrado = true;
                    }
                }
                if(encontrado) {
                    cout << "X";
                }
                else {
                    cout << ".";
                }
            }
            cout << endl;
        }
    }
}

void imprimirCamino(const vector<vector<int>> &camino) {
    if(p) {
        cout << "A greedy path: " << endl;
        for(int i=0; i<camino.size(); i++)
            cout << "(" << camino[i][0] << "," << camino[i][1] << ")";
        cout << endl;
    }
}

void leerMapa(ifstream &f, int &n, int &m, vector< vector<int> > &mapa) {
    string linea;

    if(f.is_open()) {
        if(getline(f, linea)) {
            n = atoi(linea.substr(0, linea.find(" ")+1).c_str());
            m = atoi(linea.substr(linea.find(" ")+1).c_str());
        }
        else {
            cout << "El fichero está vacío." << endl;
            exit(1);
        }

        int pos;

        while(getline(f, linea)) {
            vector<int> fila;

            istringstream iss(linea);
            vector<string> pesos{istream_iterator<string>{iss},
                      istream_iterator<string>{}};

            for(int i=0; i<pesos.size(); i++)
                fila.push_back(atoi(pesos[i].c_str()));
 
            mapa.push_back(fila);
        }

        f.close();
    }
    else {
        cout << "Fallo al abrir el archivo." << endl;
        exit(1);
    }
}

int minimo(int a, int b, int c) {
    if(a<=b && a<=c)
        return a;
    if(b<=a && b<=c)
        return b;
    if(c<=a && c<=b)
        return c;
}

// i,n -> fila
// j,m -> columna
int voraz(int &i, int &j, const int &n, const int &m, const vector<vector<int>> &mapa, vector<vector<int>> &camino) {
    if(p) {
        vector<int> nodo;
        nodo.push_back(i);
        nodo.push_back(j);

        camino.push_back(nodo);
    } 

    //Ultima casilla
    if(i == (n-1) && j == (m-1))
        return mapa[i][j];
    //Ultima fila, solo derecha
    else if(i == (n-1))
        return mapa[i][j] + voraz(i, ++j, n, m, mapa, camino);
    //Ultima columna, solo abajo
    else if(j == (m-1))
        return mapa[i][j] + voraz(++i, j, n, m, mapa, camino);
    else {
        int derecha = mapa[i][(j+1)];
        int abajo = mapa[(i+1)][j];
        int diagonal = mapa[(i+1)][(j+1)];

        int min = minimo(derecha, abajo, diagonal);

        if(min == diagonal)
            return mapa[i][j] + voraz(++i, ++j, n, m, mapa, camino);
        else if(min == derecha)
            return mapa[i][j] + voraz(i, ++j, n, m, mapa, camino);
        else if(min == abajo)
            return mapa[i][j] + voraz(++i, j, n, m, mapa, camino);
    }
}

int main(int argc, char** argv) {
    if(!comprobarArgumentos(argc, argv))
        return 1;

    ifstream f (fichero);
    vector< vector<int> > mapa;
    int n, m;
    int i = 0, j = 0;
    vector<vector<int>> camino;

    leerMapa(f, n, m, mapa);
    cout << "Greedy: " << voraz(i,j,n,m,mapa,camino) << endl << endl;
    
    imprimirCamino(camino);
    imprimirMatriz(n,m,camino);
    
    return 0;
}