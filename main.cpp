#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <bitset>
#include "KMeans.h"

using namespace cv;

// Globals
int IMAGE_WIDTH = 1392;
int IMAGE_HEIGHT = 550;

// Function headers
std::vector<char>   readByteFile        (char const* fileName);
Mat                 byteFileToImage     (std::vector<char> bytes);
Mat                 doNoiseRemoval      (Mat original);
Mat                 doEdgeDetection     (Mat original);
Mat                 doHoughTransform    (Mat original);
std::vector<Vec2f>  groupDetectedLines  (std::vector<Vec2f> original);

int main() {
    /*std::vector<cv::Point2f> test, result;
    test.push_back(Point2f(0, 0));
    test.push_back(Point2f(0, 1));
    test.push_back(Point2f(1, 0));
    test.push_back(Point2f(3, 3));
    test.push_back(Point2f(4, 3));
    test.push_back(Point2f(3, 4));

    KMeans km;
    result = km.run(test, 2, 4);

    for (unsigned int i = 0; i < result.size(); i ++) {
        printf("%f, %f\n", reqsult.at(i).x, result.at(i).y);
    }*/


    std::vector<char> fileBytes = readByteFile("/home/misha/Dropbox/hawkeye/tenniscourt/image.raw");
    Mat image = byteFileToImage(fileBytes);

    if (!image.data) {
        printf("Couldn't load image");
        return -1;
    }


    Mat noiseRemoved = doNoiseRemoval(image);
    Mat edgeDetected = doEdgeDetection(noiseRemoved);
    Mat lineDetected = doHoughTransform(edgeDetected);

    imshow("Image", edgeDetected);
    waitKey(0);

    return 0;
}

std::vector<char> readByteFile(const char* fileName) {
    std::ifstream ifs(fileName, std::ios::binary | std::ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();

    std::vector<char> result((unsigned long) pos);

    ifs.seekg(0, std::ios::beg);
    ifs.read(&result[0], pos);

    return result;
}

Mat byteFileToImage(std::vector<char> bytes) {
    // Create the image with one unsigned channel
    Mat image(IMAGE_HEIGHT, IMAGE_WIDTH, CV_8UC1);

    // For each pixel, write the bytes to the image
    for (int x = 0; x < image.cols; x ++) {
        for (int y = 0; y < image.rows; y ++) {
            uchar byte = (uchar) bytes.at((unsigned long) (y * image.cols + x));
            image.at<uchar>(y, x) = byte;
        }
    }

    return image;
}

Mat doNoiseRemoval (Mat original) {
    Mat blurred;
    GaussianBlur(original, blurred, Size(9, 9), 0, 0);
    return blurred;
}

Mat doEdgeDetection (Mat original) {
    Mat edgeDetected, gradX, gradY, absGradX, absGradY, thresholded;

    Sobel(original, gradX, CV_16UC1, 1, 0, 3, 1, BORDER_DEFAULT);
    Sobel(original, gradY, CV_16UC1, 0, 1, 3, 1, BORDER_DEFAULT);
    convertScaleAbs(gradX, absGradX);
    convertScaleAbs(gradY, absGradY);

    addWeighted(absGradX, 0.5, absGradY, 1, 0, edgeDetected);

    threshold(edgeDetected, thresholded, 50, 255, CV_THRESH_BINARY);

    return thresholded;
}

Mat doHoughTransform(Mat original) {
    Mat image;
    cvtColor(original, image, CV_GRAY2RGB);

    std::vector<Vec2f> lines, groupedLines;
    HoughLines(original, lines, 1, CV_PI/180
            , 250);
//    groupedLines = groupDetectedLines(lines);
//    lines = groupedLines;

    for(size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0], theta = lines[i][1];
        printf("%f, %f\n", rho, theta);
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 2000*(-b));
        pt1.y = cvRound(y0 + 2000*(a));
        pt2.x = cvRound(x0 - 2000*(-b));
        pt2.y = cvRound(y0 - 2000*(a));

        line(image, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
    }

    return image;
}

std::vector<Vec2f> groupDetectedLines (std::vector<Vec2f> original) {
    std::vector<Point2f> originalPoints, groupedPoints;

    for (unsigned int i = 0; i < original.size(); i ++) {
        originalPoints.push_back(Point2f(original.at(i)[0], original.at(i)[1]));
    }

    KMeans km;
    groupedPoints = km.run(originalPoints, 10, 10000);

    std::vector<Vec2f> groupedLines;

    for (unsigned int i = 0; i < groupedPoints.size(); i ++) {
        groupedLines.push_back(Vec2f(groupedPoints.at(i).x, groupedPoints.at(i).y));
    }

    return groupedLines;
}
