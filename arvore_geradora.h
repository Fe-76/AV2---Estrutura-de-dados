#pragma once
#include "grafo.h"
#include <queue>

struct ElementoAGM {
    int u, v;
    int peso[3];
    string transporte;
};

struct ItemFila {
    int peso;
    int u, v;
    Aresta aresta;
    bool operator>(const ItemFila& o) const { return peso > o.peso; }
};

inline void mostrarAGM(const Grafo& g, int criterio, string titulo) {
    vector<bool> naArvore(g.n, false);
    vector<ElementoAGM> agm;
    priority_queue<ItemFila, vector<ItemFila>, greater<ItemFila>> fila;

    naArvore[0] = true;
    for (const auto& a : g.adj[0])
        fila.push({a.peso[criterio], 0, a.destino, a});

    while (!fila.empty() && (int)agm.size() < g.n - 1) {
        auto item = fila.top();
        fila.pop();

        if (naArvore[item.v]) continue;

        naArvore[item.v] = true;
        agm.push_back({item.u, item.v, {item.aresta.peso[0], item.aresta.peso[1], item.aresta.peso[2]},
                       item.aresta.transporte});

        for (const auto& a : g.adj[item.v]) {
            if (!naArvore[a.destino])
                fila.push({a.peso[criterio], item.v, a.destino, a});
        }
    }

    cout << "=== Arvore Geradora Minima por " << titulo << " ===" << endl;
    cout << "Arestas selecionadas: " << agm.size() << endl << endl;

    int totalCusto = 0, totalDist = 0, totalTempo = 0;
    for (size_t i = 0; i < agm.size(); i++) {
        cout << "  " << (i + 1) << ". " << g.sigla[agm[i].u] << " <-> " << g.sigla[agm[i].v]
             << "  [" << agm[i].transporte << "]"
             << "  (R$ " << agm[i].peso[CUSTO]
             << " | " << agm[i].peso[DISTANCIA] << " km"
             << " | " << horas(agm[i].peso[TEMPO]) << ")" << endl;
        totalCusto += agm[i].peso[CUSTO];
        totalDist += agm[i].peso[DISTANCIA];
        totalTempo += agm[i].peso[TEMPO];
    }

    cout << endl;
    cout << "Custo total:     R$ " << totalCusto << endl;
    cout << "Distancia total: " << totalDist << " km" << endl;
    cout << "Tempo total:     " << horas(totalTempo) << endl << endl;
}