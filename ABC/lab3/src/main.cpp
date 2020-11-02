#include <iostream>
#include <string>
#include "fileExport.h"
#include <fstream>
#include <time.h>
#include <math.h>


using namespace std;

int getRandomInt() {
    int min = 0;
    int max = 1024;
    static const double randomInt = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
   
    return static_cast<int>(rand() * randomInt * (max - min + 1) + min);
}

void performanceOfTheMemorySubsystem(string memoryType, string ElementType, float blockSize, int testsCount, string path, string filename, string key, int countIn, string type) {
    
    int BufferSize = blockSize / sizeof(int);

    if (memoryType == "L1") {
        BufferSize  = (160) / sizeof(int);
    }
    if (memoryType == "L2") {
        BufferSize  = (1024) / sizeof(int);
    }
    if (memoryType == "L3") {
        BufferSize  = (2048) / sizeof(int);
    }

    int randomArray[BufferSize];
    int a[BufferSize];

    // blockSize /= 1e+6;

    struct timespec mt1, mt2; 
    
    float totalWriteTime = 0, totalReadTime = 0;
    float writeTime[testsCount];
    float readTime[testsCount];

    // string filename = fileCreate(memoryType);

    for (int j = 0; j < testsCount; j++) { 

        for (int i = 0; i <  BufferSize; i++) {
            randomArray[i] = getRandomInt();
        }
    
        ofstream out(path);

        //-------write---------
        if (out.is_open()) {
            if (path != "MAS") {
                clock_gettime (CLOCK_REALTIME, &mt1);
                for (int i = 0; i <  BufferSize; i++) {
                    out << randomArray[i] << " ";
                }
                clock_gettime (CLOCK_REALTIME, &mt2);
            } else {
                clock_gettime (CLOCK_REALTIME, &mt1);
                for (int i = 0; i <  BufferSize; i++) {
                    a[i] = randomArray[i];
                }
                clock_gettime (CLOCK_REALTIME, &mt2);
            }
            out.close();
        }
       

        writeTime[j] = ((((float)mt2.tv_sec - (float)mt1.tv_sec) + ((float)mt2.tv_nsec - (float) mt1.tv_nsec) / 1000000));
        // cout << fixed << setprecision(9) << writeTime[j] << endl;
        // printf( "%lf\n", writeTime[j]);
        totalWriteTime += writeTime[j];
        float averageWriteTime = totalWriteTime / (j + 1);
        float writeBandwidth = blockSize / averageWriteTime;
         // * 1000000;    
        float AbsErrorWrite = abs(writeTime[0] - averageWriteTime);
        float RelErrorWrite = (AbsErrorWrite / averageWriteTime) * 0.1;

        //-------read---------
        ifstream in(path);

        char ch;
        if (in.is_open()) {
            if (path != "MAS") {
                clock_gettime (CLOCK_REALTIME, &mt1);
                while (!in.eof()){
                    in >> ch;
                }
                clock_gettime (CLOCK_REALTIME, &mt2);
            } else {
                clock_gettime (CLOCK_REALTIME, &mt1);
                for (int i = 0; i <  BufferSize; i++) {
                    a[i];
                }
                clock_gettime (CLOCK_REALTIME, &mt2);
            }
            in.close();
        }  
         

        readTime[j] = ((((float)mt2.tv_sec - (float)mt1.tv_sec) + ((float)mt2.tv_nsec - (float) mt1.tv_nsec) / 1000000));
        totalReadTime += readTime[j];
        float averageReadTime = totalReadTime / (j + 1);
        float readBandwidth = (blockSize / averageReadTime);
        // * 1000000;
        float AbsErrorRead = abs(readTime[0] - averageReadTime);
        float RelErrorRead = (AbsErrorRead / averageReadTime) * 0.1;

    
        fileExport(filename, memoryType, countIn,ElementType, BufferSize * sizeof(int), j + 1, "clock_gettime()", writeTime[j], averageWriteTime, writeBandwidth,
        AbsErrorWrite, RelErrorWrite, readTime[j], averageReadTime, readBandwidth, AbsErrorRead, RelErrorRead, type);

        if (key == "y") {
            blockSize += 4 * 1024 * 1024;
            countIn += 4;
        }
        
        }

}




int main(int argc, char* argv[]) {
    srand(static_cast <unsigned> (time(nullptr))); 

    string memoryType = argv[2], ElementType = "int";

    string bs = argv[4], res = "";

    float blockSize;
    bool f = true;
    int countIn;
    string type;

    for (int i = 0; i < bs.length(); i++) {
        if (bs[i] == 'K') {
            blockSize = stoi(res) * 1024 / sizeof(int); 
            type = "Kb";
            f = false;
            break;
        }
        if (bs[i] == 'M') {
            blockSize = stoi(res) * 1024 * 1024 / sizeof(int);
            type = "Mb";
            f = false;
            break;
        }
        res += bs[i];
    }
    if (f) {
        blockSize = stoi(res) / sizeof(int);
        type = "Byte";
    }
    countIn = stoi(res);

  
    int testsCount = stoi(argv[6]);
    string path;

    string filename;

    if (memoryType == "RAM" || memoryType  == "L1"|| memoryType  == "L2" || memoryType  == "L3") {
        path = "MAS";
    } else if (memoryType == "SSD") {
        path = "file.txt";
    } else if (memoryType == "FLASH") {
        path = "/media/alexey_der/ALEXEY_DER/FLASH/file.txt";
    } else { 
        cout << "Write a MEMORYTYPE!" << endl;
        return 1;
    }

    if (memoryType  == "L1"|| memoryType  == "L2"|| memoryType  == "L3") {
        filename = fileCreate("CASH");
    } else {
        filename = fileCreate(memoryType);
    }

    string key;
    cout << "Write 'y' for different size of data block: " << endl;
    cin >> key;
    
    performanceOfTheMemorySubsystem(memoryType, ElementType, blockSize, testsCount, path, filename, key, countIn, type);


    return 0;
}