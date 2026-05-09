#include "graph.hpp"
#include <fstream>
#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>

using namespace std;

vector<int> bfsDesde(
    Grafo& g,
    int origen,
    int& visitados
) {

    vector<int> dist(g.numNodos, -1);

    queue<int> q;

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
}

int contarComponentes(
    Grafo& g,
    int& tamanoMayor
) {

    vector<bool> visitado(g.numNodos, false);

    int numComponentes = 0;

    tamanoMayor = 0;

    for (int i = 0; i < g.numNodos; i++) {

        if (!visitado[i]) {

            numComponentes++;

            queue<int> q;

            q.push(i);

            visitado[i] = true;

            int tamano = 0;

            while (!q.empty()) {

                int actual = q.front();
                q.pop();

                tamano++;

                for (auto arista : g.adj[actual]) {

                    int vecino = arista.destino;

                    if (!visitado[vecino]) {

                        visitado[vecino] = true;

                        q.push(vecino);
                    }
                }
            }

            if (tamano > tamanoMayor) {
                tamanoMayor = tamano;
            }
        }
    }

    return numComponentes;
}

void guardarAnalisis(Grafo& g) {

    ofstream out("results/analisis_estructural.txt");

    out << fixed << setprecision(2);

    out << "===== ANALISIS ESTRUCTURAL =====\n\n";

    out << "--- Estadisticas del grafo ---\n\n";

    out << "Estadistica              | Valor SNAP  | Valor obtenido\n";
    out << "-------------------------|-------------|----------------\n";

    out << "Numero de nodos          | 1,088,092   | "
        << g.numNodos << "\n";

    out << "Numero de aristas        | 1,541,898   | "
        << g.numAristas / 2 << "\n";

    double gradoPromedio =
        (2.0 * (g.numAristas / 2.0)) / g.numNodos;

    out << "Grado promedio           | ~2.83       | "
        << gradoPromedio << "\n";

    int maxNodo = 0;
    int maxGrado = 0;

    for (int i = 0; i < g.numNodos; i++) {

        if ((int)g.adj[i].size() > maxGrado) {

            maxGrado = g.adj[i].size();

            maxNodo = i;
        }
    }

    out << "Nodo de mayor grado      | N/A         | "
        << g.internoAOriginal[maxNodo]
        << " (grado: "
        << maxGrado
        << ")\n";

    cout << "Calculando componentes conexas...\n";

    int tamanoMayor = 0;

    int numComponentes =
        contarComponentes(g, tamanoMayor);

    out << "Nodos comp. conexa princ.| 1,087,562   | "
        << tamanoMayor << "\n";

    out << "\n--- Componentes conexas ---\n\n";

    out << "Numero de componentes conexas: "
        << numComponentes
        << "\n";

    out << "Tamano de la mayor componente: "
        << tamanoMayor
        << "\n";

    cout << "Ejecutando BFS para diametro aproximado...\n";

    int visitados = 0;

    vector<int> distancias =
        bfsDesde(g, maxNodo, visitados);

    int diametroAprox = 0;

    for (int d : distancias) {

        if (d > diametroAprox) {
            diametroAprox = d;
        }
    }

    out << "\n--- Diametro aproximado ---\n\n";

    out << "Nodo origen BFS: "
        << g.internoAOriginal[maxNodo]
        << "\n";

    out << "Nodos explorados: "
        << visitados
        << "\n";

    out << "Diametro aproximado: "
        << diametroAprox
        << "\n";

    out << "Valor SNAP: 782\n";

    out.close();

    cout << "Analisis estructural completado\n";
}
