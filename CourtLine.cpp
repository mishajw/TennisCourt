//
// Created by misha on 09/12/15.
//

#include "CourtLine.h"

CourtLine::CourtLine(Line _line, vector<Line> otherLines):
    line(_line), name(_line.toString().c_str()){
    initNeighboursWithLines(otherLines);
}

CourtLine::CourtLine(const char* _name, vector<double> _neighbours)
        : line(Line(0,0,0,0)), name(_name), neighbours(_neighbours) {}

CourtLine::CourtLine(const char* _name, double *_neighbours, int neighbourSize)
        : line(Line(0,0,0,0)), name(_name) {
    vector<double> n;

    for (unsigned int i = 0; i < neighbourSize; i++) {
        n.push_back(_neighbours[i]);
    }

    this->neighbours = n;
}

void CourtLine::initNeighboursWithLines(vector<Line> lines) {
    for (unsigned int j = 0; j < lines.size(); j++) {
        Line currLine = lines.at(j);

        if (!isRightAngle(currLine)) {
            continue;
        }

//        printf("Found right angle!\n");

        double intersection = line.intersectionPercentage(currLine);

//        printf("Intersection: %f ->", intersection);

        neighbours.push_back(intersection);
    }
}

bool CourtLine::isRightAngle(Line l) {
    double ourAngle = this->line.getAngle();
    double currAngle = l.getAngle();

    // Calculate the angle between these two lines, but keep within 180deg, as we're
    // only checking for right angles.
    double difference = fmod(abs(ourAngle - currAngle), CV_PI);

    bool rightAngle = abs(difference - (CV_PI / 2)) < ACCURACY_ANGLES;

//    printf("%f, %f -> %f -> %d\n", ourAngle, currAngle, difference, rightAngle);

    return rightAngle;
}

double CourtLine::compareWith(CourtLine *otherLine) {
    double total = 0;

    if (neighbours.size() == 0) {
        return 0;
    }

    for (unsigned int i = 0; i < neighbours.size(); i ++) {
        double bestMatch = 1;

        for (unsigned int j = 0; j < otherLine->neighbours.size(); j ++) {
            double diff = abs(neighbours.at(i) - otherLine->neighbours.at(j));

            if (diff < bestMatch) {
                bestMatch = diff;
            }
        }

        total += bestMatch;
    }

    return total / neighbours.size();
}

// Factory functions

CourtLine CourtLine::createBaseLine() {
    double neighbours[] = {0.0, SIDE_TO_SINGLES, 1.0 - SIDE_TO_SINGLES, 1.0};
    return CourtLine("base", neighbours, 4);
}

CourtLine CourtLine::createServiceLine() {
    double neighbours[] = {0.0, 0.5, 1.0};
    return CourtLine("service", neighbours, 3);
}

CourtLine CourtLine::createCentreServiceLine() {
    double neighbours[] = {0.0, 1.0};
    return CourtLine("centre service", neighbours, 2);
}

CourtLine CourtLine::createSideLine() {
    double neighbours[] = {0.0, 1.0};
    return CourtLine("side", neighbours, 2);
}

CourtLine CourtLine::createSinglesSideLine() {
    double neighbours[] = {BASE_TO_SERVICE, 1.0};
    return CourtLine("singles side", neighbours, 3);
}

vector<CourtLine> CourtLine::createAllLines() {
    vector<CourtLine> lines;

    lines.push_back(createBaseLine());
    lines.push_back(createServiceLine());
    lines.push_back(createCentreServiceLine());
    lines.push_back(createSideLine());
    lines.push_back(createSinglesSideLine());

    return lines;
}
