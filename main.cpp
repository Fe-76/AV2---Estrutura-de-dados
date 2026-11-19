#include "grafo.h"

int main() {
    Grafo g;

    int CWB = g.adicionarVertice("CWB", "Curitiba, Brasil");
    int LIS = g.adicionarVertice("LIS", "Lisboa, Portugal");
    int MAD = g.adicionarVertice("MAD", "Madri, Espanha");
    int BCN = g.adicionarVertice("BCN", "Barcelona, Espanha");
    int PAR = g.adicionarVertice("PAR", "Paris, Franca");
    int AMS = g.adicionarVertice("AMS", "Amsterda, Holanda");
    int BER = g.adicionarVertice("BER", "Berlim, Alemanha");
    int MUC = g.adicionarVertice("MUC", "Munique, Alemanha");
    int ZRH = g.adicionarVertice("ZRH", "Zurique, Suica");
    int MIL = g.adicionarVertice("MIL", "Milao, Italia");
    int ROM = g.adicionarVertice("ROM", "Roma, Italia");

    // custo em reais, distancia em km, tempo em minutos
    g.adicionarAresta(CWB, LIS, 4200, 8250, 780);
    g.adicionarAresta(CWB, MAD, 4600, 8650, 840);
    g.adicionarAresta(CWB, PAR, 5100, 9650, 900);
    g.adicionarAresta(CWB, ROM, 5600, 9750, 960);
    g.adicionarAresta(LIS, MAD, 240, 625, 480);
    g.adicionarAresta(LIS, BCN, 520, 1000, 120);
    g.adicionarAresta(LIS, PAR, 650, 1740, 150);
    g.adicionarAresta(MAD, BCN, 380, 620, 150);
    g.adicionarAresta(MAD, PAR, 600, 1050, 120);
    g.adicionarAresta(BCN, PAR, 700, 1035, 390);
    g.adicionarAresta(BCN, MIL, 480, 725, 90);
    g.adicionarAresta(BCN, ROM, 550, 860, 120);
    g.adicionarAresta(PAR, AMS, 450, 515, 210);
    g.adicionarAresta(PAR, ZRH, 600, 610, 240);
    g.adicionarAresta(AMS, BER, 400, 650, 390);
    g.adicionarAresta(AMS, MUC, 550, 670, 90);
    g.adicionarAresta(BER, MUC, 380, 585, 240);
    g.adicionarAresta(BER, ROM, 650, 1180, 150);
    g.adicionarAresta(MUC, ZRH, 300, 315, 210);
    g.adicionarAresta(MUC, MIL, 230, 590, 450);
    g.adicionarAresta(ZRH, MIL, 280, 280, 210);
    g.adicionarAresta(MIL, ROM, 350, 575, 180);

    cout << "=== GRAFO ORIGINAL ===" << endl;
    cout << "Vertices: " << g.n << "  Arestas: " << g.numArestas << endl << endl;
    for (int i = 0; i < g.n; i++)
        cout << g.sigla[i] << " - " << g.nome[i] << endl;
    cout << endl;

    g.imprimirLista();
    cout << endl;

    cout << "Grafo conexo: " << (g.ehConexo() ? "sim" : "nao") << endl;
    bool graus = g.grauMinimo(3);
    cout << "Todos os vertices com grau >= 3: " << (graus ? "sim" : "nao") << endl << endl;

    cout << "=== MATRIZ DE CUSTO (R$) ===" << endl;
    g.imprimirMatriz(CUSTO);
    cout << endl << "=== MATRIZ DE DISTANCIA (km) ===" << endl;
    g.imprimirMatriz(DISTANCIA);
    cout << endl << "=== MATRIZ DE TEMPO (minutos) ===" << endl;
    g.imprimirMatriz(TEMPO);

    return 0;
}
