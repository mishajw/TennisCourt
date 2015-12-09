#include <opencv2/opencv.hpp>
#include "LineIndentifier.h"

using namespace cv;

// Globals
String IMAGE_PATH = "/home/misha/Dropbox/hawkeye/tenniscourt/image.raw";
int IMAGE_WIDTH = 1392;
int IMAGE_HEIGHT = 550;

// Function headers


int main() {
    LineIdentifier li;
    li.identifyLines(IMAGE_PATH, IMAGE_WIDTH, IMAGE_HEIGHT);

    return 0;
}