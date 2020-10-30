#include <iostream>
#include <string>
#include "fileExport.h"
#include <fstream>
#include <time.h>

using namespace std;

#define BILLION  1000000000L;

int getRandomInt() {
    int min = 0;
    int max = 1024;
    static const double randomInt = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
   
    return static_cast<int>(rand() * randomInt * (max - min + 1) + min);
}

void performanceOfTheMemorySubsystem(string memoryType, string ElementType, int blockSize, int testsCount) {
    int BufferSize = blockSize / sizeof(int);
    int randomArray[BufferSize];
    
    struct timespec mt1, mt2; 
    long int tt;      
   
    // int blockData[BufferSize];

    
    float totalWriteTime = 0, totalReadTime = 0;
    float writeTime[testsCount];
    float readTime[testsCount];

    string filename = fileCreate(memoryType);


    for (int j = 0; j < testsCount; j++) { 

        for (int i = 0; i <  BufferSize; i++) {
            randomArray[i] = getRandomInt();
        }

        int runTime = 0;

        ofstream out("file.txt");

        //-------write---------
        if (out.is_open()) {
            clock_gettime (CLOCK_REALTIME, &mt1);
            for (int i = 0; i <  BufferSize; i++) {
                out << randomArray[i] << " ";
            }
            clock_gettime (CLOCK_REALTIME, &mt2);
        }
        // tt= 1000000000*();
        writeTime[j] = (1000000000 * (mt2.tv_sec - mt1.tv_sec ) + (mt2.tv_nsec - mt1.tv_nsec)) / CLOCKS_PER_SEC; //
        cout << writeTime[j] << endl;
        // printf( "%lf\n", writeTime[j]);
        totalWriteTime += writeTime[j];
        float averageWriteTime = totalWriteTime / (j + 1);
        float writeBandwidth = ((blockSize / averageWriteTime) * 1000000) / 1048576;
        float AbsErrorWrite = abs(writeTime[0] - averageWriteTime);
        float RelErrorWrite = (AbsErrorWrite / averageWriteTime) * 0.1;

        //-------read---------
        ifstream in("file.txt");

        string line;
 
        runTime = 0;
        if (in.is_open()) {
            runTime = clock();
            while (getline(in, line)){
            }
        }    
         

        readTime[j] = ((float) clock() - (float) runTime) / CLOCKS_PER_SEC;
        totalReadTime += readTime[j];
        float averageReadTime = totalReadTime / (j + 1);
        float readBandwidth = (blockSize / averageReadTime) * 1000000;
        float AbsErrorRead = abs(readTime[0] - averageReadTime);
        float RelErrorRead = (AbsErrorRead / averageReadTime) * 0.1;

        fileExport(filename, memoryType, blockSize,ElementType, BufferSize, j + 1, "clock()", writeTime[j], averageWriteTime, writeBandwidth,
        AbsErrorWrite, RelErrorWrite, readTime[j], averageReadTime, readBandwidth, AbsErrorRead, RelErrorRead);

    }

}



int main(int argc, char* argv[]) {
    srand(static_cast <unsigned> (time(nullptr))); 

    string memoryType = argv[2], ElementType = "int";
    int blockSize = stoi(argv[4]), testsCount = stoi(argv[6]);

    performanceOfTheMemorySubsystem(memoryType, ElementType, blockSize, testsCount);

    return 0;
}