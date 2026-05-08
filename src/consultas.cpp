#include "graph.hpp"
#include <fstream>
#include <chrono>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;
using namespace chrono;

vector<int> bfs(
    Grafo& g,
    int inicio,
    int destino,
    int& explorados
);

vector<int> dijkstra(
    Grafo& g,
    int inicio,
    int destino,
    vector<int>& prev,
    int& explorados
);

void guardarCamino(
    vector<int>& prev,
    int destino,
    vector<int>& camino
) {

    int actual = destino;

    while (actual != -1) {

        camino.push_back(actual);

        actual = prev[actual];
    }

    reverse(camino.begin(), camino.end());
}

void ejecutarConsultas(Grafo& g) {

    vector<pair<int,int>> consultas = {

        {1,500000},
        {100,1000000},
        {50000,750000},
        {200000,800000},
        {300000,100000},
        {1,1087562},
        {500000,1},
        {250000,600000},
        {10000,900000},
        {400000,150000}
    };

    ofstream out("results/consultas_p2p.csv");

    out << "consulta,origen,destino,dist_dijkstra,saltos_bfs,nodos_dijkstra,nodos_bfs,t_dijkstra_ms,t_bfs_ms\n";

    ofstream caminos("results/caminos_q01_q06.txt");

    for (int i = 0; i < consultas.size(); i++) {

        int origenOriginal = consultas[i].first;
        int destinoOriginal = consultas[i].second;

        if (
            !g.existeNodo(origenOriginal)
            ||
            !g.existeNodo(destinoOriginal)
        ) {
            continue;
        }

        int origen = g.obtenerInterno(origenOriginal);
        int destino = g.obtenerInterno(destinoOriginal);

        vector<int> prev;

        int exploradosDijkstra = 0;
        int exploradosBfs = 0;

        auto inicioD = high_resolution_clock::now();

        vector<int> dist = dijkstra(
            g,
            origen,
            destino,
            prev,
            exploradosDijkstra
        );

        auto finD = high_resolution_clock::now();

        auto inicioB = high_resolution_clock::now();

        vector<int> bfsDist = bfs(
            g,
            origen,
            destino,
            exploradosBfs
        );

        auto finB = high_resolution_clock::now();

        double tiempoD =
            duration<double, milli>(finD - inicioD).count();

        double tiempoB =
            duration<double, milli>(finB - inicioB).count();

        bool alcanzable = dist[destino] < 1e9;

        out << "Q" << i + 1 << ",";
        out << origenOriginal << ",";
        out << destinoOriginal << ",";
        out << (alcanzable ? to_string(dist[destino]) : "INF") << ",";
        out << (bfsDist[destino] != -1 ? to_string(bfsDist[destino]) : "INF") << ",";
        out << exploradosDijkstra << ",";
        out << exploradosBfs << ",";
        out << fixed << setprecision(2);
        out << tiempoD << ",";
        out << tiempoB << "\n";

        if (i == 0 || i == 5) {

            caminos << "Q" << i + 1 << "\n";

            if (!alcanzable) {

                caminos << "no existe\n\n";

            } else {

                vector<int> camino;

                guardarCamino(prev, destino, camino);

                for (int nodo : camino) {

                    caminos << g.internoAOriginal[nodo] << " ";
                }

                caminos << "\n\n";
            }
        }
    }

    out.close();

    caminos.close();
}