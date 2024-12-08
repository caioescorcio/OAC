#include <stdlib.h>
#include <stdio.h>
#include <x86intrin.h>
#include <time.h>

#define BLOCKSIZE 32
#define UNROLL 4

void do_block(int n, int si, int sj, int sk, double* A, double* B, double* C){
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
void dgemm(int n, double* A, double* B, double* C){
	for ( int sj = 0; sj < n; sj += BLOCKSIZE )
        for ( int si = 0; si < n; si += BLOCKSIZE )
        for ( int sk = 0; sk < n; sk += BLOCKSIZE )
        do_block( n , 0, 0, 0, A, B, C);

}

int round_up_to_multiple(int value, int multiple) {
    return (value + multiple - 1) / multiple * multiple;
}

void single_test(int n) {
     // Tamanho original da matriz
    int n_aligned = round_up_to_multiple(n, BLOCKSIZE); // Tamanho expandido para múltiplo de 32

    // Aloca matrizes alinhadas para AVX, no tamanho expandido
    double* A = aligned_alloc(32, n_aligned * n_aligned * sizeof(double));
    double* B = aligned_alloc(32, n_aligned * n_aligned * sizeof(double));
    double* C = aligned_alloc(32, n_aligned * n_aligned * sizeof(double));

    // Inicializa as matrizes expandidas
    for (int i = 0; i < n_aligned; i++) {
        for (int j = 0; j < n_aligned; j++) {
            if (i < n && j < n) {
                A[i * n_aligned + j] = i * n + j + 1; // Valores originais
                B[i * n_aligned + j] = (i == j) ? 1.0 : 0.0; // Matriz identidade
            } else {
                A[i * n_aligned + j] = 0.0; // Zera os elementos fora do tamanho original
                B[i * n_aligned + j] = 0.0;
            }
            C[i * n_aligned + j] = 0.0; // Inicializa C com zeros
        }
    }

 
    

// Medição do tempo
    clock_t start = clock();
    dgemm(n_aligned, A, B, C);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    // Libera a memória
    free(A);
    free(B);
    free(C);

}

int main(){
    single_test(32);
    single_test(160);
    single_test(480);
    single_test(960);
    return 0;


}
