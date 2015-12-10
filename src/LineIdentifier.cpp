//
// Created by misha on 09/12/15.
//

#include "LineIdentifier.h"

void LineIdentifier::run(std::vector<Line> lines, Mat image) {
//    for (unsigned int i = 0; i < lines.size(); i++) {
//        Line currLine = lines.at(i);
//        vector<CourtLine> possibleLines = CourtLine::createAllLines(currLine);
//        printLinePossibilities(currLine, possibleLines, lines);
//    }

    vector<CourtLine> possibleLines = CourtLine::createAllLines();

    string actual[] = {"service",
                       "service",
                       "base",
                       "centre service",
                       "base",
                       "",
                       "singles side",
                       "base",
                       "singles side",
                       "side"};

    for (unsigned int i = 0; i < lines.size(); i++) {
        CourtLine currLine(lines.at(i), lines);
        printf("\n=== LINE %s, expects %s ===\n", currLine.line.toString().c_str(), actual[i].c_str());
        for (unsigned int j = 0; j < possibleLines.size(); j++) {
            CourtLine currPossibleLine = possibleLines.at(j);
            printf("Comparing with %s: %f\n",
                   currPossibleLine.name,
                   currLine.compareWith(&currPossibleLine));
        }
    }



//    for (unsigned int i = 0; i < lines.size(); i ++) {
//        vector<Line> lines2;
//        lines2.push_back(lines.at(i));
//        Mat drawn = drawLines(image, lines2);
//        imshow("Drawn", drawn);
//        waitKey(0);
//    }

    Mat drawn = drawLines(image, lines);
    imshow("Drawn", drawn);

}

Mat LineIdentifier::drawLines(Mat image, std::vector<Line> lines) {
    Mat drawnImage;
    cvtColor(image, drawnImage, CV_GRAY2RGB);

    for(unsigned int i = 0; i < lines.size(); i++) {
        line(drawnImage,
             lines.at(i).getStart(),
             lines.at(i).getEnd(),
             Scalar(0, 0, 255), 3, CV_AA);
    }

    return drawnImage;
}
