#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>
#include <omp.h>
#include <pthread.h>

using namespace std;

// g++ -o main -fopenmp -pthread main.cpp && ./main 16 4

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
            printf("%12.2f", m[i][j]);
        }
        printf("\n");
    }
    return m;
}

void openmp_DGEMM(double **a, double **b, double **c, int matrix_size) {
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


struct Mult_args_t {
    double **a;
    double **b;
    double **c;
    int size;
    int left_border;
    int right_border;
};

void *posix_DGEMM(void *arg) {
    Mult_args_t *args = (Mult_args_t *) arg;
    for (int i = args->left_border; i < args->right_border; ++i) {
        for (int j = 0; j < args->size; ++j) {
            for (int k = 0; k < args->size; ++k) {
                args->c[i][j] += args->a[i][k] * args->b[k][j];
            }
        }
    }
    pthread_exit(0);
}

void posix_multiply_matrix(double **a, double **b, double **c, int matrix_size, int threads_count, double &result) {
    int for_one_thread = matrix_size / threads_count;
    unsigned int start, stop;

    pthread_t *threads = new pthread_t[threads_count];

    int left_border = 0;
    int right_border;
    Mult_args_t **args = new Mult_args_t *[threads_count];
    for (int i = 0; i < threads_count; ++i) {
        args[i] = new Mult_args_t;
        right_border = left_border + for_one_thread;
        args[i]->a = a;
        args[i]->b = b;
        args[i]->c = c;
        args[i]->size = matrix_size;
        args[i]->left_border = left_border;
        args[i]->right_border = right_border;


        left_border += for_one_thread;
    }
    start = clock();
    for (int i = 0; i < threads_count; ++i) {
      pthread_create(&threads[i], nullptr, posix_DGEMM, args[i]);
    }

    for (int i = 0; i < threads_count; ++i) {
        pthread_join(threads[i], nullptr);
    }
    stop = clock();
    result = (double)(stop - start) / CLOCKS_PER_SEC;
}

int main(int argc, char *argv[]) {
    int matrix_size = 0;
    int threads = 0;
    if (argc != 3) {
        printf("No arguments entered!\n");
        exit(1);
    }

    matrix_size = atoi(argv[1]);
    threads = atoi(argv[2]);

    double **a, **b, **c;
    a = generate_matrix_incr(matrix_size);
    b = generate_matrix_incr(matrix_size);
    c = generate_matrix_zero(matrix_size);
    cout << "Matrix generating done" << endl;
    omp_set_dynamic(0);
    omp_set_num_threads(threads);

    cout << "Start OpenMP DGEMM" << endl;
    unsigned int start, stop;
    double openmp_result, posix_result;
    start = clock();
    openmp_DGEMM(a, b, c, matrix_size);
    stop = clock();
    openmp_result = (double)(stop - start) / CLOCKS_PER_SEC;
    cout << "OpenMP DGEMM done, result = " << openmp_result << endl;

    cout << "Start Posix DGEMM" << endl;
    posix_multiply_matrix(a, b, c, matrix_size, threads, posix_result);
    cout << "Posix DGEMM done, result = " << posix_result << endl;

    cout << "Saving results..." << endl;
    ofstream output;
    output.open("result.csv", ios_base::app);
    output << "DGEM_style;Size;Thread;Time;" << endl;
    output << "OpenMP;" << matrix_size << ";" << threads << ";" << openmp_result << ";" << endl;
    output << "Posix;" << matrix_size << ";" << threads << ";" << posix_result << ";" << endl;
    output.close();
    cout << "Results saved" << endl;

    delete[] a;
    delete[] b;
    delete[] c;

    return 0;
}
