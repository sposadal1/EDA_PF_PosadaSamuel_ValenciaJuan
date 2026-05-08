#include "graph.hpp"
#include <iostream>     

using namespace std;

Grafo cargarGrafo(string archivo);
void guardarAnalisis(Grafo& g);
void ejecutarConsultas(Grafo& g);
void generarSubgrafo(Grafo& g);

int main(int argc, char* argv[]) {

    if (argc < 3) {
        cout << "Uso: \n";
        cout << "./eda_pf A data/roadNet-PA.txt\n";
        return 1;

    }

    string modulo = argv[1];
    string archivo = argv[2];   

    cout << "Cargando grafo \n";    

    Grafo g = cargarGrafo(archivo);

    cout << "Nodos cargados " << g.numNodos << endl;
    cout << "Aristas cargadas " << g.numAristas << endl;

    if (modulo == "A") {
        guardarAnalisis(g);
        cout << "Modulo A ejecutado \n";
    }

    else if (modulo == "B") {
        ejecutarConsultas(g);
        cout << "Modulo B ejecutado \n";
    }

    else if (modulo == "C") {
        generarSubgrafo(g);
        cout << "Modulo C ejecutado \n";
    }

    return 0;

}
