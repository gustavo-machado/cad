#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

double **populaMatriz(int n);
double *populaVetor(int n);
double *multiplicacaoColunas(double **matriz, double *vetor, int n, double *resultado2);
double *multiplicacaoLinhas(double **matriz, double *vetor, int n, double *resultado1);


int main(){
    int n = 10000;
    double **matriz = populaMatriz(n);
    double *vetor = populaVetor(n);
    double *resultado1 = malloc(n * sizeof(double));
    double *resultado2 = malloc(n * sizeof(double));
    struct timeval t0, t1;
	gettimeofday(&t0, 0);
    double *teste1 = multiplicacaoColunas(matriz,vetor,n,resultado2);
    gettimeofday(&t1, 0);
    double elapsed = (t1.tv_sec-t0.tv_sec) * 1.0f + (t1.tv_usec - t0.tv_usec) / 1000000.0f;
    printf("O tempo da Multiplicacao mantendo coluna e %f\n",elapsed);

    struct timeval t3, t4;
	gettimeofday(&t3, 0);
    double *teste2 = multiplicacaoLinhas(matriz,vetor,n, resultado1);
    gettimeofday(&t4, 0);
    double elapsed2 = (t4.tv_sec-t3.tv_sec) * 1.0f + (t4.tv_usec - t3.tv_usec) / 1000000.0f;
    printf("O tempo da Multiplicacao mantendo linha e %f\n",elapsed2);
}   
   
   /** Constroi a Matriz por meio de um ponteiro de ponteiro 
     * Em seguida, ele alocao nesse ponteiro de ponteiro um espaco de memoria de um ponteiro
     * Posteriormente, dentro de cada posicao da matriz ele aloca a posicao de um double
     * E finalmente coloca um valor aleatorio na mesma**/
    double **populaMatriz(int n){
        double **matriz = malloc( n * sizeof(double *));
        #pragma omp parallel for
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
        #pragma omp parallel for
        for (int i=0; i < n; i++)
        {
            vetor[i] = rand() % 100;
        }
        return vetor;
    }
    /** Tipo de Multiplicacao 1 por linha
     * Segue a mesma ideia do fortran, somente tendo o ponteiro pro resultado sendo alocado um espaco de memoria do tamanho double para cada posicao**/
    double *multiplicacaoLinhas(double **matriz, double *vetor, int n, double *resultado1){
        
        double *resultado_privado = malloc(n * sizeof(double));
        #pragma omp parallel for num_threads(80)
        for (int i=0; i < n; i++)
        {
            for (int j=0; j < n; j++)
            {
                resultado_privado[i] += vetor[j] * matriz[i][j];
            }
        }

        #pragma omp critical
        for (int i=0; i < n; i++)
        {
            resultado1[i] += resultado_privado[i];
        }
        free(resultado_privado);
        return resultado1;
    }
    /** Tipo de Multiplicacao 2 por COLUNA
     * Segue a mesma ideia do fortran, somente tendo o ponteiro pro resultado sendo alocado um espaco de memoria do tamanho double para cada posicao**/
    double *multiplicacaoColunas(double **matriz, double *vetor, int n, double *resultado2){
        
        double *resultado_privado = malloc(n * sizeof(double));
        #pragma omp parallel for num_threads(40)
        for (int j=0; j < n; j++)
        {
            for (int i=0; i < n; i++)
            {
                resultado_privado[i] += vetor[j] * matriz[i][j];
            }    
        }
        #pragma omp critical
        for (int i=0; i < n; i++)
        {
            resultado2[i] += resultado_privado[i];
        }
        free(resultado_privado);
        return resultado2;
    }
