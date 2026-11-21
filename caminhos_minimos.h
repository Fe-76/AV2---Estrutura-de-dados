#pragma once

void dijkstra(Grafo& g, int origem, int criterio, vector<int>& d, vector<int>& pai) {
    d.assign(g.n, INT_MAX);
    pai.assign(g.n, -1);
    d[origem] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila;
    fila.push(make_pair(0, origem));

    while (!fila.empty()) {
        int valorAtual = fila.top().first;
        int u = fila.top().second;
        fila.pop();


        if (valorAtual > d[u])
            continue;

        for (Aresta a : g.adj[u]) {
            int novo = d[u] + a.peso[criterio];
            if (novo < d[a.destino]) {
                d[a.destino] = novo;
                pai[a.destino] = u;
                fila.push(make_pair(novo, a.destino));
            }
        }
    }
}


vector<int> montarCaminho(vector<int>& pai, int destino) {
    vector<int> caminho;
    int atual = destino;
    while (atual != -1) {
        caminho.insert(caminho.begin(), atual);
        atual = pai[atual];
    }
    return caminho;
}


void somarCaminho(Grafo& g, vector<int>& caminho, int criterio, int total[3]) {
    total[CUSTO] = 0;
    total[DISTANCIA] = 0;
    total[TEMPO] = 0;
    for (int i = 0; i + 1 < (int)caminho.size(); i++) {
        int u = caminho[i];
        int v = caminho[i + 1];

        bool achou = false;
        Aresta melhor;
        for (Aresta a : g.adj[u]) {
            if (a.destino == v) {
                if (!achou || a.peso[criterio] < melhor.peso[criterio]) {
                    melhor = a;
                    achou = true;
                }
            }
        }
        for (int c = 0; c < 3; c++)
            total[c] += melhor.peso[c];
    }
}

void mostrarCaminhoMinimo(Grafo& g, int origem, int destino, int criterio, string titulo) {
    vector<int> d;
    vector<int> pai;
    dijkstra(g, origem, criterio, d, pai);

    cout << "=== Menor caminho por " << titulo << " ===" << endl;

    if (d[destino] == INT_MAX) {
        cout << "Nao existe caminho ate o destino." << endl << endl;
        return;
    }

    vector<int> caminho = montarCaminho(pai, destino);
    cout << "Rota: ";
    for (int i = 0; i < (int)caminho.size(); i++) {
        cout << g.sigla[caminho[i]];
        if (i + 1 < (int)caminho.size())
            cout << " -> ";
    }
    cout << endl;

    int total[3];
    somarCaminho(g, caminho, criterio, total);
    cout << "Custo total:     R$ " << total[CUSTO] << endl;
    cout << "Distancia total: " << total[DISTANCIA] << " km" << endl;
    cout << "Tempo total:     " << horas(total[TEMPO]) << endl << endl;
}


void mostrarTodosCaminhosMinimos(Grafo& g, int origem, int destino) {
    cout << "Origem: " << g.nome[origem] << endl;
    cout << "Destino: " << g.nome[destino] << endl << endl;
    mostrarCaminhoMinimo(g, origem, destino, CUSTO, "CUSTO");
    mostrarCaminhoMinimo(g, origem, destino, DISTANCIA, "DISTANCIA");
    mostrarCaminhoMinimo(g, origem, destino, TEMPO, "TEMPO");
}
