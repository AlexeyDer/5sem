#include "fileExport.h"

string fileCreate(string memoryType) {
    string filename;

    if (memoryType == "CASH") {
        ifstream file;
        file.open("CASH.csv");

        if(file.is_open()) {
            filename = "CASH.csv";
            return filename;
        }
    } 
    filename = memoryType + ".csv";

    ofstream myFile(filename);
    myFile << "MemoryType;" << "BlockSize;" << "ElementType;" << "BufferSize;"
            << "LaunchNum;" << "Timer;" <<  "WriteTime;" << "AverageWriteTime;" << "WriteBandwidth;"
            << "AbsError   (write);" << "RelError   (write);" << "ReadTime;" << "AverageReadTime;"
            << "ReadBandwidth;" << "AbsError(read);" << "RelError(read);" << endl;
    myFile.close();
    
    return filename;
}

void fileExport(const string &fileName, const string &memoryType, float blockSize,
              const string &ElementType, int BufferSize, int LaunchNum, string Timer, float WriteTime, float AvWriteTime,
              float WriteBandwidth, 
              float AbsErrorWrite,float RelErrorWrite,
              float ReadTime, float AvReadTime,
              float ReadBandwidth, 
              float AbsErrorRead,float RelErrorRead, string type) {
  
    fstream outCSV(fileName, ios_base::app);


       outCSV << memoryType << ";"
           << blockSize  << " " << type << ";"
           << ElementType << ";"
           << BufferSize << " Kb;"
           << LaunchNum << ";" << Timer << ";" 
           << fixed << setprecision(10) <<  WriteTime << " Sec;"  //
           << AvWriteTime << " Sec;" 
           <<  WriteBandwidth << " Mb/Sec;"
           << AbsErrorWrite << " Sec;"
           << RelErrorWrite << "  %;"
           << ReadTime << " Sec;"
           << AvReadTime << " Sec;"
           << ReadBandwidth << " Mb/Sec;"
           << AbsErrorRead << " Sec ;"
           <<  RelErrorRead << " % ;" << endl; 

    outCSV.close();
}