#include "fileExport.h"

string fileCreate(string memoryType) {
       const string &filename = memoryType + ".csv";
       ofstream myFile(filename);
       myFile << "MemoryType;" << "BlockSize;" << "ElementType;" << "BufferSize;"
           << "LaunchNum;" << "Timer;" <<  "WriteTime;" << "AverageWriteTime;" << "WriteBandwidth;"
           << "AbsError(write);" << "RelError(write);" << "ReadTime;" << "AverageReadTime;"
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
              float AbsErrorRead,float RelErrorRead) {
  
    fstream outCSV(fileName, ios_base::app);


       outCSV << memoryType << ";"
           << fixed << setprecision(6)  << blockSize << " Mb;"
           << ElementType << ";"
           << BufferSize << " ?;"
           << LaunchNum << ";" << Timer << ";" 
           << fixed << setprecision(9) <<  WriteTime << " Sec;" 
           << fixed << setprecision(9) << AvWriteTime << " Sec;" 
           << fixed << setprecision(9) <<  WriteBandwidth << "Sec;"
           << fixed << setprecision(9) << AbsErrorWrite << " Sec;"
           << fixed << setprecision(9) << RelErrorWrite << " Sec;"
           << fixed << setprecision(9) << ReadTime << " Sec;"
           << fixed << setprecision(9) << AvReadTime << " Sec;"
           << fixed << setprecision(9) << ReadBandwidth << " Sec;"
           << fixed << setprecision(9) << AbsErrorRead << " Sec ;"
           << fixed << setprecision(9) <<  RelErrorRead << "Sec ;" << endl; 

    outCSV.close();
}