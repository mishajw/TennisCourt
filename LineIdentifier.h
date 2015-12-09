//
// Created by misha on 09/12/15.
//

#include <opencv2/opencv.hpp>

#ifndef TENNISCOURT_LINEIDENTIFIER_H
#define TENNISCOURT_LINEIDENTIFIER_H

using namespace cv;

class LineIdentifier {
public:
    void run(std::vector<std::pair<Point, Point>> lines);
};


#endif //TENNISCOURT_LINEIDENTIFIER_H
