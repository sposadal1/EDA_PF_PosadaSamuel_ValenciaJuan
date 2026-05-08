#include "graph.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, peso;
};

struct DSU {
    vector<int> parent, rango;

    DSU(int n) : parent(n), rango(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rango[a] < rango[b]) swap(a, b);
        parent[b] = a;
        if (rango[a] == rango[b]) rango[a]++;
        return true;
    }
};

bool dfsCiclo(int nodo, vector<vector<pair<int,int>>>& adj, vector<int>& color) {
    color[nodo] = 1;
    for (auto [vecino, _] : adj[nodo]) {
        if (color[vecino] == 1) return true;
        if (color[vecino] == 0 && dfsCiclo(vecino, adj, color)) return true;
    }
    color[nodo] = 2;
    return false;
}

vector<int> parsearCamino(const string& linea) {
    vector<int> nodos;
    istringstream ss(linea);
    int id;
    while (ss >> id) nodos.push_back(id);
    return nodos;
}

void generarSubgrafo(Grafo& g) {
    ifstream caminos("results/caminos_q01_q06.txt");

    set<int> nodosSet;
    string linea;

    while (getline(caminos, linea)) {
        if (linea.empty() || linea[0] == 'Q') continue;
        for (int id : parsearCamino(linea)) nodosSet.insert(id);
    }
    caminos.close();

    unordered_map<int,int> localIndex;
    vector<int> localAOriginal;
    int idx = 0;
    for (int id : nodosSet) {
        localIndex[id] = idx++;
        localAOriginal.push_back(id);
    }

    int N = localAOriginal.size();
    vector<vector<pair<int,int>>> adjLocal(N);
    vector<Edge> edges;
    set<pair<int,int>> aristaVista;

    for (int origId : nodosSet) {
        if (!g.existeNodo(origId)) continue;
        int u = g.obtenerInterno(origId);
        int uLocal = localIndex[origId];

        for (auto& arista : g.adj[u]) {
            int vOrig = g.internoAOriginal[arista.destino];
            if (!nodosSet.count(vOrig)) continue;
            int vLocal = localIndex[vOrig];
            adjLocal[uLocal].push_back({vLocal, arista.peso});
            auto key = make_pair(min(uLocal, vLocal), max(uLocal, vLocal));
            if (!aristaVista.count(key)) {
                aristaVista.insert(key);
                edges.push_back({uLocal, vLocal, arista.peso});
            }
        }
    }

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.peso < b.peso;
    });

    DSU dsu(N);
    long long mstPeso = 0;
    int mstAristas = 0;

    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mstPeso += e.peso;
            mstAristas++;
        }
    }

    vector<int> color(N, 0);
    bool tieneCiclo = false;
    for (int i = 0; i < N && !tieneCiclo; i++) {
        if (color[i] == 0) tieneCiclo = dfsCiclo(i, adjLocal, color);
    }

    ofstream outAnalisis("results/analisis_subgrafo.txt");
    outAnalisis << "===== ANALISIS SUBGRAFO =====\n\n";
    outAnalisis << "Nodos subgrafo: " << N << "\n";
    outAnalisis << "Aristas subgrafo: " << edges.size() << "\n\n";
    outAnalisis << "===== MST (Kruskal) =====\n";
    outAnalisis << "Peso total MST: " << mstPeso << "\n";
    outAnalisis << "Aristas MST: " << mstAristas << "\n\n";
    outAnalisis << "===== DAG =====\n";
    outAnalisis << (tieneCiclo ? "El subgrafo NO es DAG\n" : "El subgrafo SI es DAG\n");
    outAnalisis.close();

    ofstream outSubgrafo("results/subgrafo_caminos.txt");
    outSubgrafo << N << " " << edges.size() << "\n";
    for (int i = 0; i < N; i++) {
        outSubgrafo << localAOriginal[i] << ":";
        for (auto [vecino, peso] : adjLocal[i]) {
            outSubgrafo << " " << localAOriginal[vecino] << "(" << peso << ")";
        }
        outSubgrafo << "\n";
    }
    outSubgrafo.close();
}
