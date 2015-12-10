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

double Line::getLength() {
    return getDistance(x1, y1, x2, y2);
}

double Line::getAngle() {
    return atan(getM());
}

double Line::intersectionPercentage(Line l) {
    double
        ourM = getM(),
        otherM = l.getM(),
        ourC = getC(),
        otherC = l.getC();

    double x = (otherC - ourC) / (ourM - otherM);
    double y = (ourM * x) + ourC;

    return getDistance(x1, y1, x, y) / getLength();
}

cv::Point Line::getStart() {
    return cv::Point((int) x1, (int) y1);
}

cv::Point Line::getEnd() {
    return cv::Point((int) x2, (int) y2);
}

double Line::getM() {
    return (y2 - y1) / (x2 - x1);
}

double Line::getC() {
    return y1 - (getM() * x1);
}

double Line::getDistance(double x1, double y1, double x2, double y2) {
    return sqrt(
            pow(x2 - x1, 2) +
            pow(y2 - y1, 2)
    );
}

cv::Point Line::getMidPoint() {
    return cv::Point((int) ((x1 + x2) / 2), (int) ((y1 + y2) / 2));
}

std::string Line::toString() {
    return "Line((" +
            to_string(x1) + "," + to_string(y1) + ") to (" +
            to_string(x2) + "," + to_string(y1) + "))";
}
