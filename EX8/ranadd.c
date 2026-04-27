#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 1000
#include <time.h>
int main()
{
    int i;
    int A[N], B[N], C[N];
    srand(time(0));
    for ( i = 0; i < N; i++)
    {
        A[i] = rand() % 100;
        B[i] = rand() % 100;
    }
    #pragma omp parallel for
    for ( i = 0; i < N; i++)
    {
        C[i] = A[i] + B[i];
    }
    printf("Result:\n");
    for ( i = 0; i < 10; i++)
    {
        printf("Thread %d computed C[%d] = %d\n", omp_get_thread_num(), i, C[i]);
        printf("%d + %d = %d\n", A[i], B[i], C[i]);
    }
    return 0;
}
