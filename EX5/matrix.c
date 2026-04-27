#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 10

int r1, c1, r2, c2;
int A[MAX][MAX], B[MAX][MAX];
int Add[MAX][MAX], Mul[MAX][MAX];

// Thread function for Matrix Addition
void* matrix_add(void* arg)
{
    printf("\nAddition Thread ID: %lu\n", pthread_self());

    for(int i = 0; i < r1; i++)
    {
        for(int j = 0; j < c1; j++)
        {
            Add[i][j] = A[i][j] + B[i][j];
        }
    }

    pthread_exit(NULL);
}

// Thread function for Matrix Multiplication
void* matrix_multiply(void* arg)
{
    printf("\nMultiplication Thread ID: %lu\n", pthread_self());

    for(int i = 0; i < r1; i++)
    {
        for(int j = 0; j < c2; j++)
        {
            Mul[i][j] = 0;
            for(int k = 0; k < c1; k++)
            {
                Mul[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t t1, t2;

    // Input matrix sizes
    printf("Enter rows and columns of Matrix A: ");
    scanf("%d %d", &r1, &c1);

    printf("Enter rows and columns of Matrix B: ");
    scanf("%d %d", &r2, &c2);

    // Check for addition condition
    if(r1 != r2 || c1 != c2)
    {
        printf("Matrix Addition not possible!\n");
        return 0;
    }

    // Check for multiplication condition
    if(c1 != r2)
    {
        printf("Matrix Multiplication not possible!\n");
        return 0;
    }

    // Input Matrix A
    printf("Enter elements of Matrix A:\n");
    for(int i = 0; i < r1; i++)
        for(int j = 0; j < c1; j++)
            scanf("%d", &A[i][j]);

    // Input Matrix B
    printf("Enter elements of Matrix B:\n");
    for(int i = 0; i < r2; i++)
        for(int j = 0; j < c2; j++)
            scanf("%d", &B[i][j]);

    // Create Threads
    pthread_create(&t1, NULL, matrix_add, NULL);
    pthread_create(&t2, NULL, matrix_multiply, NULL);

    // Wait for threads to complete
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Print Addition Result
    printf("\nMatrix Addition Result:\n");
    for(int i = 0; i < r1; i++)
    {
        for(int j = 0; j < c1; j++)
            printf("%d ", Add[i][j]);
        printf("\n");
    }

    // Print Multiplication Result
    printf("\nMatrix Multiplication Result:\n");
    for(int i = 0; i < r1; i++)
    {
        for(int j = 0; j < c2; j++)
            printf("%d ", Mul[i][j]);
        printf("\n");
    }

    return 0;
}
