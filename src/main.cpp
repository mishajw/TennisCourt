#include "LineDetector.h"

#include <fstream>
#include <bitset>
#include "SimpleLineIdentifier.h"
#include "CSVExporter.h"

using namespace std;

// Function headers
std::vector<char> readByteFile(const char* fileName);
Mat byteFileToImage(std::vector<char> bytes, int imageWidth, int imageHeight);

int main(int argc, char* argv[]) {
    string imagePath, exportPath;
    int imageWidth, imageHeight;

    if (argc != 5) {
        printf("To pass in: image location, export path, image width, image height.\n");
        imagePath = "/home/misha/Dropbox/hawkeye/tenniscourt/res/image.raw";
        exportPath = "/home/misha/Dropbox/hawkeye/tenniscourt/out/";
        imageWidth = 1392;
        imageHeight = 550;
    } else {
        imagePath = argv[1];
        exportPath = argv[2];
        imageWidth = atoi(argv[3]);
        imageHeight = atoi(argv[4]);
    }

    std::vector<char> fileBytes = readByteFile(imagePath.c_str());
    Mat image = byteFileToImage(fileBytes, imageWidth, imageHeight);

    if (!image.data) {
        printf("Couldn't load image");
        return -1;
    }

    LineDetector detector;
    vector<Line> lines = detector.run(image, exportPath);

    SimpleLineIdentifier identifier;
    vector<pair<string, Line>> labeledLines = identifier.run(lines, image, exportPath);

    CSVExporter exporter;
    exporter.run(labeledLines, exportPath + "/detected-lines.csv");

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
