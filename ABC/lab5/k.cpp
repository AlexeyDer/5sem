#include <pthread.h>
#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

/**
 * Перевод наносекунд в секунды
 */
#define NS_TO_S 0.000000001;

/**
 * Размер динамической матрицы
 */
int matrixSize = 1000;

/**
 * Число потоков
 */
int threadNum = 4;

/**
 * Режим тестирования
 */
bool debug = false;

/**
 * Серия испытаний
 */
bool serialLaunch = true;

/**
 * Имя файла отчета
 */
string reportFileName;

/**
 * Библиотека потоков
 */
string threadLib = "pthread";

/**
 * Генерация случайного числа (double)
 * @return случайное число (double)
 */
double getRandomDouble() {
    double min = 0;
    double max = 9999.99;
    return min + (double) (rand()) / ((double) (RAND_MAX / (max - min)));
}

/**
 * Создание файла отчета
 * @param createNewFile true создать новый файл отчета, false запись в предудщий файл отчета
 * @param totalTime Общее время вычислений
 */
void reportFile(bool createNewFile, double totalTime) {
    string path = R"(report/)";

    if (createNewFile) {
        reportFileName =
                to_string(threadNum) + "-" + to_string(matrixSize) + "-report-" + to_string(abs(getRandomDouble())) +
                ".csv";
        ofstream outCSV;
        outCSV.open(path + reportFileName);

        //--------- Заголовки------------
        outCSV << "Library;";
        outCSV << "Thread num;";
        outCSV << "Matrix size;";
        outCSV << "Total time;";

        //-------- Данные --------------
        outCSV << endl;
        outCSV << threadLib << ";";
        outCSV << threadNum << ";";
        outCSV << matrixSize << ";";
        outCSV << totalTime << ";";

        outCSV.close();
    } else {
        ofstream outCSV;
        outCSV.open(path + reportFileName, ios_base::app);

        //-------- Данные --------------
        outCSV << endl;
        outCSV << threadLib << ";";
        outCSV << threadNum << ";";
        outCSV << matrixSize << ";";
        outCSV << totalTime << ";";

        outCSV.close();
    }
}

/**
 * Выбор библиотеки для работы с потоками
 */
void initThreadLib() {
    int userInput;
    cout << endl << "[1] Pthread";
    cout << endl << "[2] Omp";
    cout << endl << "> ";
    cin >> userInput;

    if (userInput == 1) {
        threadLib = "pthread";
    } else if (userInput == 2) {
        threadLib = "omp";
    } else {
        cout << endl << "Некорректный ввод";
    }
}

/**
 * Инициализация размеров матриц
 */
void initMatrixSize() {
    cout << endl << "Введите размер матриц > ";
    cin >> matrixSize;
}

/**
 * Инициализация числа потоков
 */
void initThreadNum() {
    cout << endl << "Введите число потоков > ";
    cin >> threadNum;
}

/**
 * Очистка памяти выделенной для матрицы
 * @param matrix Матрица
 */
void freeMatrixSpace(double *matrix) {
    free(matrix);
}

/**
 * Получить время вычислений
 * @tparam T Время начала отсчета
 * @param startTime Время начала вычислений
 * @return Время вычислений в секундах
 */
template<typename T>
double getWorkingTime(T startTime) {
    return chrono::duration_cast<chrono::nanoseconds>(
            chrono::high_resolution_clock::now() - startTime).count() * NS_TO_S;
}

/**
 * Параметры матрицы для хранения даннных для текущего потока (pthread)
 */
struct matrixArgs {
    double *firstMatrix;
    double *secondMatrix;
    double *multiplyResult;
    int matrixSize;
    int startIndex;
    int endIndex;
    int threadID;
} threadArgs[500];

/**
 * Умножение матриц текущего потока
 * @param pThreadArgs Параметры для текущего потока
 * @return Пустой указатель (работа с текущим потокм завершена)
 */
void *pthreadMultiplyMatrix(void *pThreadArgs) {
    int column = 0;
    int row = 0;
    double temp = 0;
    auto *args = (struct matrixArgs *) pThreadArgs;

    int mSize = args->matrixSize;
    int startIndex = args->startIndex;
    int endIndex = args->endIndex;
    double *firstMatrix = args->firstMatrix;
    double *secondMatrix = args->secondMatrix;
    double *answer = args->multiplyResult;

    auto startTime = chrono::high_resolution_clock::now();
    // строки первой матрицы
    for (int i = startIndex; i < endIndex; i++) {
        row = i * mSize;
        // столбцы второй матрицы
        for (int j = 0; j < mSize; j++) {
            column = 0;
            // столбец первой * строка второй матрицы
            for (int k = 0; k < mSize; k++) {
                temp += firstMatrix[row + k] * secondMatrix[j + column];
                column += mSize;
            }
            answer[row + j] = temp;
            temp = 0;
        }
    }
//    cout << endl << "Время выполнения потока " << args->threadID << ": " << getWorkingTime(startTime) << " сек.";
    pthread_exit(nullptr);
    return nullptr;
}

/**
 * Выделение памяти для матрицы
 * @param size размер матрицы
 * @return Матрица
 */
double *initMatrixSpace() {
    auto *matrix = (double *) malloc(matrixSize * matrixSize * sizeof(double));
    return matrix;
}

/**
 * Проверка введенных данных
 * @return true если настройки вычислений верны
 */
bool validateData() {
    bool valid = false;

    if (matrixSize <= 0) {
        cout << endl << "Ошибка: Размер матрицы некорректен";
        valid = false;
    } else {
        valid = true;
    }

    if (threadNum <= 0) {
        cout << endl << "Ошибка: Число потоков некорректно";
        valid = false;
    } else {
        valid = true;
    }

    return valid;
}

/**
 * Начало умножения
 * @param createNewFile true, если записать в новый файл отчета
 */
void startMultiply(bool createNewFile) {
    if (!validateData()) {
        return;
    }

    double totalTime;

    double *firstMatrix;
    double *secondMatrix;
    double *multiplyResult;

    pthread_t THREADS[threadNum];
    pthread_attr_t THREADS_ATTR;

    try {
        cout << endl << endl << "Выделение памяти ";
        if (debug) {
            cout << matrixSize << ", " << threadNum << ", " << threadLib << " ";
        }
        firstMatrix = initMatrixSpace();
        secondMatrix = initMatrixSpace();
        multiplyResult = initMatrixSpace();
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
                firstMatrix[i + j * matrixSize] = getRandomDouble();
                secondMatrix[i + j * matrixSize] = getRandomDouble();
            }
        }
        cout << "Успешно";
    } catch (...) {
        cout << "Ошибка при создании матриц";
        return;
    }

    if (threadLib == "pthread") {
        try {
            cout << endl << endl << "Умножение ";

            if (debug) {
                cout << matrixSize << ", " << threadNum << ", " << threadLib << " ";
            }

            auto startTime = chrono::high_resolution_clock::now();
            pthread_attr_init(&THREADS_ATTR);
            pthread_attr_setdetachstate(&THREADS_ATTR, PTHREAD_CREATE_JOINABLE);
            int step = (int) ((double) matrixSize / (double) threadNum);
            int startIndex = 0;
            for (int i = 0; i < threadNum; i++) {
                threadArgs[i].firstMatrix = firstMatrix;
                threadArgs[i].secondMatrix = secondMatrix;
                threadArgs[i].multiplyResult = multiplyResult;
                threadArgs[i].matrixSize = matrixSize;
                threadArgs[i].startIndex = startIndex;
                startIndex += step;
                threadArgs[i].endIndex = (i == threadNum - 1) ? matrixSize : startIndex;
                threadArgs[i].threadID = i;

                try {
                    pthread_create(&THREADS[i], &THREADS_ATTR, pthreadMultiplyMatrix, (void *) &threadArgs[i]);
                } catch (...) {
                    cout << "Ошибка при работе с потоком ";
                    return;
                }
            }

            pthread_attr_destroy(&THREADS_ATTR);

            for (unsigned long long i : THREADS) {
                pthread_join(i, nullptr);
            }

            totalTime = getWorkingTime(startTime);
            cout << "Успешно" << endl;
            reportFile(createNewFile, totalTime);

            if (!debug) {
                cout << endl << "Файл отчета: " << reportFileName;
            }
        } catch (...) {
            cout << "Ошибка при умножении матриц";
            return;
        }
    } else if (threadLib == "omp") {
        cout << endl << endl << "Умножение ";

        if (debug) {
            cout << matrixSize << ", " << threadNum << ", " << threadLib << " ";
        }

        auto startTime = chrono::high_resolution_clock::now();
        omp_set_dynamic(0); // отключение функции динамического числа потоков
        omp_set_num_threads(threadNum);

#pragma omp parallel for shared(firstMatrix, secondMatrix, multiplyResult, matrixSize)
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
                for (int k = 0; k < matrixSize; k++) {
                    multiplyResult[i + j * matrixSize] +=
                            firstMatrix[i + k * matrixSize] * secondMatrix[k + j * matrixSize];
                }
            }
        }

        totalTime = getWorkingTime(startTime);
        cout << "Успешно" << endl;
        reportFile(createNewFile, totalTime);
        if (!debug) {
            cout << endl << "Файл отчета: " << reportFileName;
        }
    } else {
        cout << endl << "Некорректная библиотека потоков";
    }

    freeMatrixSpace(firstMatrix);
    freeMatrixSpace(secondMatrix);
    freeMatrixSpace(multiplyResult);
}

/**
 * Ввод в меню
 * @return Пользовательский ввод
 */
int switchMenu() {
    int userInput;

    cin >> userInput;

    if (userInput == 1) {
        initMatrixSize();
    } else if (userInput == 2) {
        initThreadNum();
    } else if (userInput == 3) {
        initThreadLib();
    } else if (userInput == 4) {
        startMultiply(true);
    } else if (userInput == 0) {
        cout << endl << "До свидания" << endl << endl;
    } else {
        cout << endl << "Некорректный ввод";
    }

    return userInput;
}

/**
 * Печать меню
 */
void printMenu() {
    cout << endl << "------------------------------------------------------------";
    cout << endl << "Текущие настройки: размер матриц " << matrixSize << "x" << matrixSize << ", потоков " << threadNum
         << ", " << threadLib;
    cout << endl << "[1] Ввести размер матриц";
    cout << endl << "[2] Ввести количество потоков";
    cout << endl << "[3] Выбрать библиотеку потоков";
    cout << endl << "[4] Начать вычисления";
    cout << endl << "[0] Выход";
    cout << endl << "> ";
}

/**
 * Режим отладки
 */
void runDebug() {
    if (serialLaunch) {
        int lowSize = 1000;
        int mediumSize = 3000;
        int largeSize = 5000;

        int lowThreadNum = 4;
        int mediumThreadNum = 8;
        int largeThreadNum = 16;

        threadLib = "pthread";
        threadNum = lowThreadNum;
        matrixSize = lowSize;
        startMultiply(true);

        threadNum = mediumThreadNum;
        matrixSize = lowSize;
        startMultiply(false);

        threadNum = largeThreadNum;
        matrixSize = lowSize;
        startMultiply(false);

        threadNum = lowThreadNum;
        matrixSize = mediumSize;
        startMultiply(false);

        threadNum = mediumThreadNum;
        matrixSize = mediumSize;
        startMultiply(false);

        threadNum = largeThreadNum;
        matrixSize = mediumSize;
        startMultiply(false);

        threadNum = lowThreadNum;
        matrixSize = largeSize;
        startMultiply(false);

        threadNum = mediumThreadNum;
        matrixSize = largeSize;
        startMultiply(false);

        threadNum = largeThreadNum;
        matrixSize = largeSize;
        startMultiply(false);

        threadLib = "omp";
        threadNum = lowThreadNum;
        matrixSize = lowSize;
        startMultiply(false);

        threadNum = mediumThreadNum;
        matrixSize = lowSize;
        startMultiply(false);

        threadNum = largeThreadNum;
        matrixSize = lowSize;
        startMultiply(false);

        threadNum = lowThreadNum;
        matrixSize = mediumSize;
        startMultiply(false);

        threadNum = mediumThreadNum;
        matrixSize = mediumSize;
        startMultiply(false);

        threadNum = largeThreadNum;
        matrixSize = mediumSize;
        startMultiply(false);

        threadNum = lowThreadNum;
        matrixSize = largeSize;
        startMultiply(false);

        threadNum = mediumThreadNum;
        matrixSize = largeSize;
        startMultiply(false);

        threadNum = largeThreadNum;
        matrixSize = largeSize;
        startMultiply(false);

        cout << endl << endl << "Файл отчета: " << reportFileName << endl << endl;
        return;
    }
    threadNum = 4;
    threadLib = "pthread";
    matrixSize = 1000;
    startMultiply(true);
    cout << endl << endl << "Файл отчета: " << reportFileName << endl << endl;
}

/**
 * Точка входа в программу
 * @return статус завершения программы
 */
int main() {
    srand(static_cast <unsigned> (time(nullptr)));
    if (debug) {
        runDebug();
    } else {
        do {
            printMenu();
        } while (switchMenu() != 0);
    }
    return 0;
}