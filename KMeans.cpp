//
// Created by misha on 07/12/15.
//

#include "KMeans.h"

std::vector<cv::Point2f> KMeans::run(std::vector<cv::Point2f> points, int k, int iterations,
                                     std::vector<cv::Point2f> means) {

    float maxX = FLT_MIN, minX = FLT_MAX, maxY = FLT_MIN, minY = FLT_MAX;

    for (unsigned int i = 0; i < points.size(); i++) {
        cv::Point2f p = points.at(i);
        if (p.x > maxX) maxX = p.x;
        if (p.x < minX) minX = p.x;
        if (p.y > maxY) maxY = p.y;
        if (p.y < minY) minY = p.y;
    }

    struct cmpByStringLength {
        bool operator()(const cv::Point2f& a, const cv::Point2f& b) const {
            if (a.x != b.x) {
                return a.x > b.x;
            } else {
                return a.y > b.y;
            }
        }
    };

    int meansLacking = (int) (k - means.size());

    if (meansLacking > 0) {
        for (unsigned int i = 0; i < meansLacking; i ++) {
            means.push_back(points.at(i));
        }
    }

    if (meansLacking < 0 || iterations == 0) {
        return means;
    }

    std::map<cv::Point2f, std::vector<cv::Point2f>, cmpByStringLength> groups;

    // Make groups
    for (unsigned int i = 0; i < means.size(); i++) {
        std::vector<cv::Point2f> empty;
        groups[means.at(i)] = empty;
    }

    // Assign each point to closest group
    for (unsigned int i = 0; i < points.size(); i++) {
        cv::Point2f currentPoint = points.at(i), closest;
        double closestDist = DBL_MAX;

        for (unsigned int j = 0; j < means.size(); j++) {
            cv::Point2f currentMeans = means.at(j);
            double currentDist = sqrt(
                    pow(applyRange(currentMeans.x, maxX, minX) - applyRange(currentPoint.x, maxX, minX), 2) +
                    pow(applyRange(currentMeans.y, maxY, minY) - applyRange(currentPoint.y, maxY, minY), 2));

//            printf("CurDist: %f\n", currentDist);

            if (currentDist < closestDist) {
                closest = currentMeans;
                closestDist = currentDist;
            }
        }

        groups[closest].push_back(currentPoint);
    }

    // Get average of groups
    std::vector<cv::Point2f> newMeans;

    for (unsigned int i = 0; i < means.size(); i++) {
        std::vector<cv::Point2f> currentGroup = groups[means.at(i)];

        if (currentGroup.size() == 0) {
            newMeans.push_back(means.at(i));
            continue;
        }

        float avgX = 0, avgY = 0;

        for (unsigned int j = 0; j < currentGroup.size(); j++) {
            avgX += currentGroup.at(j).x;
            avgY += currentGroup.at(j).y;
        }

        avgX /= currentGroup.size();
        avgY /= currentGroup.size();

        newMeans.push_back(cv::Point2f(avgX, avgY));
    }

    return run(points, k, iterations - 1, newMeans);
}

float KMeans::applyRange(float x, float max, float min) {
    return (x - min) / (max - min);
}
