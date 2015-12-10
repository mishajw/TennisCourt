//
// Created by misha on 10/12/15.
//

#ifndef TENNISCOURT_CSVEXPORTER_H
#define TENNISCOURT_CSVEXPORTER_H

#include "Line.h"

using namespace std;

class CSVExporter {
public:
    void run(vector<pair<string, Line>> labeledLines, string path);
private:
    string labeledLineToString(pair<string, Line> labeledLine);
    vector<cv::Point> getPointsOnLine(Line line, double amount);
    void writeStringToFile(string content, string path);
};


#endif //TENNISCOURT_CSVEXPORTER_H
