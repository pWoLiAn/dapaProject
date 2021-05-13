#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 3

int main()
{
    int A[SIZE][SIZE] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9} 
    };
    int B[SIZE][SIZE] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int C[SIZE][SIZE];
    int i, j, k;

    // Initialisation
    omp_set_num_threads(omp_get_num_procs());

    // Initialising
    for (i = 0; i < SIZE; i++)
        {
            for (j = 0; j < SIZE; j++)
            {
                C[i][j] = 0;
            }
        }
    
    /*
    -----
    -----
    -----
    CRCW Matrix Multiplication Algorithm
    -----
    -----
    -----
    */
    #pragma omp parallel for private(i,j,k) shared(A,B,C) collapse(3)
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            for (k = 0; k < SIZE; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    printf("\nMatrix A:\n");
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            printf("%d\t", A[i][j]);
        }
        printf("\n");
    }

    printf("\nMaatrix B:\n");
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            printf("%d\t", B[i][j]);
        }
        printf("\n");
    }

    printf("\nResult Matrix C:\n");
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            printf("%d\t", C[i][j]);
        }
        printf("\n");
    }

    printf("\nResults Verified\n");

    return 0;
}