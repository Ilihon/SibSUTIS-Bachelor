#include <cstdio>
#include <cstdlib>
#include <pthread.h>

// g++ -o posix -pthread posix.cpp && ./posix 16 4

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

struct Mult_args_t {
    double **a;
    double **b;
    double **c;
    int size;
    int left_border;
    int right_border;
};

void *DGEMM(void *arg) {
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

void multiply_matrix(double **a, double **b, double **c, int matrix_size, int threads_count) {
    int for_one_thread = matrix_size / threads_count;

    pthread_t *threads = new pthread_t[threads_count];

    int left_border = 0;
    int right_border;
    for (int i = 0; i < threads_count; ++i) {
        right_border = left_border + for_one_thread;

        Mult_args_t *args = new Mult_args_t;
        args->a = a;
        args->b = b;
        args->c = c;
        args->size = matrix_size;
        args->left_border = left_border;
        args->right_border = right_border;

        pthread_create(&threads[i], nullptr, DGEMM, args);

        left_border += for_one_thread;
    }

    for (int i = 0; i < threads_count; ++i) {
        pthread_join(threads[i], nullptr);
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

    multiply_matrix(a, b, c, matrix_size, threads);

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