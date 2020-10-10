#include <iostream>
#include "mathFunc.h"
#include "randNumber.h"
#include "fileExport.h"
using namespace std;

double getTaskPerformance(int opNumber, float time) {
    return (double) opNumber / time;
}

int getNumberTest() {
    int numberTest;
    cout << "\nВведите число испытаний (от 10 и больше) ";
    cin >> numberTest;
    if (numberTest < 10) {
        cout << "\nНельзя ввести меньше 10 испытаний\n";
        return 0;
    } else 
        return numberTest;
}

int getTestType() {
    int testType;
    cout << "\nВыберите задачу:";
    cout << "\n1. Нахождение синуса";
    cout << "\n2. Нахождение логарифма";
    cout << "\n3. Нахождение корня";
    cout << "\n>";
    cin >> testType;
    if (testType == 1) {
        return 1;
    } else if (testType == 2) {
        return 2;
    } else if (testType == 3) {
        return 3;
    } else {
        cout << "\nОшибка ввода\n";
        return 0;
    }
}

void startBenchmark(int benchmarkType) {
    const int size = 100000;
    double performance;
    float totalTime = 0;
    float averageTime;
    float relativeInaccuracy;
    float absoluteInaccuracy;

    int testType = getTestType();
    int numberTest = getNumberTest();

    int randomIntArr[size];
    float randomFloatArr[size];
    double randomDoubleArr[size];
    
    float testTimeResult[numberTest];
    double resultArr[size];

     if (testType == 1) { // sin
            for (int j = 0; j < numberTest; j++) {

                if (benchmarkType == 1) { // int
                    for (int k = 0; k < size; k++) { 
                        randomIntArr[k] = getRandomInt();
                    }
                } else if (benchmarkType == 2) { // float
                    for (int k = 0; k < size; k++) { 
                        randomIntArr[k] = getRandomFloat();
                    }
                } else if (benchmarkType == 3) { // double
                    for (int k = 0; k < size; k++) { 
                        randomIntArr[k] = getRandomDouble();
                    }
                } else {
                    cout << "\nОшибка ввода\n";
                    return;
                }
               
                const int runTime = clock();
                for (int i = 0; i < size; i++) {
                    resultArr[i] = getSin(randomIntArr[i]);
                }

                testTimeResult[j] = ((float) clock() - (float) runTime) / CLOCKS_PER_SEC;
//                printf("\n[%d] %f сек", j + 1, testTimeResult[j]);
                totalTime += testTimeResult[j];
            }

        } else if (testType == 2) { // log

            for (int j = 0; j < numberTest; j++) {
                 if (benchmarkType == 1) { // int
                    for (int k = 0; k < size; k++) { 
                        randomIntArr[k] = getRandomInt();
                    }
                } else if (benchmarkType == 2) { // float
                    for (int k = 0; k < size; k++) { 
                        randomIntArr[k] = getRandomFloat();
                    }
                } else if (benchmarkType == 3) { // double
                    for (int k = 0; k < size; k++) { 
                        randomIntArr[k] = getRandomDouble();
                    }
                } else {
                    cout << "\nОшибка ввода\n";
                    return;
                }
                
                const int runTime = clock();
                for (int i = 0; i < size; i++) {
                    resultArr[i] = getLog(randomIntArr[i]);
                }
                testTimeResult[j] = ((float) clock() - (float) runTime) / CLOCKS_PER_SEC;
//                printf("\n[%d] %f сек", j + 1, testTimeResult[j]);
                totalTime += testTimeResult[j];
            }

        } else if (testType == 3) { // sqrt

            for (int j = 0; j < numberTest; j++) {
                 if (benchmarkType == 1) { // int
                    for (int k = 0; k < size; k++) { 
                        randomIntArr[k] = getRandomInt();
                    }
                } else if (benchmarkType == 2) { // float
                    for (int k = 0; k < size; k++) { 
                        randomIntArr[k] = getRandomFloat();
                    }
                } else if (benchmarkType == 3) { // double
                    for (int k = 0; k < size; k++) { 
                        randomIntArr[k] = getRandomDouble();
                    }
                } else {
                    cout << "\nОшибка ввода\n";
                    return;
                }
                const int runTime = clock();
                for (int i = 0; i < size; i++) {
                    resultArr[i] = getSqrt(randomIntArr[i]);
                }
                testTimeResult[j] = ((float) clock() - (float) runTime) / CLOCKS_PER_SEC;
//                printf("\n[%d] %f сек", j + 1, testTimeResult[j]);
                totalTime += testTimeResult[j];
            }

        } else {
            return;
        }

        averageTime = totalTime / numberTest;
        absoluteInaccuracy = abs(testTimeResult[0] - averageTime);
        relativeInaccuracy = (absoluteInaccuracy / averageTime) * 0.1;
        performance = getTaskPerformance(1, totalTime);

        if (benchmarkType == 1) { // int
            fileExport("int", "sin", "int, double", numberTest, 1, averageTime, absoluteInaccuracy, relativeInaccuracy,
                       performance);
                } else if (benchmarkType == 2) { // float
                    fileExport("float", "sin", "float, double", numberTest, 1, averageTime, absoluteInaccuracy, relativeInaccuracy,
                       performance);
                } else if (benchmarkType == 3) { // double
                    fileExport("double", "sin", "double", numberTest, 1, averageTime, absoluteInaccuracy, relativeInaccuracy,
                       performance);
                } else {
                    cout << "\nОшибка ввода\n";
                    return;
                }
            //            printf("\nОбщее время: %f сек", totalTime);
            //            printf("\nСреднее время: %f сек", averageTime);
            //            printf("\nАбсолютная погрешность: %f сек", absoluteInaccuracy);
            //            printf("\nОтносительная погрешность: %f %%", relativeInaccuracy);       
    
}

int main() {
    srand(static_cast <unsigned> (time(nullptr))); 

    int menuInput = 0;

    // cout << getSin(1) << endl
    //     << getSin((float)1.0) << endl
    //     << getSin((double)1.0);

    do {
        cout << "\n\n1. Протестировать значения типа int";
        cout << "\n2. Протестировать значения типа float";
        cout << "\n3. Протестировать значения типа double";
        cout << "\n0. Выход";
        cout << "\n>";

        cin >> menuInput;

        switch (menuInput) {
            case 1:
                startBenchmark(1); // int
                break;
            case 2:
                startBenchmark(2); // float
                break;
            case 3:
                startBenchmark(3); // double
                break;
            case 0:
                cout << "\nВыход\n\n";
                break;
            default:
                cout << "\nНеверный ввод\n";
                break;
        }
    } while (menuInput != 0);


    return 0;
}