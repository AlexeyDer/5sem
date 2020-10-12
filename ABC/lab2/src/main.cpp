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
    cout << "\nВыберите задачу:" << endl;
    cout << "1. Нахождение синуса" << endl;
    cout << "2. Нахождение логарифма" << endl;
    cout << "3. Нахождение корня" << endl;

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
    int insCount = 0;
    string name;
     
    if (numberTest == 0) {
        return;
    }

     if (testType == 1) { // sin
            name = "sin";
            string fileName;
            string dataType;

            if (benchmarkType == 1) {
                fileName = fileCreate("int", name);
                dataType = "int";
            }
            else if (benchmarkType == 2) {
                fileName = fileCreate("float", name);
                dataType = "float";
            } else if (benchmarkType == 3) {
                fileName = fileCreate("double", name);
                dataType = "double";
            } else {
                return;
            }

            for (int j = 0; j < numberTest; j++) {
                int runTime = 0;
                
                if (benchmarkType == 1) { // int
                    for (int k = 0; k < size; k++) { 
                        randomIntArr[k] = getRandomInt();
                    }

                    runTime = clock();
                    for (int i = 0; i < size; i++) {
                        resultArr[i] = getSin(randomIntArr[i]);
                    }
                } else if (benchmarkType == 2) { // float
                    for (int k = 0; k < size; k++) { 
                        randomFloatArr[k] = getRandomFloat();
                    }
                    
                    runTime = clock();
                    for (int i = 0; i < size; i++) {
                        resultArr[i] = getSin(randomFloatArr[i]);
                    }

                } else if (benchmarkType == 3) { // double
                    for (int k = 0; k < size; k++) { 
                        randomDoubleArr[k] = getRandomDouble();
                    }

                    runTime = clock();
                    for (int i = 0; i < size; i++) {
                        resultArr[i] = getSin(randomDoubleArr[i]);
                    }
                } else {
                    cout << "\nОшибка ввода\n";
                    return;
                }
               
                testTimeResult[j] = ((float) clock() - (float) runTime) / CLOCKS_PER_SEC;
                totalTime += testTimeResult[j];
                insCount++;

                averageTime = totalTime / insCount;
                absoluteInaccuracy = abs(testTimeResult[0] - averageTime);
                relativeInaccuracy = (absoluteInaccuracy / averageTime) * 0.1;
                performance = getTaskPerformance(1, totalTime);

                fileExport(fileName, dataType, name, dataType, numberTest, insCount, averageTime, absoluteInaccuracy, relativeInaccuracy, performance);

            }

        } else if (testType == 2) { // log
            name = "log";

            string fileName;
            string dataType;

            if (benchmarkType == 1) {
                fileName = fileCreate("int", name);
                dataType = "int";
            }
            else if (benchmarkType == 2) {
                fileName = fileCreate("float", name);
                dataType = "float";
            } else if (benchmarkType == 3) {
                fileName = fileCreate("double", name);
                dataType = "double";
            } else {
                return;
            }
            
            for (int j = 0; j < numberTest; j++) {
                int runTime = 0;
                
                if (benchmarkType == 1) { // int
                    for (int k = 0; k < size; k++) { 
                        randomIntArr[k] = getRandomInt();
                    }

                    runTime = clock();
                    for (int i = 0; i < size; i++) {
                        resultArr[i] = getLog(randomIntArr[i]);
                    }
                } else if (benchmarkType == 2) { // float
                    for (int k = 0; k < size; k++) { 
                        randomFloatArr[k] = getRandomFloat();
                    }
                    
                    runTime = clock();
                    for (int i = 0; i < size; i++) {
                        resultArr[i] = getLog(randomFloatArr[i]);
                    }

                } else if (benchmarkType == 3) { // double
                    for (int k = 0; k < size; k++) { 
                        randomDoubleArr[k] = getRandomDouble();
                    }

                    runTime = clock();
                    for (int i = 0; i < size; i++) {
                        resultArr[i] = getLog(randomDoubleArr[i]);
                    }
                } else {
                    cout << "\nОшибка ввода\n";
                    return;
                }
                insCount++;
                testTimeResult[j] = ((float) clock() - (float) runTime) / CLOCKS_PER_SEC;
                totalTime += testTimeResult[j];

                averageTime = totalTime / insCount;
                absoluteInaccuracy = abs(testTimeResult[0] - averageTime);
                relativeInaccuracy = (absoluteInaccuracy / averageTime) * 0.1;
                performance = getTaskPerformance(1, totalTime);

                fileExport(fileName, dataType, name, dataType, numberTest, insCount, averageTime, absoluteInaccuracy, relativeInaccuracy, performance);

            }
        } else if (testType == 3) { // sqrt
            name = "sqrt";
            string fileName;
            string dataType;

            if (benchmarkType == 1) {
                fileName = fileCreate("int", name);
                dataType = "int";
            }
            else if (benchmarkType == 2) {
                fileName = fileCreate("float", name);
                dataType = "float";
            } else if (benchmarkType == 3) {
                fileName = fileCreate("double", name);
                dataType = "double";
            } else {
                return;
            }


            for (int j = 0; j < numberTest; j++) {
                int runTime = 0;
                
                if (benchmarkType == 1) { // int
                    for (int k = 0; k < size; k++) { 
                        randomIntArr[k] = getRandomInt();
                    }

                    runTime = clock();
                    for (int i = 0; i < size; i++) {
                        resultArr[i] = getSqrt(randomIntArr[i]);
                    }
                } else if (benchmarkType == 2) { // float
                    for (int k = 0; k < size; k++) { 
                        randomFloatArr[k] = getRandomFloat();
                    }
                    
                    runTime = clock();
                    for (int i = 0; i < size; i++) {
                        resultArr[i] = getSqrt(randomFloatArr[i]);
                    }

                } else if (benchmarkType == 3) { // double
                    for (int k = 0; k < size; k++) { 
                        randomDoubleArr[k] = getRandomDouble();
                    }

                    runTime = clock();
                    for (int i = 0; i < size; i++) {
                        resultArr[i] = getSqrt(randomDoubleArr[i]);
                    }
                } else {
                    cout << "\nОшибка ввода\n";
                    return;
                }   


                insCount++;
                testTimeResult[j] = ((float) clock() - (float) runTime) / CLOCKS_PER_SEC;
                totalTime += testTimeResult[j];

                averageTime = totalTime / insCount;
                absoluteInaccuracy = abs(testTimeResult[0] - averageTime);
                relativeInaccuracy = (absoluteInaccuracy / averageTime) * 0.1;
                performance = getTaskPerformance(1, totalTime);

                fileExport(fileName, dataType, name, dataType, numberTest, insCount, averageTime, absoluteInaccuracy, relativeInaccuracy, performance);
            }

        } else {
            return;
        }
        // cout << endl << averageTime << endl;
        // cout << endl << performance << endl;
}

int main() {
    srand(static_cast <unsigned> (time(nullptr))); 

    int menuInput = 0;

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