#include "graph.hpp"
#include <vector>
#include <queue>

using namespace std;

vector<int> bfs(
    Grafo& g,
    int inicio,
    int destino,
    int& explorados
)
{
    vector<int> dist(g.numNodos, -1);
    queue<int> q;
    dist[inicio] = 0;
    q.push(inicio);
    explorados = 0;
    while (!q.empty()) {
        int actual = q.front();
        q.pop();

        explorados++;

        if(actual == destino) {
            break;

        }

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
