#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <cblas.h>
#include <iomanip>
#include <fstream>
#include <assert.h>
#include <immintrin.h>

using namespace std;


double getRandomDouble() {
    double min = 0;
    double max = 500;

    double f = (double) rand() / RAND_MAX;
    return min + f * (max - min);
}


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
//         int i, j, k, i0, j0, k0;
//         double **a0, b0, c0; 
        
//         for (i = 0; i < n; i += BS) {
//             for (j = 0; j < n; j += BS) {
//                 for (k = 0; k < n; k += BS) {
//                     for (i0 = 0, c0 = (c + i * n + j),
//                     a0 = (a + i * n + k); i0 < BS;
//                     ++i0, c0 += n, a0 += n){
//                         for (k0 = 0, b0 = (b + k * n + j);
//                         k0 < BS; ++k0, b0 += n){
//                             for (j0 = 0; j0 < BS; ++j0) {
//                                 c0[j0] += a0[k0] * b0[j0];
//                             }
//                         }
//                     }
//                 }   
//             }
//         }
// }

//описание функций
//  

void DGEMM_opt_2(int n, double *A, double *B, double *C, int bSize) {
    int i, j, k, ik, jk, kk;

    // assert(n % bSize == 0);

    for(j = 0; j < n; j++) {
        for(i = 0; i < n; i++) {
            C[j * n + i] = 0;
        }
    }
    for(jk = 0; jk < n; jk+= bSize)
        for(kk = 0; kk < n; kk+= bSize)
            for(ik = 0; ik < n; ik+= bSize)
                for(j = 0; j < bSize; j++ )
                    for(k = 0; k < bSize; k++ )
    #pragma simd
                        for(i = 0; i < bSize; i++ )
                            C[(jk + j) * n + (ik + i)] +=
                                A[(jk + j) * n + (kk + k)] *
                                B[(kk + k) * n + (ik + i)];

}


// void DGEMM_opt_3(int N, double **a, double **b, double **c) {
//         int i, j, k; 
//         for (i = 0; i < N; i++) {
//             for (k = 0; k < N; k++) {
// #pragma simd
//                 for (j = 0; j < N; j++) {
//                     c[i][j] += a[i][k] * b[k][j];
//                 }
//             }
//         }
// }

void DGEMM_opt_3(int n, double *A, double *B, double *C) {
        int i, j, k; 

        for(j = 0; j < n; j++ )
            for(i = 0; i < n; i++ )
                C[j * n + i] = 0;
        for(j = 0; j < n; j++ )
            for(k = 0; k < n; k++ )
            #pragma simd
                for(i = 0; i < n; i++ )
                    C[j * n + i] += A[j * n + k] * B[k * n + i];
}


// void allocMatrix(double ** mat, int n)
// {
//  // выделяем память, выровненную по 64 байт
//  (*mat) = (double *)_mm_malloc(sizeof(double)* (n * n), 64);
// }

// void freeMatrix(double ** mat)
// {
//  _mm_free((*mat));
// }


int main(int argc, char* argv[]) {
    srand(static_cast <unsigned> (time(nullptr))); 
    struct timespec tv1, tv2;
    int n = stoi(argv[1]);
    int i, j;
    double matrix_DGEMM_time;
    ofstream file;


    // ----------- classic ------------

    double **a = new double* [n], **b = new double* [n], **c = new double* [n];

    for (i = 0; i < n; i++) {
        a[i] = new double[n];
        b[i] = new double[n];
        c[i] = new double[n];
    }

    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            a[i][j] = getRandomDouble();
            b[i][j] = getRandomDouble();
            c[i][j] = 0;
        }
    }

    // ---------- opt_2 -------------------------


    // double *A, *B, *C;
    // A = (double*)malloc(n*n*sizeof(double));
    // B = (double*)malloc(n*n*sizeof(double));
    // C = (double*)malloc(n*n*sizeof(double));

    // for (i = 0;i < n * n; i++) {
    //     A[i] = getRandomDouble();
    //     B[i] = getRandomDouble();
    //     C[i] = 0;
    // }   

     // ---------- opt_3 -------------------------


    double *A, *B, *C;
    

    A = (double *)_mm_malloc(sizeof(double)* (n * n), 64);
    B = (double *)_mm_malloc(sizeof(double)* (n * n), 64);
    C = (double *)_mm_malloc(sizeof(double)* (n * n), 64);

    for (i = 0;i < n * n; i++) {
        A[i] = getRandomDouble();
        B[i] = getRandomDouble();
        C[i] = 0;
    }   




    // --------------- classic ------------------

    // clock_gettime(CLOCK_REALTIME, &tv1);
    // DGEMM(n, a, b , c);
    // clock_gettime(CLOCK_REALTIME, &tv2);

    // matrix_DGEMM_time = ((double)tv2.tv_sec - (double) tv1.tv_sec) + ((double)tv2.tv_nsec - (double)tv1.tv_nsec) / 1000000000;
    // cout << fixed << setprecision(9) << matrix_DGEMM_time << endl;

    // file.open("file.txt", ios_base::app);
    // file << n << " " << fixed << setprecision(6) << matrix_DGEMM_time << endl;
    // file.close();
    
    // ---------------- opt_1 --------------------

    // clock_gettime(CLOCK_REALTIME, &tv1);
    // DGEMM_opt_1(n, a, b , c);
    // clock_gettime(CLOCK_REALTIME, &tv2);

    // matrix_DGEMM_time = ((double)tv2.tv_sec - (double) tv1.tv_sec) + ((double)tv2.tv_nsec - (double)tv1.tv_nsec) / 1000000000;
    // cout << fixed << setprecision(9) << matrix_DGEMM_time << endl;

    // file.open("opt_1.txt", ios_base::app);
    // file << n << " " << fixed << setprecision(6) << matrix_DGEMM_time << endl;
    // file.close();
    
    //------------ opt_2 ---------------------

    clock_gettime(CLOCK_REALTIME, &tv1);
    DGEMM_opt_2(n, A, B , C, 64);
    clock_gettime(CLOCK_REALTIME, &tv2);

    matrix_DGEMM_time = ((double)tv2.tv_sec - (double) tv1.tv_sec) + ((double)tv2.tv_nsec - (double)tv1.tv_nsec) / 1000000000;
    cout << fixed << setprecision(9) << matrix_DGEMM_time << endl;

    file.open("opt_2.txt", ios_base::app);
    file << n << " " << fixed << setprecision(6) << matrix_DGEMM_time << endl;
    file.close();


    // ------------ opt_3 ------------------

    // clock_gettime(CLOCK_REALTIME, &tv1);
    // DGEMM_opt_3(n, A, B , C);
    // clock_gettime(CLOCK_REALTIME, &tv2);

    // matrix_DGEMM_time = ((double)tv2.tv_sec - (double) tv1.tv_sec) + ((double)tv2.tv_nsec - (double)tv1.tv_nsec) / 1000000000;
    // cout << fixed << setprecision(9) << matrix_DGEMM_time << endl;

    // file.open("opt_3.txt", ios_base::app);
    // file << n << " " << fixed << setprecision(6) << matrix_DGEMM_time << endl;
    // file.close();

    return 0;
}