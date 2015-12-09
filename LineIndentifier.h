//
// Created by misha on 09/12/15.
//

#include <opencv2/opencv.hpp>

#ifndef TENNISCOURT_LINEINDENTIFIER_H
#define TENNISCOURT_LINEINDENTIFIER_H

using namespace cv;

class LineIdentifier {
public:
    void identifyLines(String imagePath, int imageWidth, int imageHeight);
private:
    std::vector<char>   readByteFile        (char const* fileName);
    Mat                 byteFileToImage     (std::vector<char> bytes, int imageWidth, int imageHeight);
    Mat                 doNoiseRemoval      (Mat original);
    Mat                 doEdgeDetectionSobel(Mat original);
    Mat                 doEdgeDetectionCanny(Mat original);
    Mat                 doLineDetection     (Mat original);
    std::vector<Vec2f>  groupDetectedLines  (std::vector<Vec2f> original);
    std::pair<Point, Point> trimLine        (double rho, double theta, Mat original);
};

#endif //TENNISCOURT_LINEINDENTIFIER_H
