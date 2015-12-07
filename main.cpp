#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <bitset>

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

int main() {
    std::vector<char> fileBytes = readByteFile("/home/misha/Dropbox/hawkeye/tenniscourt/image.raw");
    Mat image = byteFileToImage(fileBytes);

    if (!image.data) {
        printf("Couldn't load image");
        return -1;
    }

    Mat noiseRemoved, edgeDetected, lineDetected;
    noiseRemoved = doNoiseRemoval(image);
    edgeDetected = doEdgeDetection(noiseRemoved);
    lineDetected = doHoughTransform(edgeDetected);

    imshow("Image", lineDetected);
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
    GaussianBlur(original, blurred, Size(15, 15), 0, 0);
    return blurred;
}

Mat doEdgeDetection (Mat original) {
    Mat edgeDetected;
    Canny(original, edgeDetected, 50, 150, 3);
    return edgeDetected;
}

Mat doHoughTransform (Mat original) {
    Mat image;
    cvtColor(original, image, CV_GRAY2RGB);

    std::vector<Vec2f> lines;
    HoughLines(original, lines, 1, CV_PI/180, 140);

    printf("%d\n", (int) lines.size());

    for(size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));

        printf("(%d, %d) to (%d, %d)\n", pt1.x, pt1.y, pt2.x, pt2.y);

        line(image, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
    }

    return image;
}
