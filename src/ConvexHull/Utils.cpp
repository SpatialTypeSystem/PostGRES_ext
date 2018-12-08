#include <algorithm>
#include <vector>

#include "../../include/ConvexHull/Utils.h"
#include "../../include/RGPPoint2D.h"

/*
 * +1 : if p3 is left of line (p1, p2)
 * 0 : if p3 is on line (p1, p2)
 * -1 : if p3 is right of line (p1, p2)
 */
int getPositionOfPoint(const RGPPoint2D *p1, const RGPPoint2D *p2, const RGPPoint2D *p3)
{
  Number one("1.0");
  Number minusOne("-1.0");

  // Calculates determinant of the below matrix
  // │x1  y1  1│
  // │x2  y2  1│
  // │x3  y3  1│
  Number position(p1->x * p2->y - p1->x * p3->y - p1->y * p2->x + p1->y * p3->x + p2->x * p3->y - p3->x * p2->y);

  // std::cout << "position " << position << std::endl;
  if (position >= one)
    return 1;
  if (position <= minusOne)
    return -1;

  return 0;
}

/*
 * A utility function to return square of distance 
 * between p1 and p2
 */
Number distanceSquare(const RGPPoint2D *p1, const RGPPoint2D *p2)
{
  return (p1->x - p2->x) * (p1->x - p2->x) +
         (p1->y - p2->y) * (p1->y - p2->y);
}

/*
 * Computes convex hull of points in
 * near constant time when number of points <= 3
 */
std::vector<RGPPoint2D *> getConvexHullBruteForce(std::vector<RGPPoint2D *> &points)
{
  int pointsSize = (int)points.size();
  std::vector<RGPPoint2D *> convexHull;

  if (pointsSize == 1)
  {
    convexHull.push_back(points[0]);
  }
  else if (pointsSize == 2)
  {
    if ((points[0]->x < points[1]->x) ||
        (points[0]->x == points[1]->x && points[0]->y < points[1]->y))
    {
      convexHull.push_back(points[0]);
      convexHull.push_back(points[1]);
    }
    else
    {
      convexHull.push_back(points[1]);
      convexHull.push_back(points[0]);
    }
  }
  else if (pointsSize == 3)
  {
    std::sort(points.begin(), points.end(), pointsComparator());
    int orientation = getPositionOfPoint(points[0], points[1], points[2]);
    if (orientation == 0)
    {
      convexHull.push_back(points[0]);
      convexHull.push_back(points[2]);
    }
    else if (orientation == -1)
    {
      convexHull.push_back(points[0]);
      convexHull.push_back(points[2]);
      convexHull.push_back(points[1]);
    }
    else
    {
      convexHull.push_back(points[0]);
      convexHull.push_back(points[1]);
      convexHull.push_back(points[2]);
    }
  }
  else
  {
    throw std::invalid_argument("Length of points vector too large!");
  }

  return convexHull;
}

// A utility function to swap two RGPPoint2Ds
void swap(std::vector<RGPPoint2D *> &RGPPoint2Ds, int a, int b)
{
  if (a == b)
  {
    return;
  }

  RGPPoint2D *temp = RGPPoint2Ds[a];
  RGPPoint2Ds[a] = RGPPoint2Ds[b];
  RGPPoint2Ds[b] = temp;
}