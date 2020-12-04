#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
// #include <unistd.h>
// #include <cblas.h>
#include <iomanip>
#include <fstream>
// #include <immintrin.h>
#include <pthread.h>
#include <omp.h>
#include "tbb/task_scheduler_init.h"

using namespace std;
using namespace tbb;



int i, j, tmp, n;

double getRandomDouble() {
    double min = 0;
    double max = 500;

    double f = (double) rand() / RAND_MAX;
    return min + f * (max - min);
}

// int g = 0;

void DGEMM(int N, double **a, double **b, double **c) {
        int i, j, k; 
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                for (k = 0; k < N; k++) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        // cout << g++ << endl;
}

void *thread_function( void *arg ) {
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

    DGEMM(n, a, b, c);
    
    pthread_exit( NULL );
}


int main(int argc, char* argv[]) {
    
    srand(static_cast <unsigned> (time(nullptr))); 
    struct timespec tv1, tv2;
    n = stoi(argv[1]);
    int count_thread =  stoi(argv[2]);
   
    double matrix_DGEMM_time;
    ofstream file;

// ------------POSIX-------------------
    // pthread_t thread[count_thread];
    // pthread_attr_t attr;

    // pthread_attr_init(&attr);
    // pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    // pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);


    // for (i = 0; i < count_thread; i++) {
    //     tmp = pthread_create( &thread[i], &attr, thread_function, NULL );

    //     if (tmp != 0) {
    //         cout << "Create thread " << i << " failed!" << endl;
    //         return 1;
    //     }
    // }

    // clock_gettime(CLOCK_REALTIME, &tv1);
    // for (i = 0; i < count_thread; i++) {
    //     tmp = pthread_join(thread[i], NULL);

    //     if (tmp != 0) {
    //         cout << "Joing thread " << i << " failed!" << endl;
    //         return 1;
    //     }
    // }
    // clock_gettime(CLOCK_REALTIME, &tv2);

    // cout << "\nPOSIX" << endl;
    // matrix_DGEMM_time = ((double)tv2.tv_sec - (double) tv1.tv_sec) + ((double)tv2.tv_nsec - (double)tv1.tv_nsec) / 1000000000;
    // cout << fixed << setprecision(9) << matrix_DGEMM_time << endl;

// -------------OpenMP---------------------

    // clock_gettime(CLOCK_REALTIME, &tv1);
    // #pragma omp parallel num_threads(count_thread)
    // {   
    //     double **a = new double* [n], **b = new double* [n], **c = new double* [n];

    //     for (i = 0; i < n; i++) {
    //         a[i] = new double[n];
    //         b[i] = new double[n];
    //         c[i] = new double[n];
    //     }

    //     for (i = 0; i < n; i++){
    //         for (j = 0; j < n; j++){
    //             a[i][j] = getRandomDouble();
    //             b[i][j] = getRandomDouble();
    //             c[i][j] = 0;
    //         }
    //     }


    //     if (omp_get_thread_num() == 0) {
    //         DGEMM(n, a, b, c); // In master thread
    //     } else {
    //         DGEMM(n, a, b, c); // In other parallel thread
    //     }
    // }
    // clock_gettime(CLOCK_REALTIME, &tv2);

    // cout << "\nOpenMP" << endl;
    // matrix_DGEMM_time = ((double)tv2.tv_sec - (double) tv1.tv_sec) + ((double)tv2.tv_nsec - (double)tv1.tv_nsec) / 1000000000;
    // cout << fixed << setprecision(9) << matrix_DGEMM_time << endl;

// -------------Intel TBB----------------------

    task_scheduler_init init;

    clock_gettime(CLOCK_REALTIME, &tv1);
    init.initialize(count_thread);
    
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

    DGEMM(n, a, b, c);
    init.terminate();
    clock_gettime(CLOCK_REALTIME, &tv2);

    cout << "\nIntel TBB" << endl;
    matrix_DGEMM_time = ((double)tv2.tv_sec - (double) tv1.tv_sec) + ((double)tv2.tv_nsec - (double)tv1.tv_nsec) / 1000000000;
    cout << fixed << setprecision(9) << matrix_DGEMM_time << endl;


    // file.open("file.txt", ios_base::app);
    // file << n << " " << fixed << setprecision(6) << matrix_DGEMM_time << endl;
    // file.close();
    

    return 0;
}