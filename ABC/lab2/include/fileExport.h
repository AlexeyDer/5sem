#ifndef FILEEXPORT_H
#define FILEEXPORT_H

using namespace std;
// #include <cstdlib>
#include <iostream>
#include <fstream>

void fileExport(const string &dataType, const string &Task, const string &OpType, int LNum, int InsCount, float AvTime,
                float AbsError,
                float RelError, double TaskPerf);


#endif