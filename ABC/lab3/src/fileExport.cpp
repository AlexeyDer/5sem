#include "fileExport.h"

string fileCreate(string memoryType) {
       const string &filename = memoryType + ".csv";
       ofstream myFile(filename);
       myFile << "MemoryType;" << "BlockSize(Byte);" << "ElementType;" << "BufferSize;"
           << "LaunchNum;" << "Timer;" << "WriteTime;" << "AverageWriteTime;" << "WriteBandwidth;"
           << "AbsError(write);" << "RelError(write);" << "ReadTime;" << "AverageReadTime;"
           << "ReadBandwidth;" << "AbsError(read);" << "RelError(read);" << endl;

       // cout << "\n\nФайл " << filename << " успешно создан!";
       myFile.close();
       return filename;
}

void fileExport(const string &fileName, const string &memoryType, int blockSize,
              const string &ElementType, int BufferSize, int LaunchNum, string Timer, float WriteTime, float AvWriteTime,
              float WriteBandwidth, 
              float AbsErrorWrite,float RelErrorWrite,
              float ReadTime, float AvReadTime,
              float ReadBandwidth, 
              float AbsErrorRead,float RelErrorRead) {
  
    fstream outCSV(fileName, ios_base::app);

       outCSV << memoryType << ";" << blockSize << ";" << ElementType << ";" << BufferSize << ";"
           << LaunchNum << ";" << Timer << ";" << WriteTime << ";" << AvWriteTime << ";" << WriteBandwidth << ";"
           << AbsErrorWrite << ";" << RelErrorWrite << ";" << ReadTime << ";" << AvReadTime << ";"
           << ReadBandwidth << ";" << AbsErrorRead << ";" << RelErrorRead << ";" << endl; 

    outCSV.close();
}