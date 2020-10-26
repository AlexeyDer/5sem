#include <iostream>
#include <string>
#include "fileExport.h"


using namespace std;

void performanceOfTheMemorySubsystem() {

}

int getRandomInt() {
    int min = 0;
    int max = 1024;
    static const double randomInt = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
   
    return static_cast<int>(rand() * randomInt * (max - min + 1) + min);
}


int main(int argc, char* argv[]) {
    srand(static_cast <unsigned> (time(nullptr))); 


    string memoryType = argv[2], ElementType = "int";


    int blockSize = stoi(argv[4]), testsCount = stoi(argv[6]);
    int BufferSize = blockSize * sizeof(int);
    int randomArray[BufferSize];
    int blockData[BufferSize];

    
    float totalWriteTime = 0, totalReadTime = 0;
    float writeTime[testsCount];
    float readTime[testsCount];

    string filename = fileCreate(memoryType);


    for (int j = 0; j < testsCount; j++) { 

        for (int i = 0; i <  BufferSize; i++) {
            randomArray[i] = getRandomInt();
        }

        int runTime = 0;
        //-------write---------
        runTime = clock();
        for (int i = 0; i <  BufferSize; i++) {
            blockData[i] = randomArray[i];
        }

        writeTime[j] = ((float) clock() - (float) runTime) / CLOCKS_PER_SEC;
        totalWriteTime += writeTime[j];
        float averageWriteTime = totalWriteTime / (j + 1);
        float writeBandwidth = (blockSize / averageWriteTime) * 1000000;
        float AbsErrorWrite = abs(writeTime[0] - averageWriteTime);
        float RelErrorWrite = (AbsErrorWrite / averageWriteTime) * 0.1;


        //-------read---------
        runTime = 0;
        cout << "------READ------" << endl;
        runTime = clock();
        for (int i = 0; i <  BufferSize; i++) {
            cout << blockData[i] << " ";
        }

        readTime[j] = ((float) clock() - (float) runTime) / CLOCKS_PER_SEC;
        totalReadTime += readTime[j];
        float averageReadTime = totalReadTime / (j + 1);
        float readBandwidth = (blockSize / averageReadTime) * 1000000;
        float AbsErrorRead = abs(readTime[0] - averageReadTime);
        float RelErrorRead = (AbsErrorRead / averageReadTime) * 0.1;

        cout << "----------------";

        fileExport(filename, memoryType, blockSize,ElementType, BufferSize, j + 1, "clock()", writeTime[j], averageWriteTime, writeBandwidth,
        AbsErrorWrite, RelErrorWrite, readTime[j], averageReadTime, readBandwidth, AbsErrorRead, RelErrorRead);


    }



    // cout << subsystem << endl << blockSize << endl <<  testsCount << endl;

    // cin.get();
    return 0;
}