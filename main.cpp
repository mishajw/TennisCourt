#include "LineDetector.h"
#include "LineIdentifier.h"

using namespace std;

// Globals
String IMAGE_PATH = "/home/misha/Dropbox/hawkeye/tenniscourt/image.raw";
int IMAGE_WIDTH = 1392;
int IMAGE_HEIGHT = 550;

int main() {
    LineDetector detector;
    vector<pair<Point, Point>> lines = detector.run(IMAGE_PATH, IMAGE_WIDTH, IMAGE_HEIGHT);

    LineIdentifier identifier;
    identifier.run(lines);

    return 0;
}