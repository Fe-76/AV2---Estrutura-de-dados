# Eurotrip - AV2 Grafos (Estrutura de Dados Não Lineares)

Projeto de modelagem e otimização de rotas para uma viagem partindo de **Curitiba (Brasil)** com destino final em **Roma (Itália)**, passando por 7 países europeus e 10 destinos na Europa (11 cidades no total, contando Curitiba).

---

## 📌 Estrutura do Projeto

O projeto é dividido nos seguintes arquivos:

- `grafo.h`: Estrutura de dados do grafo utilizando **Lista de Adjacência**, representação por matrizes de pesos (Custo, Distância e Tempo), validação de conexidade via **DFS** e verificação do grau mínimo dos vértices.
- `caminhos_minimos.h`: Implementação do algoritmo de **Dijkstra** com `priority_queue` para calcular e exibir a melhor rota em relação ao **Custo (R$)**, **Distância (km)** e **Tempo (horas)**.
- `arvore_geradora.h`: Implementação do algoritmo de **Prim** para encontrar a **Árvore Geradora Mínima (AGM)**, conectando todas as 11 cidades com o menor custo financeiro total.
- `main.cpp`: Ponto de entrada da aplicação, cadastro dos vértices, arestas e execução estruturada das 3 partes da avaliação.

---

## 🛠️ Como Compilar e Executar

Utilize um compilador C++11 ou superior:

```bash
g++ -Wall -std=c++11 main.cpp -o eurotrip
./eurotrip
```

---

## 📊 Resumo dos Resultados

### Parte 1: Representação do Grafo
- **Vértices:** 11 cidades (CWB, LIS, MAD, BCN, PAR, AMS, BER, MUC, ZRH, MIL, ROM).
- **Arestas:** 22 ligações bidirecionais com pesos triplos (R$, km, minutos).
- **Conexidade:** Grafo conexo (validado via DFS).
- **Grau mínimo:** Todos os vértices possuem grau $\ge 3$.
- **Matrizes:** Exibição das 3 matrizes de adjacência (Custo, Distância e Tempo).

### Parte 2: Caminhos Mínimos (Dijkstra) — Curitiba para Roma
- **Menor Custo:** `CWB -> LIS -> BCN -> ROM`  
  - **Custo Total:** R$ 5.270,00  
  - **Distância Total:** 10.110 km  
  - **Tempo Total:** 17h (1.020 min)
- **Menor Distância:** `CWB -> ROM` (Voo direto)  
  - **Distância Total:** 9.750 km  
  - **Custo Total:** R$ 5.600,00  
  - **Tempo Total:** 16h (960 min)
- **Menor Tempo:** `CWB -> ROM` (Voo direto)  
  - **Tempo Total:** 16h (960 min)  
  - **Custo Total:** R$ 5.600,00  
  - **Distância Total:** 9.750 km  

### Parte 3: Árvore Geradora Mínima (Prim)
- **Objetivo:** Interligar todas as 11 cidades gastando o mínimo possível.
- **Arestas Selecionadas:** 10 ligações otimizadas.
- **Custo Total da Malha:** **R$ 7.390,00**
- **Distância Total da Malha:** 13.415 km
- **Tempo Total em Deslocamentos:** 53h (3.180 min)

---

## 📝 Análise e Conclusão do Grupo

- **Critério Vantajoso para a Rota Direta (CWB $\rightarrow$ ROM):**  
  O critério de **Custo** é o mais vantajoso. Ao aceitar conexões em Lisboa e Barcelona, economiza-se **R$ 330,00** por pessoa em relação ao voo direto, adicionando apenas **1 hora** ao tempo total de viagem (17h contra 16h).

- **Otimização Geral da Viagem (AGM):**  
  Para realizar um mochilão completo passando pelos 10 destinos europeus em 7 países, o algoritmo de Prim garante que toda a rede viária de integração seja construída com um investimento mínimo de **R$ 7.390,00**.