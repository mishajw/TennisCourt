//
// Created by misha on 09/12/15.
//

#include <opencv2/opencv.hpp>
#include "CourtLine.h"

#ifndef TENNISCOURT_LINEIDENTIFIER_H
#define TENNISCOURT_LINEIDENTIFIER_H

using namespace cv;

class LineIdentifier {
public:
    void run(std::vector<Line> lines, Mat image);

private:
    std::vector<CourtLine> possibleLines;
    void printLinePossibilities(Line line, vector<CourtLine> possibilities, vector<Line> lines);
    Mat drawLines(Mat image, std::vector<Line> lines);
};

#endif //TENNISCOURT_LINEIDENTIFIER_H
