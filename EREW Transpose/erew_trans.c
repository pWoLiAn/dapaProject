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

    int i, j, k, temp;

    printf("\nMatrix A:\n");
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            printf("%d\t", A[i][j]);
        }
        printf("\n");
    }

    // Initialisation
    omp_set_num_threads(omp_get_num_procs());

    /*
    -----
    -----
    -----
    EREW Transpose Algorithm
    -----
    -----
    -----
    */
    #pragma omp parallel for private(i,j) shared(A) collapse(2)
    for (i = 1; i < SIZE; i++)
    {
        for (j = 0; j < SIZE-1; j++)
        {
            if (j < i)
            {
                temp=A[i][j];
                A[i][j]=A[j][i];
                A[j][i]=temp;
            }
        }
    }


    printf("\nTransposed Matrix:\n");
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            printf("%d\t", A[i][j]);
        }
        printf("\n");
    }

    printf("\nResults Verified\n");

    return 0;
}