#include <algorithm>
#include <iostream>
#include <vector>

#include "../../include/ConvexHull/Utils.h"
#include "../../include/RGPPoint2D.h"

/*
 * Merges two convex hulls
 */
std::vector<RGPPoint2D *> mergeConvexHulls(std::vector<RGPPoint2D *> leftConvexHull, std::vector<RGPPoint2D *> rightConvexHull)
{
  int leftConvexHullSize = (int)leftConvexHull.size();
  int rightConvexHullSize = (int)rightConvexHull.size();

  // if left is empty, return right convex hull
  if (leftConvexHullSize == 0)
  {
    return rightConvexHull;
  }

  // if right is empty, return left convex hull
  if (rightConvexHullSize == 0)
  {
    return leftConvexHull;
  }

  // calculate right most point of left convex hull
  Number rightMostXCordinateOfLeftHull("0.0");
  int rightMostIndexOfLeftHull = -1;
  for (int i = 0; i < leftConvexHullSize; i++)
  {
    if (rightMostIndexOfLeftHull == -1 || leftConvexHull[i]->x > rightMostXCordinateOfLeftHull)
    {
      rightMostXCordinateOfLeftHull = leftConvexHull[i]->x;
      rightMostIndexOfLeftHull = i;
    }
  }

  // calculate left most point of right convex hull
  Number leftMostXCordinateOfRightHull("0.0");
  int leftMostIndexOfRightHull = -1;
  for (int i = 0; i < rightConvexHullSize; i++)
  {
    if (leftMostIndexOfRightHull == -1 || rightConvexHull[i]->x <= leftMostXCordinateOfRightHull)
    {
      rightMostXCordinateOfLeftHull = leftConvexHull[i]->x;
      leftMostIndexOfRightHull = i;
    }
  }

  // initialize left end points of upper and lower tangent
  int lowerTangentLeftPointIndex = -1, lowerTangentRightPointIndex = -1, upperTangentLeftPointIndex = -1, upperTangentRightPointIndex = -1;
  if (leftConvexHullSize == 1)
  {
    lowerTangentLeftPointIndex = 0;
    upperTangentLeftPointIndex = 0;
  }
  else
  {
    lowerTangentLeftPointIndex = rightMostIndexOfLeftHull;
    upperTangentLeftPointIndex = rightMostIndexOfLeftHull;
  }

  // initialize right end points of upper and lower tangent
  if (rightConvexHullSize == 1)
  {
    lowerTangentRightPointIndex = 0;
    upperTangentRightPointIndex = 0;
  }
  else
  {
    lowerTangentRightPointIndex = leftMostIndexOfRightHull;
    upperTangentRightPointIndex = leftMostIndexOfRightHull;
  }

  bool changed = true;
  int posBefore, posAfter;

  // calculating lower tangent end points
  while (changed)
  {
    changed = false;

    // check if points immediately before and after lowerTangentLeftPointIndex are present
    // left of lowerTangentLeftPointIndex and lowerTangentRightPointIndex
    if (leftConvexHullSize > 1)
    {
      posBefore = lowerTangentLeftPointIndex == 0 ? (leftConvexHullSize - 1) : (lowerTangentLeftPointIndex - 1);
      posAfter = (lowerTangentLeftPointIndex + 1) % leftConvexHullSize;

      while (getPositionOfPoint(leftConvexHull[lowerTangentLeftPointIndex], rightConvexHull[lowerTangentRightPointIndex], leftConvexHull[posBefore]) < 0 ||
             getPositionOfPoint(leftConvexHull[lowerTangentLeftPointIndex], rightConvexHull[lowerTangentRightPointIndex], leftConvexHull[posAfter]) < 0)
      {
        lowerTangentLeftPointIndex = posBefore;
        changed = true;

        posBefore = lowerTangentLeftPointIndex == 0 ? (leftConvexHullSize - 1) : (lowerTangentLeftPointIndex - 1);
        posAfter = (lowerTangentLeftPointIndex + 1) % leftConvexHullSize;
      }
    }

    // check if points immediately before and after lowerTangentRightPointIndex are present
    // left of lowerTangentLeftPointIndex and lowerTangentRightPointIndex
    if (rightConvexHullSize > 1)
    {
      posBefore = lowerTangentRightPointIndex == 0 ? (rightConvexHullSize - 1) : (lowerTangentRightPointIndex - 1);
      posAfter = (lowerTangentRightPointIndex + 1) % rightConvexHullSize;

      while (getPositionOfPoint(leftConvexHull[lowerTangentLeftPointIndex], rightConvexHull[lowerTangentRightPointIndex], rightConvexHull[posBefore]) < 0 ||
             getPositionOfPoint(leftConvexHull[lowerTangentLeftPointIndex], rightConvexHull[lowerTangentRightPointIndex], rightConvexHull[posAfter]) < 0)
      {
        lowerTangentRightPointIndex = posAfter;
        changed = true;

        posBefore = lowerTangentRightPointIndex == 0 ? (rightConvexHullSize - 1) : (lowerTangentRightPointIndex - 1);
        posAfter = (lowerTangentRightPointIndex + 1) % rightConvexHullSize;
      }
    }
  }

  changed = true;

  // calculating upper tangent end points
  while (changed)
  {
    changed = false;

    // check if points immediately before and after upperTangentLeftPointIndex are present
    // left of upperTangentLeftPointIndex and upperTangentRightPointIndex
    if (leftConvexHullSize > 1)
    {
      posBefore = upperTangentLeftPointIndex == 0 ? (leftConvexHullSize - 1) : (upperTangentLeftPointIndex - 1);
      posAfter = (upperTangentLeftPointIndex + 1) % leftConvexHullSize;
      while (getPositionOfPoint(leftConvexHull[upperTangentLeftPointIndex], rightConvexHull[upperTangentRightPointIndex], leftConvexHull[posBefore]) > 0 ||
             getPositionOfPoint(leftConvexHull[upperTangentLeftPointIndex], rightConvexHull[upperTangentRightPointIndex], leftConvexHull[posAfter]) > 0)
      {
        upperTangentLeftPointIndex = posAfter;
        changed = true;

        posBefore = upperTangentLeftPointIndex == 0 ? (leftConvexHullSize - 1) : (upperTangentLeftPointIndex - 1);
        posAfter = (upperTangentLeftPointIndex + 1) % leftConvexHullSize;
      }
    }

    // check if points immediately before and after upperTangentRightPointIndex are present
    // left of upperTangentLeftPointIndex and upperTangentRightPointIndex
    if (rightConvexHullSize > 1)
    {
      posBefore = upperTangentRightPointIndex == 0 ? (rightConvexHullSize - 1) : (upperTangentRightPointIndex - 1);
      posAfter = (upperTangentRightPointIndex + 1) % rightConvexHullSize;
      while (getPositionOfPoint(leftConvexHull[upperTangentLeftPointIndex], rightConvexHull[upperTangentRightPointIndex], rightConvexHull[posBefore]) > 0 ||
             getPositionOfPoint(leftConvexHull[upperTangentLeftPointIndex], rightConvexHull[upperTangentRightPointIndex], rightConvexHull[posAfter]) > 0)
      {
        upperTangentRightPointIndex = posBefore;
        changed = true;

        posBefore = upperTangentRightPointIndex == 0 ? (rightConvexHullSize - 1) : (upperTangentRightPointIndex - 1);
        posAfter = (upperTangentRightPointIndex + 1) % rightConvexHullSize;
      }
    }
  }

  // calculate merged convex hull
  // include points till left end point of lower tangent
  std::vector<RGPPoint2D *> mergedConvexHull;
  for (int i = 0; i <= lowerTangentLeftPointIndex; i++)
  {
    mergedConvexHull.push_back(leftConvexHull[i]);
  }

  // include right end point of lower tangent
  mergedConvexHull.push_back(rightConvexHull[lowerTangentRightPointIndex]);

  // include points between right end point of lower tangent to right end point of upper tangent
  if (lowerTangentRightPointIndex != upperTangentRightPointIndex)
  {
    for (int i = lowerTangentRightPointIndex + 1; i < upperTangentRightPointIndex; i++)
    {
      mergedConvexHull.push_back(rightConvexHull[i]);
    }

    mergedConvexHull.push_back(rightConvexHull[upperTangentRightPointIndex]);
  }

  // include points after and including left end point of upper tangent
  if (upperTangentLeftPointIndex != lowerTangentLeftPointIndex)
  {
    for (int i = upperTangentLeftPointIndex; i < leftConvexHullSize; i++)
    {
      mergedConvexHull.push_back(leftConvexHull[i]);
    }
  }

  int mergedHullSize = (int)mergedConvexHull.size();
  if (mergedHullSize > 2)
  {
    int m = 1;
    for (int i = 2; i < (int)mergedConvexHull.size(); i++)
    {
      while (i < mergedHullSize && m > 0 && getPositionOfPoint(mergedConvexHull[i], mergedConvexHull[m], mergedConvexHull[m - 1]) == 0)
      {
        swap(mergedConvexHull, m, i);
        i++;
      }

      if (i < mergedHullSize)
      {
        m++;
        swap(mergedConvexHull, m, i);
      }
    }

    m++;

    while ((int)mergedConvexHull.size() > m)
    {
      mergedConvexHull.pop_back();
    }

    mergedHullSize = (int)mergedConvexHull.size();
    if (mergedHullSize > 2)
    {
      if (getPositionOfPoint(mergedConvexHull[mergedHullSize - 2], mergedConvexHull[mergedHullSize - 1], mergedConvexHull[0]) == 0)
      {
        mergedConvexHull.pop_back();
      }
    }
  }

  return mergedConvexHull;
}

/*
 * Intenal method to compute convex hull using divide and conquer method
 */
std::vector<RGPPoint2D *> getConvexHullDivideAndConquerInternal(std::vector<RGPPoint2D *> &points)
{
  int numberOfPoints = (int)points.size();
  if (numberOfPoints <= 3)
  {
    return getConvexHullBruteForce(points);
  }

  int splitIndex = numberOfPoints / 2;
  // std::cout << "splitIndex: " << splitIndex << std::endl;

  std::vector<RGPPoint2D *> leftPoints;
  std::vector<RGPPoint2D *> rightPoints;
  for (int i = 0; i < splitIndex; i++)
  {
    leftPoints.push_back(points[i]);
  }

  for (int i = splitIndex; i < numberOfPoints; i++)
  {
    rightPoints.push_back(points[i]);
  }

  std::vector<RGPPoint2D *> leftConvexHull = getConvexHullDivideAndConquerInternal(leftPoints);
  std::vector<RGPPoint2D *> rightConvexHull = getConvexHullDivideAndConquerInternal(rightPoints);
  std::vector<RGPPoint2D *> convexHull = mergeConvexHulls(leftConvexHull, rightConvexHull);
  return convexHull;
}

/*
 * Computes convex hull using divide and conquer method
 */
std::vector<RGPPoint2D *> getConvexHullDivideAndConquer(std::vector<RGPPoint2D *> points)
{
  std::vector<RGPPoint2D *> pointsCopy(points);
  std::sort(pointsCopy.begin(), pointsCopy.end(), pointsComparator());

  std::vector<RGPPoint2D *> convexHullPoints = getConvexHullDivideAndConquerInternal(pointsCopy);
  return convexHullPoints;
}