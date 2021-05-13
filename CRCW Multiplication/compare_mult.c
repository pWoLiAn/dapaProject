#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

// The maximum matrix size for testing
#define N 1000

int A[N][N];
int B[N][N];
int C[N][N];

int main() 
{
    int i, j, k;
    struct timeval tv1, tv2;
    struct timezone tz;
	double elapsed_sequential, elapsed_parallel;
    srand(time(0));

    // Initialisation
    omp_set_num_threads(omp_get_num_procs());
    
    for (i= 0; i< N; i++)
    {
        for (j= 0; j< N; j++)
	    {
            A[i][j] = (double)rand()/(double)RAND_MAX;
            B[i][j] = (double)rand()/(double)RAND_MAX;
        }
    }

    printf("Size,Parallel Time,Sequential Time\n");

    for(int size = 5; size <= N; size+=5)
    {
        // Initialising
        for (i = 0; i < size; i++)
        {
            for (i = 0; i < size; i++)
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
        gettimeofday(&tv1, &tz);
        #pragma omp parallel for private(i,j,k) shared(A,B,C) collapse(3)
        for (i = 0; i < size; i++)
        {
            for (j = 0; j < size; j++)
            {
                for (k = 0; k < size; k++)
                {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        gettimeofday(&tv2, &tz);
        elapsed_parallel = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;

        // Reinitialising
        for (i = 0; i < size; i++)
        {
            for (i = 0; i < size; i++)
            {
                C[i][j] = 0;
            }
        }

        /*
        -----
        -----
        -----
        Sequential Matrix Multiplication Algorithm
        -----
        -----
        -----
        */
        gettimeofday(&tv1, &tz);
        for (i = 0; i < size; i++)
        {
            for (j = 0; j < size; j++)
            {
                for (k = 0; k < size; k++)
                {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        gettimeofday(&tv2, &tz);
        elapsed_sequential = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
        
        printf("%d,%f,%f\n", size, elapsed_parallel, elapsed_sequential);
    }

    return 0;
}
 