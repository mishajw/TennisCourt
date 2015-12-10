//
// Created by misha on 09/12/15.
//

#ifndef TENNISCOURT_LINE_H
#define TENNISCOURT_LINE_H


#include <opencv2/opencv.hpp>

using namespace std;

class Line {
public:
    double x1, y1, x2, y2;

    Line(double x1, double y1, double x2, double y2);
    Line(cv::Point p1, cv::Point p2);

    double getLength();
    double getAngle();
    double intersectionPercentage(Line l);

    cv::Point getStart();
    cv::Point getEnd();

    cv::Point getMidPoint();

    std::string toString();

private:
    double getM();
    double getC();
    double getDistance(double x1, double y1, double x2, double y2);
};


#endif //TENNISCOURT_LINE_H
