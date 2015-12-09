#include "LineDetector.h"

using namespace std;

// Globals
String IMAGE_PATH = "/home/misha/Dropbox/hawkeye/tenniscourt/image.raw";
int IMAGE_WIDTH = 1392;
int IMAGE_HEIGHT = 550;

int main() {
    LineDetector li;
    vector<pair<Point, Point>> lines = li.identifyLines(IMAGE_PATH, IMAGE_WIDTH, IMAGE_HEIGHT);

    return 0;
}