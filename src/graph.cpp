#include "graph.hpp"

int Grafo::agregarNodo(int idOrig) {
    if (!originalAInterno.count(idOrig)) {
        originalAInterno[idOrig] = numNodos;
        internoAOriginal.push_back(idOrig);
        adj.push_back({});

        numNodos++;
    }
return originalAInterno[idOrig];

}

void Grafo::agregarArista(int u, int v, int peso) {

    adj[u].push_back({v, peso});
    adj[v].push_back({u, peso});

    numAristas++;
}

bool Grafo::existeNodo(int idOrig){
    return originalAInterno.count(idOrig);

}

int Grafo::obtenerInterno(int idOrig){
    return originalAInterno[idOrig];
}

