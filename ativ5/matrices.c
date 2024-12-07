#include <stdlib.h>
#include "matrices.h"

// Define the matrices
double* A5;
double* B5;
double* C5;
double* A10;
double* B10;
double* C10;
double* A4;
double* B4;
double* C4;

void initialize_matrices() {
    // Allocate memory for A5, B5, and C5 (5x5 matrix)
    A5 = (double*)malloc(5 * 5 * sizeof(double));
    B5 = (double*)malloc(5 * 5 * sizeof(double));
    C5 = (double*)malloc(5 * 5 * sizeof(double));

    A4 = (double*)malloc(4 * 4 * sizeof(double));
    B4 = (double*)malloc(4 * 4 * sizeof(double));
    C4 = (double*)malloc(4 * 4 * sizeof(double));


    // Allocate memory for A100, B100, and C100 (100x100 matrix)
    A10 = (double*)malloc(10 * 10* sizeof(double));
    B10 = (double*)malloc(10* 10* sizeof(double));
    C10 = (double*)malloc(100 * 100 * sizeof(double));

    // Initialize A5 and B5
    double A5_values[25] = {
        1.1, 2.2, 3.3, 4.4, 5.5,
        6.6, 7.7, 8.8, 9.9, 10.0,
        11.1, 12.2, 13.3, 14.4, 15.5,
        16.6, 17.7, 18.8, 19.9, 20.0,
        21.1, 22.2, 23.3, 24.4, 25.5
    };

    double B5_values[25] = {
        25.5, 24.4, 23.3, 22.2, 21.1,
        20.0, 19.9, 18.8, 17.7, 16.6,
        15.5, 14.4, 13.3, 12.2, 11.1,
        10.0, 9.9, 8.8, 7.7, 6.6,
        5.5, 4.4, 3.3, 2.2, 1.1
    };

    double A4_values[16] = {
        1.1, 2.2, 3.3, 4.4, 5.5,
        6.6, 7.7, 8.8, 9.9, 10.0,
        11.1, 12.2, 13.3, 14.4, 15.5,
        16.6
    };

    double B4_values[16] = {
        25.5, 24.4, 23.3, 22.2, 21.1,
        20.0, 19.9, 18.8, 17.7, 16.6,
        15.5, 14.4, 13.3, 12.2, 11.1,
        10.0
    };


    // Copy values into A5 and B5
    for (int i = 0; i < 25; i++) {
        A5[i] = A5_values[i];
        B5[i] = B5_values[i];
    }

    // Initialize A100 and B100
    for (int i = 0; i < 8 * 10; i++) {
        A10[i] = (i + 1) * 0.1; // Arbitrary values: 0.1, 0.2, ..., 1000.0
        B10[i] = 1000.0 - (i * 0.1); // Arbitrary values: 1000.0, 999.9, ..., 0.1
    }
}

// This will call the `initialize_matrices()` function automatically when the program starts
__attribute__((constructor)) void auto_initialize_matrices() {
    initialize_matrices();
}
