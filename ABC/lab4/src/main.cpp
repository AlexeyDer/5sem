#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <cblas.h>
#include <iomanip>

// #include <blas.h>
using namespace std;


double getRandomDouble() {
    double min = -10000;
    double max = 10000;

    double f = (double) rand() / RAND_MAX;
    return min + f * (max - min);
}

// void DGEMM(char *ch1, char *ch2, unsigned long int M, unsigned long int N, unsigned long int K, double alpha, double *a, 
//     unsigned long int lda, double *b, unsigned long int ldb, double beta, double *c, unsigned long int ldc ) {


void DGEMM(int N, double **a, double **b, double **c) {
        int i, j, k; 
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                for (k = 0; k < N; k++) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
}


void DGEMM_opt_1(int N, double **a, double **b, double **c) {
        int i, j, k; 
        for (i = 0; i < N; i++) {
            for (k = 0; k < N; k++) {
                for (j = 0; j < N; j++) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
}

// void DGEMM_opt_2(int n, double **a, double **b, double **c, int BS) {
//         int i, j, k, i0, j0, a0, b0, c0, k0; 
        
//         for (i = 0; i < n; i += BS) {
//             for (j = 0; j < n; j += BS) {
//                 for (k = 0; k < n; k += BS) {
//                     for (i0 = 0, c0 = (c + i * n + j), a0 = (a + i * n + k); i0 < BS; ++i0, c0 += n, a0 += n){
//                         for (k0 = 0, b0 = (b + k * n + j);k0 < BS; ++k0, b0 += n){
//                             for (j0 = 0; j0 < BS; ++j0) {
//                                 c0[j0] += a0[k0] * b0[j0];
//                             }
//                         }
//                     }
//                 }   
//             }
//         }
// }

int main(int argc, char* argv[]) {
    srand(static_cast <unsigned> (time(nullptr))); 
    struct timespec tv1, tv2;
    
    int n = stoi(argv[1]);

    int i, j;
    double **a = new double* [n], **b = new double* [n], **c = new double* [n];

    for (i = 0; i < n; i++) {
        a[i] = new double[n];
        b[i] = new double[n];
        c[i] = new double[n];
    }


    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            a[i][j] = rand();
            b[i][j] = rand();
            c[i][j] = rand();
        }
    }   

    clock_gettime(CLOCK_REALTIME, &tv1);
    DGEMM(n, a, b , c);
    clock_gettime(CLOCK_REALTIME, &tv2);

    double matrix_DGEMM_time = ((double)tv2.tv_sec - (double) tv1.tv_sec) + ((double)tv2.tv_nsec - (double)tv1.tv_nsec) / 1000000000;
    cout << fixed << setprecision(6) << matrix_DGEMM_time << endl;

    // clock_gettime(CLOCK_REALTIME, &tv1);
    // DGEMM_opt_1(n, a, b , c);
    // clock_gettime(CLOCK_REALTIME, &tv2);

    // matrix_DGEMM_time = ((double)tv2.tv_sec - (double) tv1.tv_sec) + ((double)tv2.tv_nsec - (double)tv1.tv_nsec) / 1000000000;
    // cout << fixed << setprecision(6) << matrix_DGEMM_time << endl;


    

    return 0;
}