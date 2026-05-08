#include "graph.hpp"
#include <vector>
#include <queue>
#include <functional>

using namespace std;

const int INF = 1e9;

vector<int> dijkstra(
    Grafo& g,
    int inicio,
    int destino,
    vector<int>& prev,
    int& explorados
) {
    vector<int> dist(g.numNodos, INF);

    prev.assign(g.numNodos, -1);
    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;

    dist[inicio] = 0;
    pq.push({0, inicio});

    explorados = 0;
    while (!pq.empty()) {
        auto actual = pq.top();
        pq.pop();

        int distancia = actual.first;
        int nodo = actual.second;

        if (distancia > dist[nodo]) {
            continue;
        }

        explorados++;

        if (nodo == destino) {
            break;
        }

        for (auto arista : g.adj[nodo]) {

            int vecino = arista.destino;
            int peso = arista.peso;

            if (dist[nodo] + peso < dist[vecino]) {
                dist[vecino] = dist[nodo] + peso;
                prev[vecino] = nodo;
                pq.push({dist[vecino], vecino});
            }
        }
    }

    return dist;
}

