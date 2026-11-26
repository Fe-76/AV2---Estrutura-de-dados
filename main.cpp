#include "grafo.h"
#include "caminhos_minimos.h"
#include "arvore_geradora.h"

int main() {
    Grafo g;

    // ---------- Vertices ----------
    // Brasil: Curitiba nao tem voo direto para a Europa, entao a saida
    // passa por um dos hubs internacionais (Guarulhos, Viracopos ou Galeao).
    int CWB = g.adicionarVertice("CWB", "Curitiba, Brasil (partida)");
    int GRU = g.adicionarVertice("GRU", "Sao Paulo-Guarulhos, Brasil");
    int VCP = g.adicionarVertice("VCP", "Campinas-Viracopos, Brasil");
    int GIG = g.adicionarVertice("GIG", "Rio de Janeiro-Galeao, Brasil");

    // Europa: 7 paises
    int LIS = g.adicionarVertice("LIS", "Lisboa, Portugal");
    int MAD = g.adicionarVertice("MAD", "Madri, Espanha");
    int BCN = g.adicionarVertice("BCN", "Barcelona, Espanha");
    int PAR = g.adicionarVertice("PAR", "Paris, Franca");
    int AMS = g.adicionarVertice("AMS", "Amsterda, Holanda");
    int BER = g.adicionarVertice("BER", "Berlim, Alemanha");
    int MUC = g.adicionarVertice("MUC", "Munique, Alemanha");
    int ZRH = g.adicionarVertice("ZRH", "Zurique, Suica");
    int MIL = g.adicionarVertice("MIL", "Milao, Italia");
    int ROM = g.adicionarVertice("ROM", "Roma, Italia (destino final)");

    // ---------- Arestas ----------
    // adicionarAresta(origem, destino, transporte, custo R$, distancia km, tempo h(horas, min))
    // Custo por pessoa (passagem so de ida). Tempo = tempo de deslocamento do veiculo.

    // Trechos domesticos no Brasil
    g.adicionarAresta(CWB, GRU, "Aviao",  450,  340, h(1, 5));
    g.adicionarAresta(CWB, VCP, "Aviao",  400,  360, h(1, 5));
    g.adicionarAresta(CWB, GIG, "Aviao",  550,  680, h(1, 30));
    g.adicionarAresta(GRU, VCP, "Onibus",  60,   95, h(1, 30));
    g.adicionarAresta(GRU, GIG, "Aviao",  400,  340, h(1, 5));
    g.adicionarAresta(VCP, GIG, "Aviao",  380,  420, h(1, 10));

    // Voos intercontinentais (rotas diretas que existem)
    g.adicionarAresta(GRU, LIS, "Aviao", 4300, 7950, h(10, 0));
    g.adicionarAresta(GRU, MAD, "Aviao", 4500, 8370, h(10, 30));
    g.adicionarAresta(GRU, PAR, "Aviao", 5000, 9400, h(11, 15));
    g.adicionarAresta(GRU, ROM, "Aviao", 5300, 9500, h(11, 40));
    g.adicionarAresta(VCP, LIS, "Aviao", 4100, 7950, h(9, 50));
    g.adicionarAresta(GIG, LIS, "Aviao", 4400, 7700, h(9, 40));
    g.adicionarAresta(GIG, PAR, "Aviao", 5100, 9150, h(11, 0));

    // Trechos dentro da Europa
    g.adicionarAresta(LIS, MAD, "Onibus", 240,  625, h(8, 30));
    g.adicionarAresta(LIS, BCN, "Aviao",  520, 1000, h(1, 50));
    g.adicionarAresta(LIS, PAR, "Aviao",  650, 1450, h(2, 25));
    g.adicionarAresta(MAD, BCN, "Trem",   380,  620, h(2, 30));
    g.adicionarAresta(MAD, PAR, "Aviao",  600, 1050, h(2, 0));
    g.adicionarAresta(BCN, PAR, "Trem",   700, 1035, h(6, 30));
    g.adicionarAresta(BCN, MIL, "Aviao",  480,  725, h(1, 30));
    g.adicionarAresta(BCN, ROM, "Aviao",  550,  860, h(1, 50));
    g.adicionarAresta(PAR, AMS, "Trem",   450,  515, h(3, 20));
    g.adicionarAresta(PAR, ZRH, "Trem",   600,  610, h(4, 5));
    g.adicionarAresta(AMS, BER, "Trem",   400,  650, h(6, 20));
    g.adicionarAresta(AMS, MUC, "Aviao",  550,  670, h(1, 25));
    g.adicionarAresta(BER, MUC, "Trem",   380,  585, h(4, 0));
    g.adicionarAresta(BER, ROM, "Aviao",  650, 1180, h(2, 15));
    g.adicionarAresta(MUC, ZRH, "Trem",   300,  315, h(3, 30));
    g.adicionarAresta(MUC, MIL, "Onibus", 230,  590, h(7, 30));
    g.adicionarAresta(ZRH, MIL, "Trem",   280,  280, h(3, 20));
    g.adicionarAresta(MIL, ROM, "Trem",   350,  575, h(3, 10));

    cout << "========================================" << endl;
    cout << "       PARTE 1 - GRAFO ORIGINAL" << endl;
    cout << "========================================" << endl << endl;

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
    cout << endl << "=== MATRIZ DE TEMPO (horas) ===" << endl;
    g.imprimirMatriz(TEMPO);
    cout << endl;

    cout << "========================================" << endl;
    cout << "    PARTE 2 - CAMINHOS MINIMOS" << endl;
    cout << "========================================" << endl << endl;

    mostrarTodosCaminhosMinimos(g, CWB, ROM);

    cout << "========================================" << endl;
    cout << "  PARTE 3 - ARVORE GERADORA MINIMA" << endl;
    cout << "========================================" << endl << endl;

    mostrarAGM(g, CUSTO, "CUSTO (R$)");

    return 0;
}
