#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <string>
#include <climits>
using namespace std;

const int CUSTO = 0;
const int DISTANCIA = 1;
const int TEMPO = 2;

struct Aresta {
    int destino;
    int peso[3];
};

string horas(int minutos) {
    string s = to_string(minutos / 60) + "h";
    if (minutos % 60 > 0)
        s += to_string(minutos % 60) + "min";
    return s;
}

class Grafo {
public:
    int n = 0;
    int numArestas = 0;
    vector<string> sigla;
    vector<string> nome;
    vector<list<Aresta>> adj;

    int adicionarVertice(string s, string nomeLocal) {
        sigla.push_back(s);
        nome.push_back(nomeLocal);
        adj.push_back(list<Aresta>());
        n++;
        return n - 1;
    }

    void adicionarAresta(int u, int v, int custo, int km, int minutos) {
        adj[u].push_back({v, {custo, km, minutos}});
        adj[v].push_back({u, {custo, km, minutos}});
        numArestas++;
    }

    void imprimirLista() {
        cout << "Lista de adjacencia (custo R$ | distancia | tempo)" << endl;
        for (int u = 0; u < n; u++) {
            cout << sigla[u];
            for (Aresta a : adj[u]) {
                cout << " -> " << sigla[a.destino] << " (R$ " << a.peso[CUSTO] << " | "
                     << a.peso[DISTANCIA] << " km | " << horas(a.peso[TEMPO]) << ")";
            }
            cout << endl;
        }
    }

    vector<vector<int>> matriz(int c) {
        vector<vector<int>> m(n, vector<int>(n, INT_MAX));
        for (int u = 0; u < n; u++) {
            m[u][u] = 0;
            for (Aresta a : adj[u])
                m[u][a.destino] = a.peso[c];
        }
        return m;
    }

    void imprimirMatriz(int c) {
        vector<vector<int>> m = matriz(c);
        cout << setw(6) << "i/j";
        for (int j = 0; j < n; j++)
            cout << setw(6) << sigla[j];
        cout << endl;
        for (int i = 0; i < n; i++) {
            cout << setw(6) << sigla[i];
            for (int j = 0; j < n; j++) {
                if (m[i][j] == INT_MAX)
                    cout << setw(6) << "inf";
                else
                    cout << setw(6) << m[i][j];
            }
            cout << endl;
        }
    }

    void dfs(int u, vector<bool>& visitado) {
        visitado[u] = true;
        for (Aresta a : adj[u])
            if (!visitado[a.destino])
                dfs(a.destino, visitado);
    }

    bool ehConexo() {
        vector<bool> visitado(n, false);
        dfs(0, visitado);
        for (int i = 0; i < n; i++)
            if (!visitado[i])
                return false;
        return true;
    }

    bool grauMinimo(int minimo) {
        bool ok = true;
        for (int u = 0; u < n; u++) {
            cout << sigla[u] << ": grau " << adj[u].size() << endl;
            if ((int)adj[u].size() < minimo)
                ok = false;
        }
        return ok;
    }
};
