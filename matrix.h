#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "omp.h"

// Aloca cada linha da matriz em uma posição distinta na memória
double** newMatrix(int l, int c);

// Desaloca uma matriz
void freeMatrix(double **M, int l);

void printMatrix(double **M, int l, int c);

// Exporta uma matriz para um arquivo 
// csv = true -> exporta para csv; csv = false -> exporta para txt
void exportToFile(double **M, int l, int c, char *Matrix, char *filename, bool csv);

// =============================================== SEQUENCIAL =================================================

// Preenche a matriz com valores aleatórios
// seed = false -> valores repetem entre execuções
// seed = true -> valores aleatórios entre execuções
void fillMatrix(double **M, int l, int c, bool seed);

// Retorna uma matriz com o quadrado de todos os elementos de uma matriz passada como parâmetro
double** matrixSquare(double **M, int l, int c);

// Retorna a matriz das diferenças de duas matrizes
double** twoMatrixSub(double **A, double**B, int l, int c);

// Retorna a soma de todos os elementos de uma matriz
double matrixSum(double **M, int l, int c);

// ============================================= PARALELO ========================================

#define NUM_THREADS 4

// Preenche a matriz com valores aleatórios
// seed = false -> valores repetem entre execuções
// seed = true -> valores aleatórios entre execuções
void fillMatrix_P(double **M, int l, int c, bool seed, short num_threads);

// Retorna uma matriz com o quadrado de todos os elementos de uma matriz passada como parâmetro
double** matrixSquare_P(double **M, int l, int c, short num_threads);

// Retorna a matriz das diferenças de duas matrizes
double** twoMatrixSub_P(double **A, double**B, int l, int c, short num_threads);

// Retorna a soma de todos os elementos de uma matriz
double matrixSum_P(double **M, int l, int c, short num_threads);