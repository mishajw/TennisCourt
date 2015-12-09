//
// Created by misha on 09/12/15.
//

#include "Line.h"

Line::Line(double x1, double y1, double x2, double y2) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}

Line::Line(cv::Point p1, cv::Point p2) {
    this->x1 = p1.x;
    this->y1 = p1.y;
    this->x2 = p2.x;
    this->y2 = p2.y;
}

double Line::getAngle() {
    return atan(y2 - y1 / x2 - x1);
}

double Line::intersectionPercentage(Line l) {
    return 0;
}

cv::Point Line::getStart() {
    return cv::Point((int) x1, (int) y1);
}

cv::Point Line::getEnd() {
    return cv::Point((int) x2, (int) y2);
}
