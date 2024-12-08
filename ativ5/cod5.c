#include <stdlib.h>
#include <stdio.h>
#include <x86intrin.h>
#include <time.h>

#define BLOCKSIZE 32
#define UNROLL 4

void do_block(int n, int si, int sj, int sk, double* A, double* B, double* C) {
    for (int i = si; i < si + BLOCKSIZE; i += UNROLL * 4)
        for (int j = sj; j < sj + BLOCKSIZE; j++) {
            __m256d c[4];
            for (int x = 0; x < UNROLL; x++)
                c[x] = _mm256_load_pd(C + i + x * 4 + j * n);
            for (int k = sk; k < sk + BLOCKSIZE; k++) {
                __m256d b = _mm256_broadcast_sd(B + k + j * n);
                for (int x = 0; x < UNROLL; x++)
                    c[x] = _mm256_add_pd(c[x],
                                         _mm256_mul_pd(_mm256_load_pd(A + n * k + x * 4 + i), b));
            }
            for (int x = 0; x < UNROLL; x++)
                _mm256_store_pd(C + i + x * 4 + j * n, c[x]);
        }
}

void dgemm(int n, double* A, double* B, double* C) {
    for (int sj = 0; sj < n; sj += BLOCKSIZE)
        for (int si = 0; si < n; si += BLOCKSIZE)
            for (int sk = 0; sk < n; sk += BLOCKSIZE)
                do_block(n, si, sj, sk, A, B, C);
}

int round_up_to_multiple(int value, int multiple) {
    return (value + multiple - 1) / multiple * multiple;
}

void single_test(int n, FILE* output_file) {
    int n_aligned = round_up_to_multiple(n, BLOCKSIZE);

    double* A = aligned_alloc(32, n_aligned * n_aligned * sizeof(double));
    double* B = aligned_alloc(32, n_aligned * n_aligned * sizeof(double));
    double* C = aligned_alloc(32, n_aligned * n_aligned * sizeof(double));

    for (int i = 0; i < n_aligned; i++) {
        for (int j = 0; j < n_aligned; j++) {
            if (i < n && j < n) {
                A[i * n_aligned + j] = i * n + j + 1;
                B[i * n_aligned + j] = (i == j) ? 1.0 : 0.0;
            } else {
                A[i * n_aligned + j] = 0.0;
                B[i * n_aligned + j] = 0.0;
            }
            C[i * n_aligned + j] = 0.0;
        }
    }

    clock_t start = clock();
    dgemm(n_aligned, A, B, C);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    fprintf(output_file, "Matrix size: %d, Time spent: %.6f seconds\n", n, time_spent);

    free(A);
    free(B);
    free(C);
}

int main() {
    FILE* output_file = fopen("execution_times_cod5.txt", "a");
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
