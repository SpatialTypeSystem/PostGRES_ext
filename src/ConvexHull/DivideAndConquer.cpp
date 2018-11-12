#include <algorithm>
#include <iostream>
#include <vector>

#include "../../include/RGPPoint2D.h"
#include "../../include/ConvexHull/Utils.h"

/*
 * Merges two convex hulls
 */
std::vector < RGPPoint2D* > mergeConvexHulls(std::vector < RGPPoint2D* > leftConvexHull, std::vector < RGPPoint2D* > rightConvexHull) {
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
    Number rightMostXCordinateOfLeftHull("-1");
    int rightMostIndexOfLeftHull = -1;
    for (int i = 0; i < leftConvexHullSize; i++) {
        if (rightMostIndexOfLeftHull == -1 || leftConvexHull[i]->x > rightMostXCordinateOfLeftHull) {
            rightMostXCordinateOfLeftHull = leftConvexHull[i]->x;
            rightMostIndexOfLeftHull = i;
        }
    }

    // calculate left most point of right convex hull
    Number leftMostXCordinateOfRightHull("-1");
    int leftMostIndexOfRightHull = -1;
    for (int i = 0; i < rightConvexHullSize; i++) {
        if (leftMostIndexOfRightHull == -1 || rightConvexHull[i]->x <= leftMostXCordinateOfRightHull) {
            rightMostXCordinateOfLeftHull = leftConvexHull[i]->x;
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
    std::vector < RGPPoint2D* > mergedConvexHull;
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
std::vector < RGPPoint2D* > getConvexHullBruteForce(std::vector < RGPPoint2D* > points) {
    int pointsSize = (int)points.size();
    std::vector < RGPPoint2D* > convexHull;

    if (pointsSize == 1) {
        convexHull.push_back(points[0]);
    }
    else if (pointsSize == 2) {
        if ((points[0]->x < points[1]->x) || 
            (points[0]->x == points[1]->x && points[0]->y < points[1]->y)) {
            convexHull.push_back(points[0]);
            convexHull.push_back(points[1]);
        }
        else {
            convexHull.push_back(points[1]);
            convexHull.push_back(points[0]);
        }
    }
    else if (pointsSize == 3) {
        Number leftMostXCordinate, leftMostYCordinate;
        int leftMostPointIndex = -1;
        for (int i = 0; i < pointsSize; i++) {
            if (leftMostPointIndex == -1 ||
                (points[i]->x < leftMostXCordinate || (points[i]->x == leftMostXCordinate && points[i]->y < leftMostYCordinate))) {
                    leftMostXCordinate = points[i]->x;
                    leftMostYCordinate = points[i]->y;
                }
        }

        Number rightMostXCordinate, rightMostYCordinate;
        int rightMostPointIndex = -1;
        for (int i = 0; i < pointsSize; i++) {
            if (rightMostPointIndex == -1 ||
                (points[i]->x > rightMostXCordinate || (points[i]->x == rightMostXCordinate && points[i]->y > rightMostYCordinate))) {
                    rightMostXCordinate = points[i]->x;
                    rightMostYCordinate = points[i]->y;
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
std::vector < RGPPoint2D* > getConvexHullDivideAndConquerInternal(std::vector < RGPPoint2D* >& points) {
    int numberOfPoints = (int)points.size();
    if (numberOfPoints <= 3) {
        return getConvexHullBruteForce(points);
    }

    int splitIndex = numberOfPoints / 2;
    std::cout << "splitIndex: " << splitIndex << std::endl;

    std::vector < RGPPoint2D* > leftPoints; 
    std::vector < RGPPoint2D* > rightPoints;
    for (int i = 0; i < splitIndex; i++) {
        leftPoints.push_back(points[i]);
    }

    for (int i = splitIndex; i < numberOfPoints; i++) {
        rightPoints.push_back(points[i]);
    }

    std::vector < RGPPoint2D* > leftConvexHull = getConvexHullDivideAndConquerInternal(leftPoints);
    std::vector < RGPPoint2D* > rightConvexHull = getConvexHullDivideAndConquerInternal(rightPoints);
    std::vector < RGPPoint2D* > convexHull = mergeConvexHulls(leftConvexHull, rightConvexHull);
    return convexHull;
}

/*
 * Computes convex hull using divide and conquer method
 */
std::vector < RGPPoint2D* > getConvexHullDivideAndConquer(std::vector < RGPPoint2D* > points) {
    std::vector < RGPPoint2D* > pointsCopy(points);
    std::sort(pointsCopy.begin(), pointsCopy.end(), pointsComparator());

    std::vector < RGPPoint2D* > convexHullPoints = getConvexHullDivideAndConquerInternal(pointsCopy);
    return convexHullPoints;
}