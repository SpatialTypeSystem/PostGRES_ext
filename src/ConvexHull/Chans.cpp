#include <cmath>
#include <vector>

#include "../../include/ConvexHull/DivideAndConquer.h"

std::vector < std::pair < double, double > > getHull(std::vector < std::pair < double, double > > points) {
    // TODO: use graham scan when available
    return getConvexHullDivideAndConquer(points);
}

std::vector < std::pair < double, double > > mergeHulls(std::vector < std::vector < std::pair < double, double > > > hulls, int m, bool* isCompleteHullObtained) {
    std::vector < std::pair < double, double > > convexHull;
    
    // TODO: add merge hull code
    return convexHull;
}

std::vector < std::vector < std::pair < double, double > > > getSubHulls(std::vector < std::pair < double, double > >& points, int m) {
    std::vector < std::vector < std::pair < double, double > > > subHulls;
    int pointsSize = (int)points.size();

    std::vector < std::pair < double, double > > currentPoints;
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

std::vector < std::pair < double, double > > getConvexHullChansInternal(std::vector < std::pair < double, double > >& points) {
    int t = 1;
    int m = pow(2, pow(2, t));
    bool isCompleteHullObtained = false;
    std::vector < std::pair < double, double > > convexHullPoints;
    std::vector < std::vector < std::pair < double, double > > > subHulls;

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
std::vector < std::pair < double, double > > getConvexHullChans(std::vector < std::pair < double, double > >& points) {
    std::vector < std::pair < double, double > > pointsCopy(points);

    std::vector < std::pair < double, double > > convexHullPoints = getConvexHullChansInternal(pointsCopy);
    return convexHullPoints;
}