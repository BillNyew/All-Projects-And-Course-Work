#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void displayMatrix(int *matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d ", matrix[i * N + j]);
        }
        printf("\n");
    }
    printf("\n");
}

void matrixMultiply(int *A, int *B, int *C, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i * N + j] = 0;
            for (int k = 0; k < N; k++) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
}

void transposeMatrix(int *matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int temp = matrix[i * N + j];
            matrix[i * N + j] = matrix[j * N + i];
            matrix[j * N + i] = temp;
        }
    }
}

void matrixMultiplyTranspose(int *A, int *B, int *C, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i * N + j] = 0;
            for (int k = 0; k < N; k++) {
                C[i * N + j] += A[i * N + k] * B[j * N + k];
            }
        }
    }
}

int main() {
    int N = 1000; // Adjust this value to find the largest multiple of 100 that doesn't cause a segfault
    int *A = (int *)malloc(N * N * sizeof(int));
    int *B = (int *)malloc(N * N * sizeof(int));
    int *C = (int *)malloc(N * N * sizeof(int));

    if (!A || !B || !C) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Fill in matrices A and B with initial values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = i * N + j;
            B[i * N + j] = i * N + j;
        }
    }

    // Display matrices A and B (commented out for performance testing)
    /*
    printf("Matrix A:\n");
    displayMatrix(A, N);

    printf("Matrix B:\n");
    displayMatrix(B, N);
    */
    // Display result matrix C (commented out for performance testing)
    /*
    printf("Matrix C (Result of A * B):\n");
    displayMatrix(C, N);
    */
    // Display transposed matrix B (commented out for performance testing)
    /*
    printf("Matrix B Transposed:\n");
    displayMatrix(B, N);
    */
    // Display result matrix C (commented out for performance testing)
    /*
    printf("Matrix C (Result of A * B_transposed):\n");
    displayMatrix(C, N);
    */



    // Standard matrix multiplication

    clock_t start = clock();
    matrixMultiply(A, B, C, N);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Standard Matrix Multiplication Time: %f seconds\n", time_taken);

    // Transpose matrix B

    // transposeMatrix(B, N);

    // Matrix multiplication with transposed B

    // clock_t start = clock();
    // matrixMultiplyTranspose(A, B, C, N);
    // clock_t end = clock();
    // double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    // printf("Transposed Matrix Multiplication Time: %f seconds\n", time_taken);

    // Free allocated memory
    free(A);
    free(B);
    free(C);

    return 0;
}












// STANDARD MATRIX 

// TRIAL 1:
// Standard Matrix Multiplication Time: 8.375080 seconds

// real	0m8.392s
// user	0m8.363s
// sys	0m0.024s
// // TRIAL 2:
// Standard Matrix Multiplication Time: 8.658837 seconds

// real	0m8.736s
// user	0m8.659s
// sys	0m0.008s

// // TRIAL 3:
// Standard Matrix Multiplication Time: 8.390892 seconds

// real	0m8.403s
// user	0m8.375s
// sys	0m0.024s


// TRANSPOSED MATRIX B 

// TRIAL 1:
// Transposed Matrix Multiplication Time: 4.175583 seconds

// real	0m4.191s
// user	0m4.175s
// sys	0m0.012s

//  TRIAL 2:
// Transposed Matrix Multiplication Time: 4.187518 seconds

// real	0m4.203s
// user	0m4.187s
// sys	0m0.012s

//  TRIAL 3 :
// Transposed Matrix Multiplication Time: 4.183545 seconds

// real	0m4.199s
// user	0m4.183s
// sys	0m0.012s

// Based on the results, we can observe that transposed matrix multiplication is faster.
// This is because accessing elements in a row-major order utilizes the cache more efficiently,
// reducing cache misses.
