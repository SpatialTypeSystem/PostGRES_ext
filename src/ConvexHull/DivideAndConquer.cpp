#include <algorithm>
#include <iostream>
#include <vector>

/*
 * Comparator to compare points consisting of x and y coordinates
 * returns true if x coordinate of first point is less than x coordinate of second point
 * or if y coordinate of first point is less than y coordinate of second point when the x coordinates are equal
 */
struct pointsComparator
{
    inline bool operator() (const std::pair < double, double>& a, const std::pair < double, double>& b)
    {
        if (a.first == b.first)
            return a.second < b.second;

        return a.first < b.first;
    }
};

/*
 * +1 : if p3 is left of line (p1, p2)
 * 0 : if p3 is on line (p1, p2)
 * -1 : if p3 is right of line (p1, p2)
 */
int getPositionOfPoint(std::pair < double, double > p1, std::pair < double, double > p2, std::pair < double, double > p3) {
    // Calculates determinant of the below matrix
    // │x1  y1  1│
    // │x2  y2  1│
    // │x3  y3  1│
    int position = p1.first * p2.second - p1.first * p3.second
                    - p1.second * p2.first + p1.second * p3.first
                    + p2.first * p3.second - p3.first * p2.second;
    if (position > 1)
        position = 1;
    if (position < -1)
        position = -1;

    return position;
}

/*
 * Merges two convex hulls
 */
std::vector < std::pair < double, double > > mergeConvexHulls(std::vector < std::pair < double, double > > leftConvexHull, std::vector < std::pair < double, double > > rightConvexHull) {
    int leftConvexHullSize = (int)leftConvexHull.size();
    int rightConvexHullSize = (int)rightConvexHull.size();

    // if left is empty, return right convex hull
    if (leftConvexHullSize == 0) {
        return rightConvexHull;
    }

    // if right is empty, return left convex hull
    if (rightConvexHullSize == 0) {
        return leftConvexHull;
    }

    // calculate right most point of left convex hull
    double rightMostXCordinateOfLeftHull = -1.0;
    int rightMostIndexOfLeftHull = -1;
    for (int i = 0; i < leftConvexHullSize; i++) {
        if (rightMostIndexOfLeftHull == -1 || leftConvexHull[i].first > rightMostXCordinateOfLeftHull) {
            rightMostXCordinateOfLeftHull = leftConvexHull[i].first;
            rightMostIndexOfLeftHull = i;
        }
    }

    // calculate left most point of right convex hull
    double leftMostXCordinateOfRightHull = -1.0;
    int leftMostIndexOfRightHull = -1;
    for (int i = 0; i < rightConvexHullSize; i++) {
        if (leftMostIndexOfRightHull == -1 || rightConvexHull[i].first <= leftMostXCordinateOfRightHull) {
            rightMostXCordinateOfLeftHull = leftConvexHull[i].first;
            leftMostIndexOfRightHull = i;
        }
    }

    // initialize left end points of upper and lower tangent
    int lowerTangentLeftPointIndex  = -1, lowerTangentRightPointIndex = -1, upperTangentLeftPointIndex = -1, upperTangentRightPointIndex = -1;
    if (leftConvexHullSize == 1) {
        lowerTangentLeftPointIndex = 0;
        upperTangentLeftPointIndex = 0;
    }
    else {
        lowerTangentLeftPointIndex = rightMostIndexOfLeftHull;
        upperTangentLeftPointIndex = rightMostIndexOfLeftHull;
    }

    // initialize right end points of upper and lower tangent
    if (rightConvexHullSize == 1) {
        lowerTangentRightPointIndex = 0;
        upperTangentRightPointIndex = 0;
    }
    else {
        lowerTangentRightPointIndex = leftMostIndexOfRightHull;
        upperTangentRightPointIndex = leftMostIndexOfRightHull;
    }

    bool changed = true;
    int posBefore, posAfter;

    // calculating lower tangent end points
    while (changed) {
        changed = false;

        // check if points immediately before and after lowerTangentLeftPointIndex are present
        // left of lowerTangentLeftPointIndex and lowerTangentRightPointIndex
        if (leftConvexHullSize > 1) {
            posBefore = lowerTangentLeftPointIndex == 0 ? (leftConvexHullSize - 1) : (lowerTangentLeftPointIndex - 1);
            posAfter = (lowerTangentLeftPointIndex + 1) % leftConvexHullSize;
            
            while (getPositionOfPoint(leftConvexHull[lowerTangentLeftPointIndex], rightConvexHull[lowerTangentRightPointIndex], leftConvexHull[posBefore]) < 0 ||
                getPositionOfPoint(leftConvexHull[lowerTangentLeftPointIndex], rightConvexHull[lowerTangentRightPointIndex], leftConvexHull[posAfter]) < 0) {
                lowerTangentLeftPointIndex = posBefore;
                changed = true;

                posBefore = lowerTangentLeftPointIndex == 0 ? (leftConvexHullSize - 1) : (lowerTangentLeftPointIndex - 1);
                posAfter = (lowerTangentLeftPointIndex + 1) % leftConvexHullSize;
            }
        }

        // check if points immediately before and after lowerTangentRightPointIndex are present
        // left of lowerTangentLeftPointIndex and lowerTangentRightPointIndex
        if (rightConvexHullSize > 1) {
            posBefore = lowerTangentRightPointIndex == 0 ? (rightConvexHullSize - 1) : (lowerTangentRightPointIndex - 1);
            posAfter = (lowerTangentRightPointIndex + 1) % rightConvexHullSize;

            while (getPositionOfPoint(leftConvexHull[lowerTangentLeftPointIndex], rightConvexHull[lowerTangentRightPointIndex], rightConvexHull[posBefore]) < 0 ||
                getPositionOfPoint(leftConvexHull[lowerTangentLeftPointIndex], rightConvexHull[lowerTangentRightPointIndex], rightConvexHull[posAfter]) < 0) {
                lowerTangentRightPointIndex = posAfter;
                changed = true;

                posBefore = lowerTangentRightPointIndex == 0 ? (rightConvexHullSize - 1) : (lowerTangentRightPointIndex - 1);
                posAfter = (lowerTangentRightPointIndex + 1) % rightConvexHullSize;
            }
        }
    }

    changed = true;

    // calculating upper tangent end points
    while (changed) {
        changed = false;

        // check if points immediately before and after upperTangentLeftPointIndex are present
        // left of upperTangentLeftPointIndex and upperTangentRightPointIndex
        if (leftConvexHullSize > 1) {
            posBefore = upperTangentLeftPointIndex == 0 ? (leftConvexHullSize - 1) : (upperTangentLeftPointIndex - 1);
            posAfter = (upperTangentLeftPointIndex + 1) % leftConvexHullSize;
            while (getPositionOfPoint(leftConvexHull[upperTangentLeftPointIndex], rightConvexHull[upperTangentRightPointIndex], leftConvexHull[posBefore]) > 0 ||
                getPositionOfPoint(leftConvexHull[upperTangentLeftPointIndex], rightConvexHull[upperTangentRightPointIndex], leftConvexHull[posAfter]) > 0) {
                upperTangentLeftPointIndex = posAfter;
                changed = true;

                posBefore = upperTangentLeftPointIndex == 0 ? (leftConvexHullSize - 1) : (upperTangentLeftPointIndex - 1);
                posAfter = (upperTangentLeftPointIndex + 1) % leftConvexHullSize;
            }
        }

        // check if points immediately before and after upperTangentRightPointIndex are present
        // left of upperTangentLeftPointIndex and upperTangentRightPointIndex
        if (rightConvexHullSize > 1) {
            posBefore = upperTangentRightPointIndex == 0 ? (rightConvexHullSize - 1) : (upperTangentRightPointIndex - 1);
            posAfter = (upperTangentRightPointIndex + 1) % rightConvexHullSize;
            while (getPositionOfPoint(leftConvexHull[upperTangentLeftPointIndex], rightConvexHull[upperTangentRightPointIndex], rightConvexHull[posBefore]) > 0 ||
                getPositionOfPoint(leftConvexHull[upperTangentLeftPointIndex], rightConvexHull[upperTangentRightPointIndex], rightConvexHull[posAfter]) > 0) {
                upperTangentRightPointIndex = posBefore;
                changed = true;

                posBefore = upperTangentRightPointIndex == 0 ? (rightConvexHullSize - 1) : (upperTangentRightPointIndex - 1);
                posAfter = (upperTangentRightPointIndex + 1) % rightConvexHullSize;
            }
        }
    }

    // calculate merged convex hull
    // include points till left end point of lower tangent
    std::vector < std::pair < double, double > > mergedConvexHull;
    for (int i = 0; i <= lowerTangentLeftPointIndex; i++) {
        mergedConvexHull.push_back(leftConvexHull[i]);
    }

    // include right end point of lower tangent
    mergedConvexHull.push_back(rightConvexHull[lowerTangentRightPointIndex]);

    // include points between right end point of lower tangent to right end point of upper tangent
    if (lowerTangentRightPointIndex != upperTangentRightPointIndex) {
        for (int i = lowerTangentRightPointIndex + 1; i < upperTangentRightPointIndex; i++) {
            mergedConvexHull.push_back(rightConvexHull[i]);
        }

        mergedConvexHull.push_back(rightConvexHull[upperTangentRightPointIndex]);
    }

    // include points after and including left end point of upper tangent
    if (upperTangentLeftPointIndex != lowerTangentLeftPointIndex) {   
        for (int i = upperTangentLeftPointIndex; i < leftConvexHullSize; i++) {
            mergedConvexHull.push_back(leftConvexHull[i]);
        }
    }

    return mergedConvexHull;
}

/*
 * Computes convex hull of points in
 * near constant time when number of points <= 3
 */
std::vector < std::pair < double, double > > getConvexHullBruteForce(std::vector < std::pair < double, double > > points) {
    int pointsSize = (int)points.size();
    std::vector < std::pair < double, double > > convexHull;

    if (pointsSize == 1) {
        convexHull.push_back(points[0]);
    }
    else if (pointsSize == 2) {
        if ((points[0].first < points[1].first) || 
            (points[0].first == points[1].first && points[0].second < points[1].second)) {
            convexHull.push_back(points[0]);
            convexHull.push_back(points[1]);
        }
        else {
            convexHull.push_back(points[1]);
            convexHull.push_back(points[0]);
        }
    }
    else if (pointsSize == 3) {
        double leftMostXCordinate, leftMostYCordinate;
        int leftMostPointIndex = -1;
        for (int i = 0; i < pointsSize; i++) {
            if (leftMostPointIndex == -1 ||
                (points[i].first < leftMostXCordinate || (points[i].first == leftMostXCordinate && points[i].second < leftMostYCordinate))) {
                    leftMostXCordinate = points[i].first;
                    leftMostYCordinate = points[i].second;
                }
        }

        double rightMostXCordinate, rightMostYCordinate;
        int rightMostPointIndex = -1;
        for (int i = 0; i < pointsSize; i++) {
            if (rightMostPointIndex == -1 ||
                (points[i].first > rightMostXCordinate || (points[i].first == rightMostXCordinate && points[i].second > rightMostYCordinate))) {
                    rightMostXCordinate = points[i].first;
                    rightMostYCordinate = points[i].second;
                }
        }

        int middlePointIndex = 0;
        for (int i = 0; i < 2; i++) {
            if (leftMostPointIndex == middlePointIndex || rightMostPointIndex == middlePointIndex) {
                middlePointIndex++;
            }
        }

        convexHull.push_back(points[leftMostPointIndex]);
        convexHull.push_back(points[middlePointIndex]);
        convexHull.push_back(points[rightMostPointIndex]);
    }

    return convexHull;
}

/*
 * Intenal method to compute convex hull using divide and conquer method
 */
std::vector < std::pair < double, double > > getConvexHullDivideAndConquerInternal(std::vector < std::pair < double, double > > points) {
    int numberOfPoints = (int)points.size();
    if (numberOfPoints <= 3) {
        return getConvexHullBruteForce(points);
    }

    int splitIndex = numberOfPoints / 2;
    // std::cout << "splitIndex: " << splitIndex << std::endl;

    std::vector < std::pair < double, double > > leftPoints; 
    std::vector < std::pair < double, double > > rightPoints;
    for (int i = 0; i < splitIndex; i++) {
        leftPoints.push_back(points[i]);
    }

    for (int i = splitIndex; i < numberOfPoints; i++) {
        rightPoints.push_back(points[i]);
    }

    std::vector < std::pair < double, double > > leftConvexHull = getConvexHullDivideAndConquerInternal(leftPoints);
    std::vector < std::pair < double, double > > rightConvexHull = getConvexHullDivideAndConquerInternal(rightPoints);
    std::vector < std::pair < double, double > > convexHull = mergeConvexHulls(leftConvexHull, rightConvexHull);
    return convexHull;
}

/*
 * Computes convex hull using divide and conquer method
 */
std::vector < std::pair < double, double > > getConvexHullDivideAndConquer(std::vector < std::pair < double, double > >& points) {
    std::vector < std::pair < double, double > > pointsCopy(points);

    std::sort(pointsCopy.begin(), pointsCopy.end(), pointsComparator());

    std::vector < std::pair < double, double > > convexHullPoints = getConvexHullDivideAndConquerInternal(pointsCopy);
    return convexHullPoints;
}