#pragma once
#include "grafo.h"
#include <queue>

inline void dijkstra(const Grafo& g, int origem, int criterio, vector<int>& d, vector<int>& pai) {
    d.assign(g.n, INT_MAX);
    pai.assign(g.n, -1);
    d[origem] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila;
    fila.push({0, origem});

    while (!fila.empty()) {
        int dist = fila.top().first;
        int u = fila.top().second;
        fila.pop();

        if (dist > d[u]) continue;

        for (const auto& a : g.adj[u]) {
            if (d[u] + a.peso[criterio] < d[a.destino]) {
                d[a.destino] = d[u] + a.peso[criterio];
                pai[a.destino] = u;
                fila.push({d[a.destino], a.destino});
            }
        }
    }
}

inline void mostrarCaminhoMinimo(const Grafo& g, int origem, int destino, int criterio, string titulo) {
    vector<int> d, pai;
    dijkstra(g, origem, criterio, d, pai);

    cout << "=== Menor caminho por " << titulo << " ===" << endl;

    vector<int> caminho;
    for (int v = destino; v != -1; v = pai[v])
        caminho.insert(caminho.begin(), v);

    cout << "Rota: ";
    for (size_t i = 0; i < caminho.size(); i++) {
        cout << g.sigla[caminho[i]];
        if (i + 1 < caminho.size()) cout << " -> ";
    }
    cout << endl;

    int total[3] = {0, 0, 0};
    for (size_t i = 0; i + 1 < caminho.size(); i++) {
        int u = caminho[i], v = caminho[i + 1];
        for (const auto& a : g.adj[u]) {
            if (a.destino == v) {
                total[CUSTO] += a.peso[CUSTO];
                total[DISTANCIA] += a.peso[DISTANCIA];
                total[TEMPO] += a.peso[TEMPO];
                break;
            }
        }
    }

    cout << "Custo total:     R$ " << total[CUSTO] << endl;
    cout << "Distancia total: " << total[DISTANCIA] << " km" << endl;
    cout << "Tempo total:     " << horas(total[TEMPO]) << endl << endl;
}

inline void mostrarTodosCaminhosMinimos(const Grafo& g, int origem, int destino) {
    cout << "Origem: " << g.nome[origem] << endl;
    cout << "Destino: " << g.nome[destino] << endl << endl;
    mostrarCaminhoMinimo(g, origem, destino, CUSTO, "CUSTO");
    mostrarCaminhoMinimo(g, origem, destino, DISTANCIA, "DISTANCIA");
    mostrarCaminhoMinimo(g, origem, destino, TEMPO, "TEMPO");
}