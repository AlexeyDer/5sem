#include "fileExport.h"

void fileExport(const string &dataType, const string &Task, const string &OpType, int LNum, int InsCount, float AvTime,
                float AbsError,
                float RelError, double TaskPerf) {
    string PModel = "AMD A9-9420 RADEON R5 (x86)";
    string Opt = "CFLAGS=\"-O1\"";
    ofstream outCSV;
    string format = ".csv";
    string fileName = dataType + "-" + Task + "-" + to_string(AvTime) + "-" + to_string(TaskPerf) + format;
    outCSV.open(fileName);
    outCSV << "PModel;" << "Task;" << "OpType;" << "Opt;"
           << "LNum;" << "InsCount;" << "AvTime (sec);" << "AbsError (sec);"
           << "RelError (%);" << "TaskPerf;" << "Type timer;";
    outCSV << endl;
    outCSV << PModel << ";" << Task << ";" << OpType << ";" << Opt << ";" << LNum << ";" << InsCount << ";" << AvTime
           << ";" << AbsError << ";" << RelError << ";" << TaskPerf << ";" << "clock();";
    outCSV.close();
    cout << "\n\nУспешно. Результаты бенчмарка в файле " << fileName << "";
}