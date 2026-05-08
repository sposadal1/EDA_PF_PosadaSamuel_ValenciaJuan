#include "graph.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

using namespace std;

Grafo cargarGrafo(string archivo) {

    Grafo g;
    ifstream file(archivo);
    string linea;
    srand (42);

    long long contador = 0;

    while (getline(file, linea)) {
        if (linea.empty() || linea[0] == '#') {
            continue;
        }

        stringstream ss(linea);

        int uOrig, vOrig;

        int u = g.agregarNodo(uOrig);
        int v = g.agregarNodo(vOrig);

        int peso = (rand() % 10  ) + 1;
        g.agregarArista(u, v, peso);

        contador++;

        if (contador % 500000 == 0) {
            cout << "Lineas procesadas: " << contador << endl;

        }
    }

    return g;
}
