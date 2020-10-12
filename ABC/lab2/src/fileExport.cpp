#include "fileExport.h"

string fileCreate(string dataType, const string &Task) {
       const string &filename = dataType + "-" + Task + ".csv";
       ofstream myFile(filename);
       myFile << "PModel;" << "Task;" << "OpType;" << "Opt;"
           << "LNum;" << "InsCount;" << "Timer;" << "AvTime (sec);" << "AbsError (sec);"
           << "RelError (%);" << "TaskPerf;\n";

       cout << "\n\nФайл " << filename << " успешно создан!";
       return filename;
}

void fileExport(const string &fileName, const string &dataType, const string &Task, const string &OpType, int LNum, int InsCount, float AvTime,
                float AbsError,
                float RelError, double TaskPerf) {
    string PModel = "AMD A9-9420 RADEON R5 (x86)";
    string Opt = "-O1";
       
    fstream outCSV(fileName, ios_base::app);
    outCSV << PModel << ";" << Task << ";" << OpType << ";" << Opt << ";" << LNum << ";" << InsCount << ";" <<"clock()" << ";" << AvTime
           << ";" << AbsError << ";" << RelError << ";" << TaskPerf << ";\n";
    outCSV.close();
}