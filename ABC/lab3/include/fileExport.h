#ifndef FILEEXPORT_H
#define FILEEXPORT_H

using namespace std;

#include <iostream>
#include <fstream>
#include <iomanip>

string fileCreate(string memoryType);
void fileExport(const string &fileName, const string &memoryType, float blockSize,
              const string &ElementType, int BufferSize, int LaunchNum, string Timer, float WriteTime, float AvWriteTime,
              float WriteBandwidth, 
              float AbsErrorWrite,float RelErrorWrite,
              float ReadTime, float AvReadTime,
              float ReadBandwidth, 
              float AbsErrorRead,float RelErrorRead);

#endif