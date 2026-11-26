# Eurotrip – AV2 Grafos (Estrutura de Dados Não Lineares)

Modelagem e otimização de uma viagem saindo de **Curitiba (Brasil)** com destino final em **Roma (Itália)**, passando por **7 países europeus** (Portugal, Espanha, França, Holanda, Alemanha, Suíça e Itália).

O grafo tem **14 vértices** (4 no Brasil e 10 na Europa) e **31 arestas**. Cada aresta tem três pesos (**custo**, **distância** e **tempo**) e o **meio de transporte** usado no trecho.

---

## Estrutura do projeto

| Arquivo | Conteúdo |
|---|---|
| `grafo.h` | Grafo em **lista de adjacência**; impressão das 3 matrizes (custo, distância, tempo); verificação de **conexidade (DFS)** e de **grau mínimo 3** |
| `caminhos_minimos.h` | **Dijkstra** com `priority_queue`, executado uma vez para cada critério (custo, distância, tempo) |
| `arvore_geradora.h` | **Prim** para a **Árvore Geradora Mínima** por custo |
| `main.cpp` | Cadastro dos vértices e arestas e execução das 3 partes |

Somente a biblioteca padrão do C++ é usada (`<vector>`, `<list>`, `<queue>` etc.).

## Como compilar e executar

```bash
g++ -Wall -std=c++11 main.cpp -o eurotrip
./eurotrip
```

---

## Modelagem do grafo

### Vértices

| Sigla | Local | País |
|---|---|---|
| CWB | Curitiba (partida) | Brasil |
| GRU | São Paulo – Guarulhos | Brasil |
| VCP | Campinas – Viracopos | Brasil |
| GIG | Rio de Janeiro – Galeão | Brasil |
| LIS | Lisboa | Portugal |
| MAD | Madri | Espanha |
| BCN | Barcelona | Espanha |
| PAR | Paris | França |
| AMS | Amsterdã | Holanda |
| BER | Berlim | Alemanha |
| MUC | Munique | Alemanha |
| ZRH | Zurique | Suíça |
| MIL | Milão | Itália |
| ROM | Roma (destino final) | Itália |

**Por que GRU, VCP e GIG?** Curitiba não tem voo direto para a Europa. Todo viajante sai por um hub internacional, então a modelagem obriga essa conexão. Com três hubs, Curitiba fica com grau 3, como o enunciado exige, e o algoritmo pode escolher a saída mais vantajosa.

### Pesos das arestas

- **Custo (R$):** passagem só de ida, por pessoa.
- **Distância (km):** distância aérea para voos e distância do percurso para trem e ônibus.
- **Tempo (horas):** tempo de deslocamento do veículo. No código fica guardado em minutos (inteiro) e é sempre exibido em horas (`11h40`). No `main.cpp` é escrito com `h(horas, minutos)`.

### Meios de transporte

| Meio | Onde é usado | Por quê |
|---|---|---|
| **Avião** | Voos domésticos, intercontinentais e trechos longos na Europa (LIS–BCN, MAD–PAR, BER–ROM…) | Única opção para cruzar o oceano; na Europa compensa quando não há trem rápido |
| **Trem** | MAD–BCN (AVE), PAR–AMS, PAR–ZRH, BER–MUC (ICE), MIL–ROM (Frecciarossa)… | Trens de alta velocidade são rápidos, saem do centro da cidade e custam pouco |
| **Ônibus** | GRU–VCP, LIS–MAD, MUC–MIL | Opção mais barata, porém mais lenta (ex.: Lisboa–Madri não tem trem direto) |

Isso explica pesos que pareceriam incoerentes sem o meio de transporte. Por exemplo, Lisboa–Madri (ônibus, 8h30) demora mais que Lisboa–Barcelona (avião, 1h50), mesmo sendo mais perto, mas custa menos da metade.

### Validações (Parte 1)

- **Conexo:** sim (DFS a partir de CWB visita os 14 vértices).
- **Grau mínimo:** todos os vértices têm grau ≥ 3.
- **Matrizes:** o programa imprime as matrizes de custo, distância e tempo (`-` = sem ligação direta).

---

## Resultados

### Parte 2 – Caminhos mínimos (Dijkstra), Curitiba → Roma

| Critério | Rota | Custo | Distância | Tempo |
|---|---|---|---|---|
| **Custo** | CWB → VCP → LIS → BCN → ROM | **R$ 5.570** | 10.170 km | 14h35 |
| **Distância** | CWB → GRU → ROM | R$ 5.750 | **9.840 km** | 12h45 |
| **Tempo** | CWB → GRU → ROM | R$ 5.750 | 9.840 km | **12h45** |

- **Menor custo:** sai por Viracopos, que tem o voo mais barato para Lisboa, e segue de avião até Barcelona e depois Roma.
- **Menor distância e menor tempo:** dão a mesma rota, o voo direto Guarulhos–Roma. Faz sentido, porque o trecho intercontinental domina os dois critérios e a rota mais curta em km também é a de menos horas de voo.

### Parte 3 – Árvore Geradora Mínima (Prim, por custo)

13 arestas ligam os 14 vértices:

| # | Ligação | Transporte | Custo | Distância | Tempo |
|---|---|---|---|---|---|
| 1 | CWB – VCP | Avião | R$ 400 | 360 km | 1h05 |
| 2 | VCP – GRU | Ônibus | R$ 60 | 95 km | 1h30 |
| 3 | VCP – GIG | Avião | R$ 380 | 420 km | 1h10 |
| 4 | VCP – LIS | Avião | R$ 4.100 | 7.950 km | 9h50 |
| 5 | LIS – MAD | Ônibus | R$ 240 | 625 km | 8h30 |
| 6 | MAD – BCN | Trem | R$ 380 | 620 km | 2h30 |
| 7 | BCN – MIL | Avião | R$ 480 | 725 km | 1h30 |
| 8 | MIL – MUC | Ônibus | R$ 230 | 590 km | 7h30 |
| 9 | MIL – ZRH | Trem | R$ 280 | 280 km | 3h20 |
| 10 | MIL – ROM | Trem | R$ 350 | 575 km | 3h10 |
| 11 | MUC – BER | Trem | R$ 380 | 585 km | 4h |
| 12 | BER – AMS | Trem | R$ 400 | 650 km | 6h20 |
| 13 | AMS – PAR | Trem | R$ 450 | 515 km | 3h20 |
| | **Total** | | **R$ 8.130** | 13.990 km | 53h45 |

Na Europa, a AGM escolhe sobretudo **trem e ônibus**, que são os trechos mais baratos. Só um voo intercontinental entra na árvore (VCP–LIS, o mais barato). Milão vira o centro da malha, ligando Barcelona, Munique, Zurique e Roma.

> A AGM não é um roteiro sequencial: ela é a rede mais barata que conecta todos os destinos. Para percorrê-la em ordem, alguns trechos seriam repetidos.

---

## Análise e conclusão

- **Custo × tempo:** a rota mais barata economiza **R$ 180 por pessoa** (R$ 540 para o trio), mas leva **1h50 a mais** de deslocamento e tem **2 conexões extras** (Lisboa e Barcelona).
- **Distância e tempo coincidem** porque o trecho sobre o oceano pesa muito mais que qualquer outro. Quem voa direto para Roma percorre menos km e passa menos horas no avião.
- **Critério mais vantajoso:** para chegar a Roma, o grupo considera o **tempo** (voo direto por GRU) o melhor, porque a economia da rota barata é pequena perto do risco e do cansaço de três voos com conexão. Para o **roteiro dentro da Europa**, o **custo** é o critério que mais pesa: a AGM mostra que trens e ônibus ligam os 7 países gastando pouco.
- **Limitação do modelo:** o tempo considera só o deslocamento do veículo. Ele não inclui espera em conexões, check-in e deslocamento até aeroportos ou estações. Isso favorece rotas com muitas escalas e prejudica o trem, que sai do centro da cidade.

---

## Uso de Inteligência Artificial

Conforme exigido nas instruções da avaliação:

- **Ferramenta:** Claude (Anthropic), via Claude Code.
- **Onde foi usada:** revisão do grafo (inclusão dos hubs GRU/VCP/GIG, definição dos meios de transporte e ajuste dos pesos), exibição do tempo em horas, inclusão do meio de transporte na saída do programa e reescrita deste README.
- **Responsabilidade:** o grupo revisou, entende e sabe explicar todo o código e os dados entregues.
