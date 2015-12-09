//
// Created by misha on 09/12/15.
//

#include "LineDetector.h"
#include <fstream>
#include <bitset>
#include "KMeans.h"

std::vector<std::pair<Point, Point>> LineDetector::identifyLines(String imagePath, int imageWidth, int imageHeight) {
    std::vector<char> fileBytes = readByteFile(imagePath.c_str());
    Mat image = byteFileToImage(fileBytes, imageWidth, imageHeight);

    if (!image.data) {
        printf("Couldn't load image");
        return std::vector<std::pair<Point, Point>>();
    }

    Mat noiseRemoved = doNoiseRemoval(image);

    Mat edgeDetected;
    if (usingSobel) {
        edgeDetected = doEdgeDetectionSobel(noiseRemoved);
    } else {
        edgeDetected = doEdgeDetectionCanny(noiseRemoved);
    }

    std::vector<std::pair<Point, Point>> lines = doLineDetection(edgeDetected);

    Mat lineDetected = drawLines(image, lines);

    imwrite("/home/misha/Dropbox/hawkeye/tenniscourt/output.png", lineDetected);
    imshow("Image", lineDetected);
    waitKey(0);

    return lines;
}

std::vector<char> LineDetector::readByteFile(const char* fileName) {
    std::ifstream ifs(fileName, std::ios::binary | std::ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();

    std::vector<char> result((unsigned long) pos);

    ifs.seekg(0, std::ios::beg);
    ifs.read(&result[0], pos);

    return result;
}

Mat LineDetector::byteFileToImage(std::vector<char> bytes, int imageWidth, int imageHeight) {
    // Create the image with one unsigned channel
    Mat image(imageHeight, imageWidth, CV_8UC1);

    // For each pixel, write the bytes to the image
    for (int x = 0; x < image.cols; x ++) {
        for (int y = 0; y < image.rows; y ++) {
            uchar byte = (uchar) bytes.at((unsigned long) (y * image.cols + x));
            image.at<uchar>(y, x) = byte;
        }
    }

    return image;
}

Mat LineDetector::doNoiseRemoval (Mat original) {
    Mat blurred;
    GaussianBlur(original, blurred, Size(blurSize, blurSize), 0, 0);
    return blurred;
}

Mat LineDetector::doEdgeDetectionSobel(Mat original) {
    Mat edgeDetected, gradX, gradY, absGradX, absGradY, thresholded, converted;

    Sobel(original, gradX, CV_8UC1, 1, 0, 3, 1, BORDER_DEFAULT);
    Sobel(original, gradY, CV_8UC1, 0, 1, 3, 1, BORDER_DEFAULT);
    convertScaleAbs(gradX, absGradX);
    convertScaleAbs(gradY, absGradY);

    // Weight Y more, because of thinner lines due to camera angle
    addWeighted(absGradX, 0.5, absGradY, 1, 0, edgeDetected);

    threshold(edgeDetected, thresholded, sobelThreshold, 255, CV_THRESH_BINARY);
    thresholded.convertTo(converted, CV_8UC1);

    return converted;
}

Mat LineDetector::doEdgeDetectionCanny(Mat original) {
    Mat edgeDetected;
    Canny(original, edgeDetected, cannyThreshold, cannyThreshold * 3, 3);
    return edgeDetected;
}

vector<pair<Point, Point>> LineDetector::doLineDetection(Mat original) {
    std::vector<Vec2f> lines;
    std::vector<std::pair<Point, Point>> trimmedLines;

    // Perform Hough transform
    HoughLines(original, lines, 1, houghDegIncrements, houghThreshold);

    // Group the lines together
    if (groupLines) {
        lines = groupDetectedLines(lines);
    }

    // Trim the lines
    for(size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0], theta = lines[i][1];
        trimmedLines.push_back(trimLine(rho, theta, original));
    }

    return trimmedLines;
}

Mat LineDetector::drawLines(Mat image, std::vector<std::pair<Point, Point>> lines) {
    Mat drawnImage;
    cvtColor(image, drawnImage, CV_GRAY2RGB);

    for(unsigned int i = 0; i < lines.size(); i++) {
        line(drawnImage,
             std::get<0>(lines.at(i)),
             std::get<1>(lines.at(i)),
             Scalar(0, 0, 255), 3, CV_AA);
    }

    return drawnImage;
}

std::vector<Vec2f> LineDetector::groupDetectedLines(std::vector<Vec2f> original) {
    std::vector<Point2f> originalPoints, groupedPoints;

    for (unsigned int i = 0; i < original.size(); i ++) {
        originalPoints.push_back(Point2f(original.at(i)[0], original.at(i)[1]));
    }

    KMeans km;
    groupedPoints = km.run(originalPoints, linesToFind, 10000);

    std::vector<Vec2f> groupedLines;

    for (unsigned int i = 0; i < groupedPoints.size(); i ++) {
        groupedLines.push_back(Vec2f(groupedPoints.at(i).x, groupedPoints.at(i).y));
    }

    return groupedLines;
}

std::pair<Point, Point> LineDetector::trimLine(double rho, double theta, Mat original) {
    Mat image;
    original.convertTo(image, CV_8UC1);
//    imshow("test", image);
//    waitKey(0);

    Point pt1, pt2;
    double a = cos(theta), b = sin(theta);
    double x0 = a*rho, y0 = b*rho;

    if (b == 0) {
        b += 0.1;
    }

    double nRight = x0 / b;
    double nLeft = (x0 - image.cols) / b;
    double nLeftTrimmed = nRight, nRightTrimmed = nLeft;

    for (double i = nLeft; i < nRight; i += 0.1){
        int curX = cvRound(x0 + i * (-b)),
                curY = cvRound(y0 + i * (a));

        if (curX < 0 || curX >= image.cols || curY < 0 || curY > image.rows) {
            continue;
        }

        uchar pixel = image.at<uchar>(curY, curX);

        if (pixel != 0) {
            if (i < nLeftTrimmed) {
                nLeftTrimmed = i;
            }
            if (i > nRightTrimmed) {
                nRightTrimmed = i;
            }
        }
    }

    pt1.x = cvRound(x0 + nLeftTrimmed * (-b));
    pt1.y = cvRound(y0 + nLeftTrimmed * (a));
    pt2.x = cvRound(x0 + nRightTrimmed * (-b));
    pt2.y = cvRound(y0 + nRightTrimmed * (a));

    return std::pair<Point, Point>(pt1, pt2);
}