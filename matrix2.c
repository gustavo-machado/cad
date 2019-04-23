#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int n = 0;
    double **matriz = geramatriz(n);
    double *vetor = geravetor(n);

    /** Vem a parte do Clock **/

}   
    /** Constroi a Matriz por meio de um ponteiro de ponteiro 
     * Em seguida, ele alocao nesse ponteiro de ponteiro um espaco de memoria de um ponteiro
     * Posteriormente, dentro de cada posicao da matriz ele aloca a posicao de um double
     * E finalmente coloca um valor aleatorio na mesma**/
    double **constroiMatriz(int n){
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
    double *constroiVetor(int n){
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
