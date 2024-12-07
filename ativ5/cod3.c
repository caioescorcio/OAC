#include <x86intrin.h>
#include "matrices.h"

void dgemm(size_t n, double* A, double* B, double* C)
{
    for (size_t i = 0; i < n; i += 4) {
        for (size_t j = 0; j < n; ++j) {
            __m256d c0 = _mm256_load_pd(C + i + j * n); /* c0 = C[i][j] */
            for (size_t k = 0; k < n; ++k) {
                __m256d a = _mm256_load_pd(A + i + k * n);
                __m256d b = _mm256_broadcast_sd(B + k + j * n);
                c0 = _mm256_add_pd(c0, _mm256_mul_pd(a, b));
            }
            _mm256_store_pd(C + i + j * n, c0); /* C[i][j] = c0 */
        }
    }
}

int main(){
    initialize_matrices();
    // Garantir alinhamento adequado para arrays A10, B10, C10
    __attribute__((aligned(32))) double A10[100];  // Ajuste o tamanho conforme necessário
    __attribute__((aligned(32))) double B10[100];
    __attribute__((aligned(32))) double C10[100];

    dgemm(8, A10, B10, C10);
    return 0;
}
