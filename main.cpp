#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <bitset>

#define IMAGE_WIDTH 1392
#define IMAGE_HEIGHT 550

using namespace cv;

std::vector<char> readByteFile(char const* fileName);
Mat byteFileToImage(std::vector<char> bytes);

int main() {
    std::vector<char> fileBytes = readByteFile("/home/misha/Dropbox/hawkeye/tenniscourt/image.raw");
    Mat image = byteFileToImage(fileBytes);

    if (!image.data) {
        printf("Couldn't load image");
        return -1;
    }

    imshow("Image", image);

    waitKey(0);

    return 0;
}

std::vector<char> readByteFile(char const* fileName) {
    std::ifstream ifs(fileName, std::ios::binary | std::ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();

    std::vector<char> result(pos);

    ifs.seekg(0, std::ios::beg);
    ifs.read(&result[0], pos);

    return result;
}

Mat byteFileToImage(std::vector<char> bytes) {
    // Create the image with one unsigned channel
    Mat image(IMAGE_WIDTH, IMAGE_HEIGHT, CV_8UC1);

    // For each pixel, write the bytes to the image
    for (int x = 0; x < image.rows; x ++) {
        for (int y = 0; y < image.cols; y ++) {
            int valInt = int(bytes.at((unsigned long) (y * image.rows + x)));
            uchar valUChar = (uchar) valInt;

            image.at<uchar>(x, y) = valUChar;
        }
    }

    return image;
}
