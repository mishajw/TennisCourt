//
// Created by misha on 09/12/15.
//

#include "CourtLine.h"

CourtLine::CourtLine(Line _line, string _name, double _neighbours[])
        : line(_line), name(_name), neighbours(_neighbours) {}

map<Line, CourtLine> CourtLine::parsePossibleNeighbours(vector<Line> lines) {
    for (unsigned int i = 0; i < lines.size(); i ++) {
        Line currLine = lines.at(i);
        bool rightAngle = isRightAngle(currLine);
        double intersection = line.intersectionPercentage(currLine);
    }

    return map<Line, CourtLine>();
}

bool CourtLine::isRightAngle(Line l) {
    double ourAngle = this->line.getAngle();
    double currAngle = l.getAngle();
    // Calculate the angle between these two lines, but keep within 180deg, as we're
    // only checking for right angles.
    double difference = fmod(abs(ourAngle - currAngle), CV_PI);

    return abs(difference - 90) < ACCURACY_ANGLES;
}

// Factory functions

CourtLine CourtLine::createBaseLine(Line line) {
    double neighbours[] = {0.0, SIDE_TO_SINGLES, 1.0 - SIDE_TO_SINGLES, 1.0};
    return CourtLine(line, "base", neighbours);
}

CourtLine CourtLine::createServiceLine(Line line) {
    double neighbours[] = {0.0, 0.5, 1.0};
    return CourtLine(line, "service", neighbours);
}

CourtLine CourtLine::createCentreServiceLine(Line line) {
    double neighbours[] = {0.0, 1.0};
    return CourtLine(line, "centre service", neighbours);
}

CourtLine CourtLine::createSideLine(Line line) {
    double neighbours[] = {0.0, 1.0};
    return CourtLine(line, "side", neighbours);
}

CourtLine CourtLine::createSinglesSideLine(Line line) {
    double neighbours[] = {0.0, BASE_TO_SERVICE, 1.0};
    return CourtLine(line, "singles side", neighbours);
}

vector<CourtLine> CourtLine::createAllLines(Line line) {
    vector<CourtLine> lines;

    lines.push_back(createBaseLine(line));
    lines.push_back(createServiceLine(line));
    lines.push_back(createCentreServiceLine(line));
    lines.push_back(createSideLine(line));
    lines.push_back(createSinglesSideLine(line));

    return lines;
}
