#include <cstdio>
#include <cstdlib>
#include <omp.h>

// g++ -o openmp -fopenmp openmp.cpp && ./openmp 16 4

double **generate_matrix_random(int size) {
    double **m = new double *[size];
    for (int i = 0; i < size; ++i) {
        m[i] = new double[size];
        for (int j = 0; j < size; ++j) {
            m[i][j] = (double) (rand() % 100);
        }
    }
    return m;
}

double **generate_matrix_incr(int size) {
    double **m = new double *[size];
    for (int i = 0; i < size; ++i) {
        m[i] = new double[size];
        for (int j = 0; j < size; ++j) {
            m[i][j] = i * size + j + 1;
        }
    }
    return m;
}

double **generate_matrix_zero(int size) {
    double **m = new double *[size];
    for (int i = 0; i < size; ++i) {
        m[i] = new double[size];
        for (int j = 0; j < size; ++j) {
            m[i][j] = 0.0;
        }
    }
    return m;
}

double **print_matrix(double **m, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%9.2f", m[i][j]);
        }
        printf("\n");
    }
    return m;
}

void DGEMM(double **a, double **b, double **c, int matrix_size) {
    int i, j, k;
#pragma omp parallel for private(i, j, k) shared(a, b, c)
    for (i = 0; i < matrix_size; ++i) {
        for (j = 0; j < matrix_size; ++j) {
            for (k = 0; k < matrix_size; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int matrix_size = 0;
    int threads = 0;
    if (argc != 3) {
        printf("No arguments specified!\n");
        std::exit(1);
    }

    matrix_size = std::atoi(argv[1]);
    threads = std::atoi(argv[2]);

    double **a, **b, **c;
    a = generate_matrix_incr(matrix_size);
    b = generate_matrix_incr(matrix_size);
    c = generate_matrix_zero(matrix_size);

    omp_set_dynamic(0);
    omp_set_num_threads(threads);

    DGEMM(a, b, c, matrix_size);

    print_matrix(a, matrix_size);
    printf("\n");
    print_matrix(b, matrix_size);
    printf("\n");
    print_matrix(c, matrix_size);
    printf("\n");

    delete[] a;
    delete[] b;
    delete[] c;

    return 0;
}