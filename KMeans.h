//
// Created by misha on 07/12/15.
//

#include <opencv2/opencv.hpp>

#ifndef TENNISCOURT_KMEANS_H
#define TENNISCOURT_KMEANS_H

using namespace std;

class KMeans {
public:
    std::vector<cv::Point2f> run(
            std::vector<cv::Point2f> points,
            int k,
            int iterations,
            std::vector<cv::Point2f> means = std::vector<cv::Point2f>());
private:
    float applyRange(float x, float max, float min);
};

#endif //TENNISCOURT_KMEANS_H
