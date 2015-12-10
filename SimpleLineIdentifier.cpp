//
// Created by misha on 10/12/15.
//

#include "SimpleLineIdentifier.h"

void SimpleLineIdentifier::run(vector<Line> lines, Mat image) {
    string HORIZONTAL_LABELS[] =
            {"service line", "baseline"};
    string VERTICAL_LABELS[] =
            {"sideline", "singles sideline", "centre service line", "singles sideline"/*, "sideline"*/};

    pair<vector<Line>, vector<Line>> grouped = groupLines(lines);
    vector<Line> horizontal = grouped.first, vertical = grouped.second;
    vector<double> horizontalMidpoints, verticalMidpoints;

    for (unsigned int i = 0; i < horizontal.size(); i++) {
        horizontalMidpoints.push_back(horizontal.at(i).getMidPoint().y);
    }

    for (unsigned int i = 0; i < vertical.size(); i++) {
        verticalMidpoints.push_back(vertical.at(i).getMidPoint().x);
    }

    vector<string> horizontalLabels = labelLines(horizontalMidpoints, HORIZONTAL_LABELS);
    vector<string> verticalLabels = labelLines(verticalMidpoints, VERTICAL_LABELS);

    Mat drawn = drawLines(image, lines, Scalar(255,0,0));

    for (unsigned int i = 0; i < horizontal.size(); i++) {
        putText(drawn,
                horizontalLabels.at(i),
                Point(i * 200, (int) horizontalMidpoints.at(i)),
                0,
                0.5,
                Scalar(0, 0, 255));
    }

    for (unsigned int i = 0; i < vertical.size(); i++) {
        putText(drawn,
                verticalLabels.at(i),
                Point((int) verticalMidpoints.at(i), 30 + i * 40),
                0,
                0.5,
                Scalar(0, 255, 0));
    }

    imshow("Labeled Lines", drawn);
    waitKey(0);
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

vector<string> SimpleLineIdentifier::labelLines(vector<double> midPoints, string labels[]) {
    double min = DBL_MAX, max = DBL_MIN;

    for (unsigned int i = 0; i < midPoints.size(); i ++) {
        double cur = midPoints.at(i);
        if (cur < min) min = cur;
        if (cur > max) max = cur;
    }

    vector<string> labeledLines;

    for (unsigned int i = 0; i < midPoints.size(); i ++) {
        labeledLines.push_back(
                labels[(int) round((midPoints.at(i) - min) / (max - min))]
        );
    }

    return labeledLines;
}
