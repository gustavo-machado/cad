# Computação de Alto Desempenho - 2019.1

Trabalhos 1 e 2 de CAD referentes a multiplicação de uma matriz por um vetor e suas diferentes implementações em C e Fortran, testando otimizações baseadas na ordem dos loops, utilização de OpenMP e transformação da matriz em um vetor, construído a partir de cada linha da matriz.

### Funções

A função matrix.f90 é a implementação do produto matriz vetor em Fortran sem otimizações. Realiza o cálculo desse produto tanto iterando pelas linhas como pelas colunas.

A função matrix.c é a implementação do produto matriz vetor em C sem otimizações. Realiza o cálculo desse produto tanto iterando pelas linhas como pelas colunas.

A função matrix2.c utiliza OpenMP para o cálculo do resultado utilizando multithreading. Realiza o cálculo desse produto tanto iterando pelas linhas como pelas colunas.

A função matrix2FlatCol.c utiliza OpenMP e transforma a matriz em um vetor. Realiza o cálculo desse produto iterando apenas pelas colunas.

A função matrix2FlatRow.c utiliza OpenMP e transforma a matriz em um vetor. Realiza o cálculo desse produto iterando apenas pelas linhas.

### Compilando

As funções matrix2.c, matrix2FlatCol.c e matrix2FlatRow.c foram compiladas da seguinte forma:

```
gcc -fopenmp nomedafuncao.c -o output
```

A função matrix.c e matrix.f90 apenas não utilizaram a flag -fopenmp.
