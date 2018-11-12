#include <cmath>
#include <vector>

#include "../../include/RGPPoint2D.h"
#include "../../include/ConvexHull/DivideAndConquer.h"

std::vector < RGPPoint2D* > getHull(std::vector < RGPPoint2D* > points) {
    // TODO: use graham scan when available
    return getConvexHullDivideAndConquer(points);
}

std::vector < RGPPoint2D* > mergeHulls(std::vector < std::vector < RGPPoint2D* > >& hulls, int m, bool* isCompleteHullObtained) {
    std::vector < RGPPoint2D* > convexHull;
    
    // TODO: add merge hull code
    return convexHull;
}

std::vector < std::vector < RGPPoint2D* > > getSubHulls(std::vector < RGPPoint2D* >& points, int m) {
    std::vector < std::vector < RGPPoint2D* > > subHulls;
    int pointsSize = (int)points.size();

    std::vector < RGPPoint2D* > currentPoints;
    for (int i = 0; i < pointsSize; i++) {
        currentPoints.push_back(points[i]);

        if ((int)currentPoints.size() == m) {
            subHulls.push_back(getHull(currentPoints));
            currentPoints.clear();
        }
    }

    if ((int)currentPoints.size() > 0) {
        subHulls.push_back(getHull(currentPoints));
        currentPoints.clear();
    }

    return subHulls;
}

std::vector < RGPPoint2D* > getConvexHullChansInternal(std::vector < RGPPoint2D* >& points) {
    int t = 1;
    int m = pow(2, pow(2, t));
    bool isCompleteHullObtained = false;
    std::vector < RGPPoint2D* > convexHullPoints;
    std::vector < std::vector < RGPPoint2D* > > subHulls;

    do {
        subHulls = getSubHulls(convexHullPoints, m);
        convexHullPoints = mergeHulls(subHulls, m, &isCompleteHullObtained);
        t++;
    } while (!isCompleteHullObtained);

    return convexHullPoints;
}

/*
 * Computes convex hull using divide and conquer method
 */
std::vector < RGPPoint2D* > getConvexHullChans(std::vector < RGPPoint2D* > points) {
    std::vector < RGPPoint2D* > pointsCopy(points);

    std::vector < RGPPoint2D* > convexHullPoints = getConvexHullChansInternal(pointsCopy);
    return convexHullPoints;
}