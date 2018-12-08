#include <algorithm>
#include <iostream>
#include <vector>

#include "../../include/ConvexHull/Utils.h"
#include "../../include/RGPPoint2D.h"

void printPoints1(std::vector<RGPPoint2D *> points)
{
  for (int i = 0; i < (int)points.size(); i++)
  {
    std::cout << "(" << points[i]->x << "," << points[i]->y << ") ";
  }

  std::cout << std::endl;
}

/*
 * Merges two convex hulls
 */
std::vector<RGPPoint2D *> mergeConvexHulls(std::vector<RGPPoint2D *> leftConvexHull, std::vector<RGPPoint2D *> rightConvexHull)
{
  std::vector<RGPPoint2D *> convexHull;

  // n1 -> number of points in polygon a
  // n2 -> number of points in polygon b
  int n1 = leftConvexHull.size(), n2 = rightConvexHull.size();
  // printPoints1(leftConvexHull);
  // printPoints1(rightConvexHull);
  // std::cout << n1 << " " << n2 << std::endl;
  while ((int)leftConvexHull.size() > 1 &&
          getPositionOfPoint(leftConvexHull[(int)leftConvexHull.size() - 2], leftConvexHull[(int)leftConvexHull.size() - 1], rightConvexHull[0]) == 0)
    leftConvexHull.pop_back();

  while ((int)rightConvexHull.size() > 1 &&
          getPositionOfPoint(leftConvexHull[0], rightConvexHull[0], rightConvexHull[1]) == 0)
    rightConvexHull.pop_back();

  if ((int)leftConvexHull.size() == 1 && (int)rightConvexHull.size() == 1)
  {
    convexHull.push_back(leftConvexHull[0]);
    convexHull.push_back(rightConvexHull[0]);
    return convexHull;
  }

  int ia = 0, ib = 0;
  for (int i = 1; i < n1; i++)
    if (leftConvexHull[i]->x > leftConvexHull[ia]->x)
      ia = i;

  // ib -> leftmost point of b
  for (int i = 1; i < n2; i++)
    if (rightConvexHull[i]->x < rightConvexHull[ib]->x)
      ib = i;

  // finding the upper tangent
  int inda = ia, indb = ib;
  bool done = 0;
  while (!done)
  {
    done = 1;
    while (getPositionOfPoint(rightConvexHull[indb], leftConvexHull[inda], leftConvexHull[(inda + 1) % n1]) <= 0)
      inda = (inda + 1) % n1;

    while (getPositionOfPoint(leftConvexHull[inda], rightConvexHull[indb], rightConvexHull[(n2 + indb - 1) % n2]) >= 0)
    {
      indb = (n2 + indb - 1) % n2;
      done = 0;
    }
  }

  int uppera = inda, upperb = indb;
  inda = ia, indb = ib;
  done = 0;
  int g = 0;
  while (!done) //finding the lower tangent
  {
    done = 1;
    while (getPositionOfPoint(leftConvexHull[inda], rightConvexHull[indb], rightConvexHull[(indb + 1) % n2]) <= 0)
      indb = (indb + 1) % n2;

    while (getPositionOfPoint(rightConvexHull[indb], leftConvexHull[inda], leftConvexHull[(n1 + inda - 1) % n1]) >= 0)
    {
      inda = (n1 + inda - 1) % n1;
      done = 0;
    }
  }

  int lowera = inda, lowerb = indb;

  //ret contains the convex hull after merging the two convex hulls
  //with the points sorted in anti-clockwise order
  int ind = uppera;
  convexHull.push_back(leftConvexHull[uppera]);
  while (ind != lowera)
  {
    ind = (ind + 1) % n1;
    convexHull.push_back(leftConvexHull[ind]);
  }

  ind = lowerb;
  convexHull.push_back(rightConvexHull[lowerb]);
  while (ind != upperb)
  {
    ind = (ind + 1) % n2;
    convexHull.push_back(rightConvexHull[ind]);
  }
  return convexHull;
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
std::vector<RGPPoint2D *> getConvexHullDivideAndConquer(std::vector<RGPPoint2D *> &points)
{
  std::vector<RGPPoint2D *> pointsCopy(points);
  std::sort(pointsCopy.begin(), pointsCopy.end(), pointsComparator());

  std::vector<RGPPoint2D *> convexHullPoints = getConvexHullDivideAndConquerInternal(pointsCopy);
  return convexHullPoints;
}