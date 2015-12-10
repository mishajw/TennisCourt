#include "LineDetector.h"

#include <fstream>
#include <bitset>
#include "SimpleLineIdentifier.h"
#include "CSVExporter.h"

using namespace std;

// Globals
String IMAGE_PATH = "/home/misha/Dropbox/hawkeye/tenniscourt/image.raw";
int IMAGE_WIDTH = 1392;
int IMAGE_HEIGHT = 550;

std::vector<char> readByteFile(const char* fileName);
Mat byteFileToImage(std::vector<char> bytes, int imageWidth, int imageHeight);

int main() {
//    Line l(1337, 300, 4, 284);
//    Line l(0, 100, 0, 200);
//    const Point &point_ = l.getPointOnLine(0.1);
//    printf("(%d, %d)", point_.x, point_.y);

    std::vector<char> fileBytes = readByteFile(IMAGE_PATH.c_str());
    Mat image = byteFileToImage(fileBytes, IMAGE_WIDTH, IMAGE_HEIGHT);

    if (!image.data) {
        printf("Couldn't load image");
        return -1;
    }

    LineDetector detector;
    vector<Line> lines = detector.run(image);

    SimpleLineIdentifier identifier;
    vector<pair<string, Line>> labeledLines = identifier.run(lines, image);

    CSVExporter exporter;
    exporter.run(labeledLines, "/home/misha/Dropbox/hawkeye/tenniscourt/detected-lines.csv");

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

Mat byteFileToImage(std::vector<char> bytes, int imageWidth, int imageHeight) {
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
