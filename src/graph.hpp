#pragma once
#include <vector>
#include <unordered_map>
using namespace std;

struct Arista {
    int destino;
    int peso;
};

struct Grafo {
    int numNodos = 0;
    long long numAristas = 0;
    
    vector<vector<Arista>> adj;
    unordered_map<int,int> originalAInterno;
    vector<int> internoAOriginal;

    int agregarNodo(int idOrig);
    void agregarArista(int u, int v, int peso);

    bool existeNodo(int idOrig);    
    int obtenerInterno(int idOrig);

};

