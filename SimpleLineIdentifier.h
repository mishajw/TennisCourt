//
// Created by misha on 10/12/15.
//

#ifndef TENNISCOURT_SIMPLELINEIDENTIFIER_H
#define TENNISCOURT_SIMPLELINEIDENTIFIER_H


#include "Line.h"

using namespace cv;

class SimpleLineIdentifier {
public:
    void run(vector<Line> lines, Mat image);

private:
    struct LineDetail {
        string name;
        double relativePosition;
    };

    static constexpr double ZERO_ANG = 0;

    pair<vector<Line>, vector<Line>> groupLines(vector<Line> lines);
    Mat drawLines(Mat image, std::vector<Line> lines, Scalar color);
    vector<string> labelLines(vector<double> midPoints, vector<LineDetail> labels);

    vector<LineDetail> getPossibleHorizontals();
    vector<LineDetail> getPossibleVerticals();
};


#endif //TENNISCOURT_SIMPLELINEIDENTIFIER_H
