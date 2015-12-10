//
// Created by misha on 09/12/15.
//

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "Line.h"

#ifndef TENNISCOURT_COURTLINE_H
#define TENNISCOURT_COURTLINE_H

using namespace std;

class CourtLine {
public:
    Line line;
    const char* name;
    vector<double> neighbours;

    CourtLine(Line _line, vector<Line> otherLines);
    CourtLine(const char* _name, vector<double> _neighbours);
    CourtLine(const char* _name, double *_neighbours, int neighbourSize);

    void initNeighboursWithLines(vector<Line> lines);
    double compareWith(CourtLine *otherLine);

    // Factory functions
    static vector<CourtLine> createAllLines();

private:
    bool isRightAngle(Line l);

    // Accuracy
    static constexpr double ACCURACY_ANGLES = CV_PI / 6;
    static constexpr double ACCURACY_PLACEMENT = 0.4;
    // Distances between lines
    static constexpr double SIDE_TO_SINGLES = (27.0 / 36.0) / 2.0;
    static constexpr double BASE_TO_SERVICE = 21.0 / 39.0;

    // Factory functions
    static CourtLine createBaseLine();
    static CourtLine createServiceLine();
    static CourtLine createCentreServiceLine();
    static CourtLine createSideLine();
    static CourtLine createSinglesSideLine();
};

#endif //TENNISCOURT_COURTLINE_H
