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
    const string name;
    const double *neighbours;

    CourtLine(Line _line, string _name, double _neighbours[]);
    map<Line, CourtLine> parsePossibleNeighbours(vector<Line> lines);
    // Factory functions
    static vector<CourtLine> createAllLines(Line line);

private:
    bool isRightAngle(Line l);

    // Accuracy
    static constexpr double ACCURACY_ANGLES = CV_PI / 3;
    static constexpr double ACCURACY_PLACEMENT = 0.2;
    // Distances between lines
    static constexpr double SIDE_TO_SINGLES = (27 / 36) / 2;
    static constexpr double BASE_TO_SERVICE = 21 / 39;
    static constexpr double SIDE_TO_CENTRE = 1 / 2;

    // Factory functions
    static CourtLine createBaseLine(Line line);
    static CourtLine createServiceLine(Line line);
    static CourtLine createCentreServiceLine(Line line);
    static CourtLine createSideLine(Line line);
    static CourtLine createSinglesSideLine(Line line);
};

#endif //TENNISCOURT_COURTLINE_H
