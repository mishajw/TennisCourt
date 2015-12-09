//
// Created by misha on 09/12/15.
//

#include <opencv2/opencv.hpp>
#include "Line.h"

#ifndef TENNISCOURT_LINEINDENTIFIER_H
#define TENNISCOURT_LINEINDENTIFIER_H

using namespace cv;

class LineDetector {
public:
    std::vector<Line> run(String imagePath, int imageWidth, int imageHeight);

private:
    bool usingSobel = false;
    double houghDegIncrements = CV_PI / 360.0;
    int houghThreshold = 180;
    int blurSize = 15;
    int sobelThreshold = 50;
    int cannyThreshold = 10;
    bool groupLines = true;
    int linesToFind = 10;

    std::vector<char> readByteFile(char const *fileName);

    Mat byteFileToImage(std::vector<char> bytes, int imageWidth, int imageHeight);

    Mat doNoiseRemoval(Mat original);

    Mat doEdgeDetectionSobel(Mat original);

    Mat doEdgeDetectionCanny(Mat original);

    std::vector<Line> doLineDetection(Mat original);

    Mat drawLines(Mat image, std::vector<Line> lines);

    std::vector<Vec2f> groupDetectedLines(std::vector<Vec2f> original);

    Line trimLine(double rho, double theta, Mat original);
};

#endif //TENNISCOURT_LINEINDENTIFIER_H
