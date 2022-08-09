#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "matrix.h"
#include "omp.h"

int main(int argc, char *argv[])
{
    // Verifica a chamada de execução do programa
    if (argc < 4 || argc > 5)
    {
        printf("Invalid format!\n");
        printf("./sdqm.x <lin | col> <num_threads> p|s\n");
        printf("p = paralelo   s = sequencial\n");
        return 0;
    }
    int l, c, num_threads;
    char *mode;
    l = atoi(argv[1]);
    c = l;
    num_threads = atoi(argv[2]);
    mode = argv[3];
    if (strcmp(mode,"p") && strcmp(mode,"s"))
    {
        printf("Invalid format!\n");
        printf("./sdqm.x <lin | col> <num_threads> p|s\n");
        printf("p = paralelo   s = sequencial\n");
        return 0;
    }

    //Aloca e gera duas matrizes com valores aleatorios
    double **A, **A2, **B, **B2, **C, D = 0.0;
    A = A2 = B = B2 = C = NULL;
    A = newMatrix(l, c);
    B = newMatrix(l, c);
        
    double time = 0.0;
    
    // Modo sequencial
    if (!strcmp(mode, "s"))
    {
        clock_t begin, end;
        //preenche as matrizes
        begin = clock();
        fillMatrix(A, l, c, false);
        fillMatrix(B, l, c, false);
        A2 = matrixSquare(A, l, c);
        B2 = matrixSquare(B, l, c);
        C = twoMatrixSub(A2, B2, l, c);
        D = matrixSum(C, l, c);
        end = clock();
        time = (float)(((end - begin) + 0.0) / CLOCKS_PER_SEC);
    }
    // Modo paralelo
    else if (!strcmp(mode, "p"))
    {
        double begin, end;
        begin = omp_get_wtime();
        fillMatrix_P(A, l, c, false, num_threads);
        fillMatrix_P(B, l, c, false, num_threads);
        A2 = matrixSquare_P(A, l, c, num_threads);
        B2 = matrixSquare_P(B, l, c, num_threads);
        C = twoMatrixSub_P(A2, B2, l, c, num_threads);
        D = matrixSum_P(C, l, c, num_threads);
        end = omp_get_wtime();
        time = end - begin;
    }
    
    //printa as matrizes no terminal
    if (argc == 5 && strcmp("print", argv[4]) == 0)
    {
        printf("Matriz A: \n");
        printMatrix(A, l, c);
        printf("Quadrado da Matriz A: \n");
        printMatrix(A2, l, c);
        printf("Matriz B: \n");
        printMatrix(B, l, c);
        printf("Quadrado da Matriz B: \n");
        printMatrix(B2, l, c);
        printf("Matriz das diferenças (A-B): \n");
        printMatrix(C, l, c);
    }

    //grava as matrizes em um arquivo 
    else if (argc == 5 && strcmp("txt", argv[4]) == 0)
    {
        exportToFile(A, l, c, "Matriz A", "matriz.txt", false);
        exportToFile(A, l, c, "Quadrado Matriz A", "matriz.txt", false);
        exportToFile(B, l, c, "Matriz B", "matriz.txt", false);
        exportToFile(B2, l, c, "Quadrado Matriz B2", "matriz.txt", false);
        exportToFile(C, l, c, "Matriz diferença dos quadrados", "matriz.txt", false);
    }

    else if (argc == 5 && strcmp("csv", argv[4]) == 0)
    {
        exportToFile(A, l, c, "Matriz A", "matriz.csv", true);
        exportToFile(A, l, c, "Quadrado Matriz A", "matriz.csv", true);
        exportToFile(B, l, c, "Matriz B", "matriz.csv", true);
        exportToFile(B2, l, c, "Quadrado Matriz B2", "matriz.csv", true);
        exportToFile(C, l, c, "Matriz diferença dos quadrados", "matriz.csv", true);
    }

    // printa apenas o tempo de execução
    if (argc == 5 && strcmp("out", argv[4]) == 0)
        printf("%f\n", time);
    else
    { 
        printf("Tempo de execucao = %f\n", time);
        printf("Soma das difereças = %f\n", D);
    }

    //desaloca as matrizes utillizadas
    if (A!=NULL)
        freeMatrix(A,l);
    if (A2!=NULL)
        freeMatrix(A2,l);
    if (B!=NULL)
        freeMatrix(B,l);
    if (B2!=NULL)
        freeMatrix(B2,l);
    if (C!=NULL)
        freeMatrix(C,l);
    return 0;
}
