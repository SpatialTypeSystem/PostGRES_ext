#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

#include "include/ConvexHull/DivideAndConquer.h"

void runConvexHullAlgorithm(std::vector < std::pair < double, double > > (*algorithmFunction)(std::vector < std::pair < double, double > >&), std::string algorithmName, std::vector < std::pair < double, double > > points);

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

    runConvexHullAlgorithm(getConvexHullDivideAndConquer, "DivideAndConquer", points);

    return 0;
}

void runConvexHullAlgorithm(std::vector < std::pair < double, double > > (*algorithmFunction)(std::vector < std::pair < double, double > >&), std::string algorithmName, std::vector < std::pair < double, double > > points) {
    std::cout << "Algorithm: " << algorithmName << std::endl;

    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    std::vector < std::pair < double, double > > convexHull = (*algorithmFunction)(points);
    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast< std::chrono::microseconds >(endTime - startTime).count();
    std::cout << "Time taken: " << duration << " (microseconds)" << std::endl;

    std::cout << "Convex hull: ";
    printPoints(convexHull);
}