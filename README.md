# Eurotrip - AV2 Grafos

Viagem saindo de **Curitiba** e terminando em **Roma**.

## O que já foi feito (Parte 1)

O "mapa" da viagem já está montado no programa:

- **11 cidades**, de Curitiba até Roma.
- **22 ligações** entre elas (voo, trem ou ônibus). Cada uma tem **preço** (R$), **distância** (km) e **tempo**.
- O programa mostra esse mapa de duas formas:
  - uma lista com as ligações de cada cidade;
  - **3 tabelas**: preço, distância e tempo.
- O programa também confere as regras do trabalho:
  - dá para chegar em qualquer cidade a partir de qualquer outra;
  - toda cidade tem pelo menos 3 ligações.

Arquivos:
- `grafo.h`: código do mapa.
- `main.cpp`: onde as cidades e as ligações são cadastradas.

Para compilar e rodar:

```
g++ -Wall main.cpp -o eurotrip
./eurotrip
```

## O que falta fazer

### Parte 2: menor caminho de Curitiba até Roma

- Fazer o algoritmo de Dijkstra.
- Rodar 3 vezes: menor preço, menor distância e menor tempo.
- Mostrar por quais cidades o caminho passa e quanto deu de preço, km e horas.

Resposta esperada:
- Menor preço: CWB → LIS → BCN → ROM, R$ 5270.
- Menor distância e menor tempo: voo direto CWB → ROM, 9750 km, 16h.

### Parte 3: ligar todas as cidades gastando o mínimo + PDF

- Fazer o algoritmo de Prim, usando o preço.
- Mostrar as ligações escolhidas e os totais de preço, km e horas.
- Montar o PDF de entrega com:
  - o desenho do mapa;
  - as 3 tabelas;
  - os resultados das Partes 2 e 3;
  - um comentário dizendo qual critério valeu mais a pena.

Resposta esperada: 10 ligações, total de R$ 7390.

### Para o grupo todo

- Compilar e testar. O programa ainda não foi rodado.
- Criar o repositório Git e cada um commitar a própria parte.
