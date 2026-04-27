#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 1000

int main() {
    // Declare array A of size 1000
    int A[N];

    // Declare constant value to add
    int constant = 5;

    /****************************************************
     * STEP 1: INITIALIZE ARRAY
     * - Fill array with values 0 to 999
     * - This runs sequentially (single thread)
     ****************************************************/
    printf("=== STEP 1: Initializing Array ===\n");
    printf("Filling array A with values 0 to %d\n", N-1);

    for (int i = 0; i < N; i++) {
        A[i] = i;
    }

    // Display first 10 initial values
    printf("Initial values (first 10): ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", A[i]);
    }
    printf("\n\n");

    /****************************************************
     * STEP 2: PARALLEL ADDITION
     * - Each thread processes a portion of the array
     * - Add constant (5) to each element
     * - OpenMP splits the work among available threads
     ****************************************************/
    printf("=== STEP 2: Parallel Addition ===\n");
    printf("Adding constant (%d) to each element using OpenMP\n", constant);
    printf("Number of threads: %d\n", omp_get_max_threads());

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        // Each thread adds 5 to its assigned elements
        A[i] = A[i] + constant;
    }

    printf("Parallel computation completed!\n\n");

    /****************************************************
     * STEP 3: DISPLAY RESULTS
     * - Print first 10 results after addition
     * - This runs sequentially
     ****************************************************/
    printf("=== STEP 3: Display Results ===\n");
    printf("Result after adding constant:\n");

    for (int i = 0; i < 10; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    /****************************************************
     * VERIFICATION: Show calculation
     ****************************************************/
    printf("\n=== VERIFICATION ===\n");
    for (int i = 0; i < 10; i++) {
        printf("A[%d] = %d + %d = %d\n", i, i, constant, A[i]);
    }

    return 0;
}
