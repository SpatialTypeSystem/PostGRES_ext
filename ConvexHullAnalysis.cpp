#include <iostream>
#include <vector>
#include <utility>

#include "include/ConvexHull/DivideAndConquer.h"

int main(void) {
    std::vector < std::pair < double, double > > points;
    points.push_back(std::make_pair(3, 0));
    points.push_back(std::make_pair(0, 1));
    points.push_back(std::make_pair(1, 2));
    points.push_back(std::make_pair(6, 2));
    points.push_back(std::make_pair(4, 3));
    points.push_back(std::make_pair(0, 4));
    points.push_back(std::make_pair(2, 5));
    points.push_back(std::make_pair(5, 5));

    std::vector < std::pair < double, double > > convexHull = getConvexHullDivideAndConquer(points);
    std::cout << "Convex hull: ";
    printPoints(convexHull);

    return 0;
}