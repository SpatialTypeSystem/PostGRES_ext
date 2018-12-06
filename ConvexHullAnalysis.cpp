// TODO: verify that vectors are not copied unnecesssarily
// TODO: simplify the make steps

#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

#include "include/Number.h"
#include "include/RGPPoint2D.h"
#include "include/ConvexHull/Chans.h"
#include "include/ConvexHull/DivideAndConquer.h"
#include "include/ConvexHull/GrahamScan.h"
#include "include/ConvexHull/MonotoneChain.h"
#include "include/ConvexHull/JarvisMarch.h"

void runConvexHullAlgorithm(std::vector < RGPPoint2D* > (*algorithmFunction)(std::vector < RGPPoint2D* >), std::string algorithmName, std::vector < RGPPoint2D* > points);

/*
 * Prints the vector of points
 */
void printPoints(std::vector < RGPPoint2D* > points) {
    for (int i = 0; i < (int)points.size(); i++) {
        std::cout << "(" << points[i]->x << "," << points[i]->y << ") ";
    }

    std::cout << std::endl;
}

int main(void) {
    std::vector < RGPPoint2D* > points;
    Number a1("3");
    Number b1("0");    
    RGPPoint2D* p1 = new RGPPoint2D(a1, b1);
    points.push_back(p1);

    Number a2("0");
    Number b2("1");
    RGPPoint2D* p2 = new RGPPoint2D(a2, b2);
    points.push_back(p2);

    Number a3("1");
    Number b3("2");
    RGPPoint2D* p3 = new RGPPoint2D(a3, b3);
    points.push_back(p3);

    Number a4("6");
    Number b4("2");
    RGPPoint2D* p4 = new RGPPoint2D(a4, b4);
    points.push_back(p4);

    Number a5("4");
    Number b5("3");
    RGPPoint2D* p5 = new RGPPoint2D(a5, b5);
    points.push_back(p5);

    Number a6("0");
    Number b6("4");
    RGPPoint2D* p6 = new RGPPoint2D(a6, b6);
    points.push_back(p6);

    Number a7("2");
    Number b7("5");
    RGPPoint2D* p7 = new RGPPoint2D(a7, b7);
    points.push_back(p7);

    Number a8("5");
    Number b8("5");
    RGPPoint2D* p8 = new RGPPoint2D(a8, b8);
    points.push_back(p8);

    // std::cout << p8->x << std::endl;

    // Convex hull: (0,1) (3,0) (6,2) (5,5) (2,5) (0,4) 
    // runConvexHullAlgorithm(getGraham, "GrahamScan", points);
    // runConvexHullAlgorithm(getMonotone, "MonotoneChain", points);
    // runConvexHullAlgorithm(getConvexHullDivideAndConquer, "DivideAndConquer", points);
    // runConvexHullAlgorithm(getConvexHullJarvisMarch, "JarvisMarch", points);
    // runConvexHullAlgorithm(getConvexHullChans, "Chans", points);

    return 0;
}

void runConvexHullAlgorithm(std::vector < RGPPoint2D* > (*algorithmFunction)(std::vector < RGPPoint2D* >), std::string algorithmName, std::vector < RGPPoint2D* > points) {
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "Algorithm: " << algorithmName << std::endl;

    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    std::cout << "Point set before --> ";
    printPoints(points);
    std::vector < RGPPoint2D* > convexHull = (*algorithmFunction)(points);
    std::cout << "Point set after --> ";
    printPoints(points);
    // std::cout << "Convex hull after --> ";
    // printPoints(convexHull);
    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast< std::chrono::microseconds >(endTime - startTime).count();
    std::cout << "Time taken: " << duration << " (microseconds)" << std::endl;

    std::cout << "Convex hull: ";
    printPoints(convexHull);
}