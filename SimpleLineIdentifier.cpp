//
// Created by misha on 10/12/15.
//

#include "SimpleLineIdentifier.h"

vector<pair<string, Line>> SimpleLineIdentifier::run(vector<Line> lines, Mat image) {
    vector<string> horizontalPossible;
    horizontalPossible.push_back("service line");
    horizontalPossible.push_back("base line");

    vector<string> verticalPossible;
    verticalPossible.push_back("sideline");
    verticalPossible.push_back("singles sideline");
    verticalPossible.push_back("centre service line");
    verticalPossible.push_back("singles sideline");

    pair<vector<Line>, vector<Line>> grouped = groupLines(lines);
    vector<Line> horizontal = grouped.first, vertical = grouped.second;
    vector<double> horizontalMidpoints, verticalMidpoints;

    for (unsigned int i = 0; i < horizontal.size(); i++) {
        horizontalMidpoints.push_back(horizontal.at(i).getMidPoint().y);
    }

    for (unsigned int i = 0; i < vertical.size(); i++) {
        verticalMidpoints.push_back(vertical.at(i).getMidPoint().x);
    }

    vector<string> horizontalLabels = labelLines(horizontalMidpoints, getPossibleHorizontals());
    vector<string> verticalLabels = labelLines(verticalMidpoints, getPossibleVerticals());

    vector<pair<string, Line>> labeledLines;



    Mat drawn = drawLines(image, lines, Scalar(255,0,0));

    for (unsigned int i = 0; i < horizontal.size(); i++) {
        string label = horizontalLabels.at(i);
        putText(drawn,
                label,
                Point(i * 200, (int) horizontalMidpoints.at(i)),
                0,
                0.5,
                Scalar(0, 0, 255));

        labeledLines.push_back(pair<string, Line>(label, horizontal.at(i)));
    }

    for (unsigned int i = 0; i < vertical.size(); i++) {
        string label = verticalLabels.at(i);

        putText(drawn,
                label,
                Point((int) verticalMidpoints.at(i), 30 + i * 40),
                0,
                0.5,
                Scalar(0, 255, 0));

        labeledLines.push_back(pair<string, Line>(label, horizontal.at(i)));
    }

    imshow("Labeled Lines", drawn);
    waitKey(0);

    return labeledLines;
}

pair<vector<Line>, vector<Line>> SimpleLineIdentifier::groupLines(vector<Line> lines) {
    vector<Line> horizontal, vertical;

    for (unsigned int i = 0; i < lines.size(); i ++) {
        Line curLine = lines.at(i);

        double curAngle = fmod(abs(curLine.getAngle() - ZERO_ANG), CV_PI / 2);

        if (curAngle > CV_PI / 4) {
            vertical.push_back(curLine);
        } else {
            horizontal.push_back(curLine);
        }
    }

    return pair<vector<Line>, vector<Line>>(horizontal, vertical);
}

Mat SimpleLineIdentifier::drawLines(Mat image, std::vector<Line> lines, Scalar color) {
    Mat drawnImage;
    cvtColor(image, drawnImage, CV_GRAY2RGB);

    for(unsigned int i = 0; i < lines.size(); i++) {
        line(drawnImage,
             lines.at(i).getStart(),
             lines.at(i).getEnd(),
             color, 3, CV_AA);
    }

    return drawnImage;
}

vector<string> SimpleLineIdentifier::labelLines(vector<double> midPoints, vector<LineDetail> labels) {
    double min = DBL_MAX, max = DBL_MIN;

    for (unsigned int i = 0; i < midPoints.size(); i ++) {
        double cur = midPoints.at(i);
        if (cur < min) min = cur;
        if (cur > max) max = cur;
    }

    vector<string> labeledLines;

    for (unsigned int i = 0; i < midPoints.size(); i ++) {
        double relative = (midPoints.at(i) - min) / (max - min);

        LineDetail closest = labels.at(0);
        for (unsigned int j = 1; j < labels.size(); j ++) {
            if (abs(relative - labels.at(j).relativePosition) <
                    abs(relative - closest.relativePosition)) {
                closest = labels.at(j);
            }
        }

        labeledLines.push_back(closest.name);
    }

    return labeledLines;
}

vector<SimpleLineIdentifier::LineDetail> SimpleLineIdentifier::getPossibleHorizontals() {
    LineDetail baseline;
    baseline.name = "base line";
    baseline.relativePosition = 1;

    LineDetail service;
    service.name = "service line";
    service.relativePosition = 0;

    vector<LineDetail> possibles;
    possibles.push_back(baseline);
    possibles.push_back(service);

    return possibles;
}

vector<SimpleLineIdentifier::LineDetail> SimpleLineIdentifier::getPossibleVerticals() {
//    LineDetail sideline;
//    sideline.name = "sideline";
//    sideline.relativePosition = 0;

    LineDetail singles;
    singles.name = "singles sideline";
    singles.relativePosition = (27.0 / 36.0) / 2.0;

    LineDetail service;
    service.name = "centre service line";
    service.relativePosition = 0.5;

    LineDetail singles2;
    singles2.name = "singles sideline";
    singles2.relativePosition = 0.9; // 1.0 - (27.0 / 36.0) / 2.0;

    LineDetail sideline2;
    sideline2.name = "sideline";
    sideline2.relativePosition = 1;

    vector<LineDetail> possibles;
//    possibles.push_back(sideline);
    possibles.push_back(singles);
    possibles.push_back(service);
    possibles.push_back(singles2);
    possibles.push_back(sideline2);

    return possibles;
}
