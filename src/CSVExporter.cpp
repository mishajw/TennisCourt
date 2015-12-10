//
// Created by misha on 10/12/15.
//

#include "CSVExporter.h"
#include <fstream>

void CSVExporter::run(vector<pair<string, Line>> labeledLines, string path) {
    string content = "Line name, Start, End, Points\n";

    for (unsigned int i = 0; i < labeledLines.size(); i ++) {
        content += labeledLineToString(labeledLines.at(i));
        content += "\n";
    }

    writeStringToFile(content, path);
}

string CSVExporter::labeledLineToString(pair<string, Line> labeledLine) {
    string label = labeledLine.first;
    Line line = labeledLine.second;
    string content = label + "," +
            to_string(line.x1) + ":" + to_string(line.y1) + "," +
            to_string(line.x2) + ":" + to_string(line.y2 );

    vector<cv::Point> pointsOnLine = getPointsOnLine(line, 5);

    for (unsigned int i = 0; i < pointsOnLine.size(); i++) {
        content += "(" +
                to_string(pointsOnLine.at(i).x) + ":" +
                to_string(pointsOnLine.at(i).y) + "),";
    }

    return content;
}

vector<cv::Point> CSVExporter::getPointsOnLine(Line line, double amount) {
    vector<cv::Point> points;

    for (double i = 0; i <= 1; i += amount / line.getLength()) {
        points.push_back(line.getPointOnLine(i));
    }

    return points;
}

void CSVExporter::writeStringToFile(string content, string path) {
    ofstream output;
    output.open(path);
    output << content;
    output.close();
}
