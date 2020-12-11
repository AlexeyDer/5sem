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
#include <malloc.h>
#include "tbb/task_scheduler_init.h"

using namespace std;
using namespace tbb;

void DGEMM(int N, double *a, double *b, double *c, int from, int to) {
    int r = 0, col = 0;
    double t = 0;

    for (int i = from; i < to; i++) {
        r = i * N;
        for (int j = 0; j < N; j++) {
            col = 0;
            for (int k = 0; k < N; k++) {
                t += a[r + k] * b[j + col];
                col += N;
            }
            c[r + j] = t;
            t = 0;
        }
    }
}

struct SMatrix
{   
    double *a, *b, *c;
    int from, to, n;
};

void *thread_posix( void *arg ) {
    SMatrix* sMatrix = (struct SMatrix *) arg;
    double *a = sMatrix->a, *b = sMatrix->b, *c = sMatrix->c;
    int from = sMatrix->from, to = sMatrix->to, n = sMatrix->n;

    DGEMM(n, a, b, c, from, to);

    pthread_exit( NULL );
}

int n, tmp;
int count_thread;

int main(int argc, char* argv[]) {
    srand(static_cast <unsigned> (time(nullptr))); 
    struct timespec tv1, tv2;
    n = stoi(argv[1]);
    count_thread =  stoi(argv[2]);

    // from = new int[count_thread], to = new int [count_thread];
    // a = (double*)malloc(n * n * sizeof(double));
    // b = (double*)malloc(n * n * sizeof(double));
    // c = (double*)malloc(n * n * sizeof(double));

    double matrix_DGEMM_time;
    // ofstream file;

    int q = (int)((double)n / (double)count_thread);
    int step = 0;

    SMatrix sMatrix[count_thread];


// ------------POSIX-------------------
    pthread_t thread[count_thread];
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    // pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

    // int num[count_thread];
    double* a = (double*)malloc(n * n * sizeof(double));
    double* b = (double*)malloc(n * n * sizeof(double));
    double* c = (double*)malloc(n * n * sizeof(double));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            a[i + j * n] = 1 + rand() % 10;
            b[i + j * n] = 1 + rand() % 10;
        }
    }
    for (int i = 0; i < count_thread; i++) {
        sMatrix[i].n = n;
        sMatrix[i].a = a;
        sMatrix[i].b = b;
        sMatrix[i].c = c;
        sMatrix[i].from = step;
        step += q;
        sMatrix[i].to = (i == count_thread - 1) ? n : step;
       
        tmp = pthread_create(&thread[i], &attr, thread_posix, (void *) &thread[i]);

        if (tmp != 0) {
            cout << "Create thread " << i << " failed!" << endl;
            return 1;
        }
    }
    pthread_attr_destroy(&attr);

    clock_gettime(CLOCK_REALTIME, &tv1);
    for (int i = 0; i < count_thread; i++) {
        tmp = pthread_join(thread[i], NULL);

        if (tmp != 0) {
            cout << "Joing thread " << i << " failed!" << endl;
            return 1;
        }
    }
    clock_gettime(CLOCK_REALTIME, &tv2);

    cout << "\nPOSIX" << endl;
    matrix_DGEMM_time = ((double)tv2.tv_sec - (double) tv1.tv_sec) + ((double)tv2.tv_nsec - (double)tv1.tv_nsec) / 1000000000;
    cout << fixed << setprecision(9) << matrix_DGEMM_time << endl;

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

    // task_scheduler_init init;

    // clock_gettime(CLOCK_REALTIME, &tv1);
    // init.initialize(count_thread);
    
    //  double **a = new double* [n], **b = new double* [n], **c = new double* [n];

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

    // DGEMM(n, a, b, c);
    // init.terminate();
    // clock_gettime(CLOCK_REALTIME, &tv2);

    // cout << "\nIntel TBB" << endl;
    // matrix_DGEMM_time = ((double)tv2.tv_sec - (double) tv1.tv_sec) + ((double)tv2.tv_nsec - (double)tv1.tv_nsec) / 1000000000;
    // cout << fixed << setprecision(9) << matrix_DGEMM_time << endl;


    // file.open("file.txt", ios_base::app);
    // file << n << " " << fixed << setprecision(6) << matrix_DGEMM_time << endl;
    // file.close();
    

    return 0;
}