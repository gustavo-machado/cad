#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

double **populaMatriz(int n);
double *populaVetor(int n);
double *multiplicacaoColunas(double *vetor, int n, double *resultado, double *flatA);
void freeArray(double **matriz, int n);

int main(){
    int n = 10000;
    double **matriz = populaMatriz(n);
    double *vetor = populaVetor(n);
    double *resultado = malloc(n * sizeof(double));
    double *flatA = malloc(n * n * sizeof(double));
    #pragma omp parallel for
    for(int i = 0;i < n; i++){
        for (int j = 0;j < n; j++){
            flatA[j * n + i] = matriz[i][j];
        }
    }
    freeArray(matriz, n);

    struct timeval t0, t1;
	gettimeofday(&t0, 0);
    double *teste1 = multiplicacaoColunas(vetor,n,resultado,flatA);
    gettimeofday(&t1, 0);
    double elapsed = (t1.tv_sec-t0.tv_sec) * 1.0f + (t1.tv_usec - t0.tv_usec) / 1000000.0f;
    printf("O tempo da Multiplicacao mantendo coluna e %f\n",elapsed);

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
    double *multiplicacaoColunas(double *vetor, int n, double *resultado, double *flatA){
        double tot;
        int i, j, joff;
        #pragma omp parallel shared(resultado) private(i, j, joff, tot) num_threads(80)
        {
            #pragma omp for schedule(static)
            for (int j=0; j < n; j++)
            {
                joff = j * n;
                for (int i=0; i < n; i++)
                {   
                    tot = 0;
                    tot += flatA[joff + i] * vetor[j];
                    resultado[i] += tot;
                }
            }
        }
        return resultado;
    }

    void freeArray(double **matriz, int n) {
        int i;
        for (i = 0; i < n; ++i) {
                free(matriz[i]);
            }
        free(matriz);
    }

