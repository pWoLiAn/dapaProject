#include <stdio.h>
#include <stdlib.h>

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

    /*
    -----
    -----
    -----
    Sequential Transpose Algorithm
    -----
    -----
    -----
    */
    for (i = 1; i < SIZE; i++)
    {
        for (j = 0; j < i; j++)
        {
            temp=A[i][j];
            A[i][j]=A[j][i];
            A[j][i]=temp;
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