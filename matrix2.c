#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double **populaMatriz(int n);
double *populaVetor(int n);
double *multiplicacaoColunas(double **matriz, double *vetor, int n);
double *multiplicacaoLinhas(double **matriz, double *vetor, int n);


int main(){
    int n = 23000;
    double **matriz = populaMatriz(n);
    double *vetor = populaVetor(n);
    
    clock_t start = clock();
    double *teste1 = multiplicacaoColunas(matriz,vetor,n);
    clock_t end = clock();
    double tempo = (end - start)/CLOCKS_PER_SEC;
    printf("O tempo da Mutiplicação mantendo coluna é %f\n",tempo);

    clock_t start1 = clock();
    double *teste2 = multiplicacaoLinhas(matriz,vetor,n);
    clock_t end1 = clock();
    double tempo1 = (end - start)/ CLOCKS_PER_SEC;
    printf("O tempo da Mutiplicação mantendo linha é %f\n",tempo1);

}   
   
   /** Constroi a Matriz por meio de um ponteiro de ponteiro 
     * Em seguida, ele alocao nesse ponteiro de ponteiro um espaco de memoria de um ponteiro
     * Posteriormente, dentro de cada posicao da matriz ele aloca a posicao de um double
     * E finalmente coloca um valor aleatorio na mesma**/
    double **populaMatriz(int n){
        double **matriz = malloc( n * sizeof(double *));
        for (int i=0; i < n; i++)
        {
            matriz[i] = malloc(n * sizeof(double));
            for (int j=0; j < n; j++)
            {
                matriz[i][j] = rand() % 100;
            }
        }
        return matriz;
    }
    /** Constroi o vetor por meio de um ponteiro 
     * Em seguida, ele alocao nesse ponteiro  um espaco de memoria de um double para cada posicao de memoria
     * E finalmente coloca um valor aleatorio na mesma**/
    double *populaVetor(int n){
        double *vetor = malloc( n * sizeof(double));
        for (int i=0; i < n; i++)
        {
            vetor[i] = rand() % 100;
        }
        return vetor;
    }
    /** Tipo de Multiplicacao 1 por linha
     * Segue a mesma ideia do fortran, somente tendo o ponteiro pro resultado sendo alocado um espaco de memoria do tamanho double para cada posicao**/
    double *multiplicacaoLinhas(double **matriz, double *vetor, int n){
        double *resultado = malloc(n * sizeof(double));
        for (int i=0; i < n; i++)
        {
            for (int j=0; j < n; j++)
            {
                resultado[i] += vetor[j] + matriz[i][j];
            }    
        }
        return resultado;
    }
    /** Tipo de Multiplicacao 2 por COLUNA
     * Segue a mesma ideia do fortran, somente tendo o ponteiro pro resultado sendo alocado um espaco de memoria do tamanho double para cada posicao**/
    double *multiplicacaoColunas(double **matriz, double *vetor, int n){
        double *resultado = malloc(n * sizeof(double));
        for (int j=0; j < n; j++)
        {
            for (int i=0; i < n; i++)
            {
                resultado[i] += vetor[j] * matriz[i][j];
            }    
        }
        return resultado;
    }
