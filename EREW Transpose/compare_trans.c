#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

// The maximum matrix size for testing
#define N 5000

int A[N][N];

int main() 
{
    int i, j, temp;
    struct timeval tv1, tv2;
    struct timezone tz;
	double elapsed_parallel, elapsed_sequential;
    srand(time(0));

    // Initialisation
    omp_set_num_threads(omp_get_num_procs());
    for (i= 0; i< N; i++)
    {
        for (j= 0; j< N; j++)
	    {
            A[i][j] = (double)rand()/(double)RAND_MAX;
	    }
    }

    printf("Size,Parallel Time,Sequential Time\n");

    for(int size=10; size <= N; size+=10)
    {
        /*
        -----
        -----
        -----
        EREW Parallel Transpose Algorithm
        -----
        -----
        -----
        */
        gettimeofday(&tv1, &tz);
        #pragma omp parallel for private(i,j) shared(A) collapse(2)
        for (i = 1; i < size; i++)
        {
            for (j = 0; j < size-1; j++)
            {
                if (j < i)
                {
                    temp=A[i][j];
                    A[i][j]=A[j][i];
                    A[j][i]=temp;
                }
            }
        }
        gettimeofday(&tv2, &tz);
        elapsed_parallel = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;

        /*
        -----
        -----
        -----
        Sequential Transpose Algorithm
        -----
        -----
        -----
        */
        gettimeofday(&tv1, &tz);
        for (i = 1; i < size; i++)
        {
            for (j = 0; j < i; j++)
            {
                temp=A[i][j];
                A[i][j]=A[j][i];
                A[j][i]=temp;
            }
        }
        gettimeofday(&tv2, &tz);
        elapsed_sequential = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
        printf("%d,%f,%f\n", size, elapsed_parallel, elapsed_sequential);
    }

    return 0;
}
 
