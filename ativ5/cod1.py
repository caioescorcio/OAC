from matrices import A5, B5, C5, A10, B10, C10
def dgemm(n: int, A, B, C) -> None:
    for i in range(n):
        for j in range(n):
            for k in range(n):
                C[i][j] += A[i][k] * B[k][j]

dgemm(10, A10, B10, C10)