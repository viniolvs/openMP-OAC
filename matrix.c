#include "matrix.h"

double** newMatrix(int l, int c)
{
    double **M;
       M = malloc (l * sizeof (double*)) ;
    int i;
    for (i=0; i < l; i++)
        M[i] = malloc (c * sizeof (double)) ;
    return M;
}

void freeMatrix(double **M, int l)
{
    int i;
    for (i = 0; i < l; i++)
        free(M[i]);
    free(M);
}

void printMatrix(double **M, int l, int c)
{
    int i, j;
    for (i = 0; i < l; i++)
    {
        printf("| ");
        for(j = 0; j < c; j++ )
            printf("%14.5lf ", M[i][j]);
        printf("|\n");
    }
    printf("\n");
}

void exportToFile(double **M, int l, int c, char *Matrix, char *filename, bool csv)
{
    FILE *file;
    file = fopen(filename,"a");

    int i,j;
    char buffer[100];

    fputs(Matrix, file);
    fputc('\n', file);

    for(i = 0; i < l; i++)
    {
        for (j = 0; j < c; j++)
        {
            sprintf(buffer, "%lf", M[i][j]);
            fputs(buffer, file);
            if(csv)
                fputc(',',file);
            else
                fputc(' ',file);
        }
        fputc('\n', file);
    }
    fputc('\n',file);
    fclose(file);
}

void fillMatrix(double **M, int l, int c, bool seed)
{
    int i,j;
    clock_t clk = clock();
    if (seed)
        srand(clk);
    for (i = 0; i < l; i++)
        for (j = 0; j < c; j++)
            M[i][j] = ((double)rand() * 1000.0) / ((double)RAND_MAX);
}

double** matrixSquare(double **M, int l, int c)
{
    double **M2 = newMatrix(l, c);
    int i, j;
    for (i = 0; i < l; i++)
        for ( j = 0; j < c; j++)
            M2[i][j] = M[i][j] * M[i][j];
    return M2;
}

double** twoMatrixSub(double **A, double**B, int l, int c)
{
    double **C = newMatrix(l, c);
    int i, j;
    for (i = 0; i < l; i++)
        for ( j = 0; j < c; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

double matrixSum(double **M, int l, int c)
{
    int i, j;
    double sum = 0.0;
    for (i = 0; i < l; i++)
        for ( j = 0; j < c; j++)
            sum += M[i][j];
    return sum;
}

void fillMatrix_P(double **M, int l, int c, bool seed, short num_threads)
{
    int i,j;
    clock_t clk = clock();
    omp_set_num_threads(num_threads);
    #pragma omp parallel shared(i, M, clk) private(j)
    if (seed)
        srand(clk);
    #pragma omp for
    for (i = 0; i < l; i++)
        for (j = 0; j < c; j++)
            M[i][j] = ((double)rand() * 1000.0) / ((double)RAND_MAX);
}

double** matrixSquare_P(double **M, int l, int c, short num_threads)
{
    double **M2 = newMatrix(l, c);
    int i, j;
    omp_set_num_threads(num_threads);
    #pragma omp parallel shared(i, M2, M) private(j)
    #pragma omp for
    for (i = 0; i < l; i++)
        for ( j = 0; j < c; j++)
            M2[i][j] = M[i][j] * M[i][j];
    return M2;
}

double** twoMatrixSub_P(double **A, double**B, int l, int c, short num_threads)
{
    double **C = newMatrix(l, c);
    int i, j;
    omp_set_num_threads(num_threads);
    #pragma omp parallel shared(i, C, A, B) private(j)
    #pragma omp for
    for (i = 0; i < l; i++)
        for ( j = 0; j < c; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

double matrixSum_P(double **M, int l, int c, short num_threads)
{
    int i, j;
    double sum = 0.0;
    omp_set_num_threads(num_threads);
    #pragma omp parallel shared(M, i) private(j) reduction(+:sum)
    #pragma omp for
    for (i = 0; i < l; i++)
        for ( j = 0; j < c; j++)
            sum += M[i][j];
    return sum;
}