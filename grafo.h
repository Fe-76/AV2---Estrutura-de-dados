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

// Cada aresta guarda o destino, os 3 pesos e o meio de transporte.
// Custo em R$, distancia em km e tempo em minutos (exibido sempre em horas).
struct Aresta {
    int destino;
    int peso[3];
    string transporte;
};

// Converte horas + minutos para minutos. Ex.: h(11, 40) = 700.
// Usado no cadastro das arestas para escrever o tempo em horas.
inline int h(int horas, int minutos = 0) {
    return horas * 60 + minutos;
}

// Formata minutos como horas. Ex.: 700 -> "11h40", 120 -> "2h".
inline string horas(int minutos) {
    string s = to_string(minutos / 60) + "h";
    int resto = minutos % 60;
    if (resto > 0)
        s += (resto < 10 ? "0" : "") + to_string(resto);
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

    // Grafo nao direcionado: a aresta e inserida nas duas listas.
    void adicionarAresta(int u, int v, string transporte, int custo, int km, int minutos) {
        adj[u].push_back({v, {custo, km, minutos}, transporte});
        adj[v].push_back({u, {custo, km, minutos}, transporte});
        numArestas++;
    }

    void imprimirLista() const {
        cout << "Lista de Adjacencia:" << endl;
        for (int u = 0; u < n; u++) {
            cout << sigla[u] << endl;
            for (const auto& a : adj[u]) {
                cout << "   -> " << sigla[a.destino] << "  [" << a.transporte << "]  R$ "
                     << a.peso[CUSTO] << " | " << a.peso[DISTANCIA] << " km | "
                     << horas(a.peso[TEMPO]) << endl;
            }
        }
    }

    void imprimirMatriz(int c) const {
        vector<vector<int>> m(n, vector<int>(n, INT_MAX));
        for (int u = 0; u < n; u++) {
            m[u][u] = 0;
            for (const auto& a : adj[u])
                m[u][a.destino] = a.peso[c];
        }

        const int L = 7;
        cout << setw(L) << "i/j";
        for (int j = 0; j < n; j++)
            cout << setw(L) << sigla[j];
        cout << endl;

        for (int i = 0; i < n; i++) {
            cout << setw(L) << sigla[i];
            for (int j = 0; j < n; j++) {
                if (m[i][j] == INT_MAX)
                    cout << setw(L) << "-";
                else if (c == TEMPO)
                    cout << setw(L) << horas(m[i][j]);
                else
                    cout << setw(L) << m[i][j];
            }
            cout << endl;
        }
    }

    void dfs(int u, vector<bool>& visitado) const {
        visitado[u] = true;
        for (const auto& a : adj[u]) {
            if (!visitado[a.destino])
                dfs(a.destino, visitado);
        }
    }

    bool ehConexo() const {
        if (n == 0) return true;
        vector<bool> visitado(n, false);
        dfs(0, visitado);
        for (int i = 0; i < n; i++) {
            if (!visitado[i]) return false;
        }
        return true;
    }

    bool grauMinimo(int minimo) const {
        bool ok = true;
        for (int u = 0; u < n; u++) {
            cout << sigla[u] << ": grau " << adj[u].size() << endl;
            if ((int)adj[u].size() < minimo)
                ok = false;
        }
        return ok;
    }
};
