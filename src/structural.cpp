#include "graph.hpp"
#include <fstream>
#include <vector>
#include <queue>
#include <iostream>


using namespace std;

vector <int> bfsDesde(Grafo& g, int origen, int& visitados) {
    vector <int> dist(g.numNodos, -1);
    queue <int> q;

    dist[origen] = 0;
    q.push(origen);
    visitados = 0;

    while (!q.empty()) {

        int actual = q.front();
        q.pop();

        visitados++;

        for (auto arista : g.adj[actual]) {
            int vecino = arista.destino;
            if (dist[vecino] == -1) {
                dist[vecino] = dist[actual] + 1;
                q.push(vecino);
            }
        }

    }

    return dist;


    int contComponentes(Grafo&, int& tamañoMayor) {
    vector <bool> visitado(g.numNodos, false);

    int numComponentes = 0;
    tamañoMayor = 0;

    for (int i = 0; i < g.numNodos; i++) {
        if (!visitado[i]) {
            numComponentes++;

            queque <int> q;
            q.push(i);
            visitado[i] = true;
            int tamaño = 0;

            while (!q.empty()) {
                int actual = q.front();
                q.pop();
                tamaño++;

                for (auto arista : g.adj[actual]) {
                    int vecino = arista.destino;
                    if (!visitado[vecino]) {
                        visitado[vecino] = true;
                        q.push(vecino);
                    }
                }
            }

            if (tamaño > tamañoMayor) {
                tamañoMayor = tamaño;
            }
            
        }
    } 

return numComponentes;

}

void guardarAnalisisBas(Grafo& g) {
    ofstream out("results/analisis_estructural.txt");
    
    out << "===== ANALISIS ESTRUCTURAL =====\n\n";

    out << "--- Estadisticas del grafo ---\n\n";

    out << "Estadistica              | Valor SNAP  | Valor obtenido\n";
    out << "-------------------------|-------------|----------------\n";

    out << "Numero de nodos          | 1,088,092   | " << g.numNodos << "\n";
    out << "Numero de aristas        | 1,541,898   | " << g.numAristas / 2 << "\n";

    double gradoPromedio = (2.0 * (g.numAristas / 2.0)) / g.numNodos;
    out << "Grado promedio           | ~2.83       | " << gradoPromedio << "\n";

    int maxNodo = 0;
    int maxGrado = 0;

    for (int i = 0; i < g.numNodos; i++) {

        if ((int)g.adj[i].size() > maxGrado) {

            maxGrado = g.adj[i].size();
            maxNodo = i;
        }
    }

    out << "Nodo de mayor grado      | (identificar)| "
        << g.internoAOriginal[maxNodo]
        << " (grado: " << maxGrado << ")\n";

    cout << "Calculando componentes conexas...\n";


    int tamañoMayor = 0;
    int numComponentes = contComponentes(g, tamañoMayor);}

    out << "Nodos comp. conexa princ.| 1,087,562   | " << tamañoMayor << "\n";

    out << "\n--- Componentes conexas ---\n\n";
    out << "Numero de componentes conexas: " << numComponentes << "\n";
    out << "Tamaño de la mayor componente: " << tamañoMayor << "\n";


    cout << "Ejecutando BFS desde nodo de mayor grado (diametro aprox.)...\n";

    int visitados = 0;
    vector <int> distancias = bfsDesde(g, maxNodo, visitados);

    int diametroAprox = 0;

    for (int i = 0; i < g.numNodos; i++) {
        if (distancias[i] > diametroAprox) {
            diametroAprox = distancias[i];
        }
    }

   out << "\n--- Diametro aproximado (BFS desde nodo de mayor grado) ---\n\n";
    out << "Nodo origen (mayor grado): " << g.internoAOriginal[maxNodo] << "\n";
    out << "Nodos explorados por BFS:  " << visitados << "\n";
    out << "Diametro aproximado:       " << diametroAprox << "\n";
    out << "Valor publicado por SNAP:  782\n";

    if (diametroAprox != 782) {
        out << "Diferencia vs SNAP:        " << (diametroAprox - 782)
            << " (el BFS desde un solo nodo es una cota inferior, "
            << "no el diametro exacto del grafo)\n";
    }

    out.close();

    cout << "Analisis estructural guardado en results/analisis_estructural.txt\n";
}    


