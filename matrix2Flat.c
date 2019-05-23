#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double **populaMatriz(int n);
double *populaVetor(int n);
double *multiplicacaoLinhas(double **matriz, double *vetor, int n, double *resultado, double *flatA);


int main(){
    int n = 1000;
    double **matriz = populaMatriz(n);
    double *vetor = populaVetor(n);
    double *resultado = malloc(n * sizeof(double));
    double flatA[n*n];

    clock_t start = clock();
    double *teste1 = multiplicacaoLinhas(matriz,vetor,n,resultado,flatA);
    clock_t end = clock();
    double tempo = (double)(end - start)/CLOCKS_PER_SEC;
    printf("O tempo da Multiplicacao mantendo coluna e %f\n",tempo);

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

    double *converteMatriz(int n, double **matriz){
        double *flatA = malloc (n * n * sizeof(double));
        #pragma omp parallel for
        for(int i = 0;i < n; i++){
            for (int j = 0;j < n; j++){
                flatA[i * n + j] = matriz[i][j]; 
            }
        }
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
    double *multiplicacaoLinhas(double **matriz, double *vetor, int n, double *resultado, double *flatA){
        #pragma omp parallel for num_threads(40)
        converteMatriz(n,matriz);
        for (int i=0; i < n; i++)
        {
            int ioff = i * n;
            int tot = 0; 
            for (int j=0; j < n; j++)
            {
                for (int k=0; k < n; k++){
                tot += flatA[ioff + k] * vetor[k];
                }
            resultado[i][j] = tot;
            }    
        }
        return resultado;
    }
