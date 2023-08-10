#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

void parse_arguments(int argc, char *argv[], int &n, int &launch_num, int &block_size);
void randmatrix(double **M, int n);
void matrix_to_mas(double **A, double *B, int N);
void DGEMM_opt_0(double **X, double **Y, double **C, int n, int launch_num, double &result, double &result_average);
void DGEMM_opt_1(double **X, double **Y, double **C, int n, int launch_num, double &result, double &result_average);
void DGEMM_opt_2(double *a, double *b, double *c, int n, int launch_num, int block_size, double &result, double &result_average);

int main(int argc, char *argv[])
{
  cout << "Start tests..." << endl;
  int n, launch_num, block_size;
  parse_arguments(argc,argv,n, launch_num, block_size);

	double **x = new double*[n];
	for (int i = 0; i < n; i++)
		x[i] = new double[n];
	double **y = new double*[n];
	for (int i = 0; i < n; i++)
		y[i] = new double[n];
  double **c = new double*[n];
  for (int i = 0; i < n; i++)
  	c[i] = new double[n];
  randmatrix(x, n);
  randmatrix(y, n);

  double *X = new double[n*n];
  double *Y = new double[n*n];
  double *C = new double[n*n];
  matrix_to_mas(x,X,n);
  matrix_to_mas(y,Y,n);

  double result_opt_0;
  double result_opt_0_average;
  double result_opt_1;
  double result_opt_1_average;
  double result_opt_2;
  double result_opt_2_average;
  DGEMM_opt_0(x, y, c, n, launch_num, result_opt_0, result_opt_0_average);
  DGEMM_opt_1(x, y, c, n, launch_num, result_opt_1, result_opt_1_average);
  DGEMM_opt_2(X, Y, C, n, launch_num, block_size, result_opt_2, result_opt_2_average);


  cout << "All tests done" << endl;
	for (int i = 0; i < n; i++) {
		delete x[i];
		delete y[i];
		delete c[i];
	}
	delete x;
	delete y;
	delete c;
	delete X;
	delete Y;
	delete C;

  cout << "Saving results..." << endl;
  ofstream output;
  output.open("result.csv", ios_base::app);
  output << "Size;DGEM_OPT;Time;AvTime;LaunchNum;BlockSize" << endl;
  output << n << ";0;" << result_opt_0 << ";" << result_opt_0_average << ";" << launch_num << ";" << block_size << endl;
  output << n << ";1;" << result_opt_1 << ";" << result_opt_1_average << ";" << launch_num << ";" << block_size << endl;
  output << n << ";2;" << result_opt_2 << ";" << result_opt_2_average << ";" << launch_num << ";" << block_size << endl;
  output.close();

  cout << "Results saved" << endl;
  return 0;
}

void parse_arguments(int argc, char *argv[], int &n, int &launch_num, int &block_size) {
  n = 100;
  launch_num = 1;
  block_size = 64;
	if (argc > 1) {
    n = atoi(argv[1]);
    if (argc > 2){
      launch_num = atoi(argv[2]);
      if (argc > 3){
       block_size = atoi(argv[3]);
      }
    }
  }
}

void randmatrix(double **M, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N;j++)
			M[i][j] = rand() % N;
	}
}

void matrix_to_mas(double **A, double *B, int N) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++)
  	 B[i*N+j] = A[i][j];
  }
}

void DGEMM_opt_0(double **X, double **Y, double **C, int n, int launch_num, double &result, double &result_average) {
	unsigned int start, stop;
  result = 0;
  for (int l = 0; l < launch_num; l++){
    start = clock();
  	for (int i = 0; i < n; i++) {
  		for (int j = 0; j < n; j++){
        C[i][j]=0;
        for (int k = 0; k < n; k++){
    			C[i][j] += X[i][k] * Y[k][j];
        }
  		}
  	}
    stop = clock();
    result += stop - start;
  }
	result = (double)result / CLOCKS_PER_SEC;
  result_average = result / launch_num;
}

void DGEMM_opt_1(double **X, double **Y, double **C, int n, int launch_num, double &result, double &result_average) {
	unsigned int start, stop;
  result = 0;
  for (int l = 0; l < launch_num; l++){
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++){
        C[i][j]=0;
      }
    }
      start = clock();
    for (int i = 0; i < n; i++) {
      for (int k = 0; k < n; k++){
  		  for (int j = 0; j < n; j++){
    			C[i][j] += X[i][k] * Y[k][j];
        }
  		}
  	}
    stop = clock();
    result += stop - start;
  }
	result = (double)result / CLOCKS_PER_SEC;
  result_average = result / launch_num;
}


void DGEMM_opt_2(double *a, double *b, double *c, int n, int launch_num, int block_size, double &result, double &result_average) {
  int i, j, k, i0, j0, k0;
  double *a0, *b0, *c0;
  unsigned int start, stop;
  result = 0;
  for (int l = 0; l < launch_num; l++){
    start = clock();
    for (i = 0; i < n; i += block_size) {
      for (j = 0; j < n; j += block_size) {
        for (k = 0; k < n; k += block_size) {
          for (i0 = 0, c0 = (c + i * n + j), a0 = (a + i * n + k); i0 < block_size; ++i0, c0 += n, a0 += n) {
            for (k0 = 0, b0 = (b + k * n + j); k0 < block_size; ++k0, b0 += n) {
              for (j0 = 0; j0 < block_size; ++j0) {
                c0[j0] += a0[k0] * b0[j0];
              }
            }
          }
        }
      }
    }
    stop = clock();
    result += stop - start;
  }
	result = (double)result / CLOCKS_PER_SEC;
  result_average = result / launch_num;
}
