#include <stdlib.h>
#include <stdio.h>
#include <x86intrin.h>
#include <time.h>

void dgemm(int n, double* A, double* B, double* C)
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
        {
            double cij = C[i + j * n]; /* cij = C[i][j] */
            for (int k = 0; k < n; ++k)
                cij += A[i + k * n] * B[k + j * n]; /* cij += A[i][k] * B[k][j] */
            C[i + j * n] = cij; /* C[i][j] = cij */
        }
}

 void single_test(int n, FILE* output_file) {
     // Tamanho original da matriz


    // Aloca matrizes alinhadas para AVX, no tamanho expandido
    double* A = aligned_alloc(32, n * n* sizeof(double));
    double* B = aligned_alloc(32, n * n * sizeof(double));
    double* C = aligned_alloc(32, n* n * sizeof(double));

    // Inicializa as matrizes expandidas
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i < n && j < n) {
                A[i * n + j] = i * n + j + 1; // Valores originais
                B[i * n + j] = (i == j) ? 1.0 : 0.0; // Matriz identidade
            } else {
                A[i * n+ j] = 0.0; // Zera os elementos fora do tamanho original
                B[i * n + j] = 0.0;
            }
            C[i * n + j] = 0.0; // Inicializa C com zeros
        }
    }

 
    

// Medição do tempo
    clock_t start = clock();
    dgemm(n, A, B, C);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    fprintf(output_file, "Matrix size: %d, Time spent: %.6f seconds\n", n, time_spent);

    // Libera a memória
    free(A);
    free(B);
    free(C);

}

int main(){
    FILE* output_file = fopen("execution_times_cod1.txt", "a");
    if (!output_file) {
        perror("Failed to open output file");
        return EXIT_FAILURE;
    }

    single_test(32, output_file);
    single_test(160, output_file);
    single_test(480, output_file);
    single_test(960, output_file);

    fclose(output_file);
    return 0;

}
