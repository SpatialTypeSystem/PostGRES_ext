#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

#include "../../include/RGPPoint2D.h"
#include "../../include/ConvexHull/Utils.h"

void FindHull(std::vector<RGPPoint2D *> &S_pointset, RGPPoint2D *point1, RGPPoint2D *point2, std::vector<RGPPoint2D *> &hullpoints);
std::vector<RGPPoint2D *> getConvexHullQuickHullInternal(std::vector<RGPPoint2D *> &points);

std::vector<RGPPoint2D *> getConvexHullQuickHull(std::vector<RGPPoint2D *> points)
{
  std::vector<RGPPoint2D *> pointsCopy(points);
  std::vector<RGPPoint2D *> convexHullPoints = getConvexHullQuickHullInternal(pointsCopy);
  return convexHullPoints;
}

Number perpendicular_distance_from_line(RGPPoint2D *point1, RGPPoint2D *point2, RGPPoint2D *general_point)
{
  Number zero("0");
  Number minusOne("-1");
  Number val = (general_point->x) * (point2->y - point1->y) - (general_point->y) * (point2->x - point1->x);
  if (val < zero)
  {
    val = val * minusOne;
  }

  return val;
}

/*
 * Intenal method to compute convex hull using Jarvis March method
 */
std::vector<RGPPoint2D *> getConvexHullQuickHullInternal(std::vector<RGPPoint2D *> &points)
{
  std::vector<RGPPoint2D *> convexHull;
  // There must be at least 3 points
  int n = points.size();
  if (n < 4)
  {
    convexHull = getConvexHullBruteForce(points);
    return convexHull;
  }

  // Find the leftmost point and among leftmost point the bottom most point
  int l = 0;
  for (int i = 1; i < n; i++)
  {
    if (points[i]->x < points[l]->x)
      l = i;
    else if ((points[i]->x == points[l]->x) && (points[i]->y < points[l]->y))
      l = i;
  }

  // Find the rightmost point and among rightmost point the top most point
  int r = 0;
  for (int i = 1; i < n; i++)
  {
    if (points[i]->x > points[r]->x)
      r = i;
    else if ((points[i]->x == points[r]->x) && (points[i]->y > points[r]->y))
      r = i;
  }

  convexHull.push_back(points[l]);
  convexHull.push_back(points[r]);

  std::vector<RGPPoint2D *> S1;
  std::vector<RGPPoint2D *> S2;

  int i = 0;
  while (i < n)
  {
    if (i != l && i != r)
    {
      int side_val;
      side_val = getPositionOfPoint(points[l], points[r], points[i]);

      if (side_val == 1)
      {
        S1.push_back(points[i]);
      }
      else
      {
        S2.push_back(points[i]);
      }
    }

    i = i + 1;
  }

  FindHull(S1, points[l], points[r], convexHull);
  FindHull(S2, points[l], points[r], convexHull);

  return convexHull;
}

void FindHull(std::vector<RGPPoint2D *> &S_pointset, RGPPoint2D *point1, RGPPoint2D *point2, std::vector<RGPPoint2D *> &hullpoints)
{
  if (S_pointset.empty())
  {
    return;
  }

  int n = S_pointset.size();
  int farthest = 0;
  Number max_distance("0");
  Number distance;
  RGPPoint2D *farthest_point = S_pointset[0];
  for (int i = 0; i < n; i++)
  {
    // calculate the farthest point using perpendicular distance as argument
    distance = perpendicular_distance_from_line(point1, point2, S_pointset[i]);
    if (distance > max_distance)
    {
      max_distance = distance;
      farthest = i;
    }
    else if (distance == max_distance)
    {
      int temp;
      if (S_pointset[farthest]->x > S_pointset[i]->x)
      {
        farthest = i;
      }
    }
  }

  Number zero("0");
  if (max_distance == zero) {
    return;
  }

  farthest_point = S_pointset[farthest];
  hullpoints.push_back(farthest_point);

  std::vector<RGPPoint2D *> S1;
  std::vector<RGPPoint2D *> S2;
  int i = 0;

  while (i < n)
  {
    int side_val;
    side_val = getPositionOfPoint(point1, farthest_point, point2);
    if ((side_val == 1 && getPositionOfPoint(point1, farthest_point, S_pointset[i]) == -1) ||
      (side_val == -1 && getPositionOfPoint(point1, farthest_point, S_pointset[i]) == 1))
    {
      S1.push_back(S_pointset[i]);
    }
    else
    {
      side_val = getPositionOfPoint(point2, farthest_point, point1);
      if ((side_val == 1 && getPositionOfPoint(point2, farthest_point, S_pointset[i]) == -1) ||
        (side_val == -1 && getPositionOfPoint(point2, farthest_point, S_pointset[i]) == 1))
      {
        S2.push_back(S_pointset[i]);
      }
    }

    i = i + 1;
  }

  FindHull(S1, point1, farthest_point, hullpoints);
  FindHull(S2, farthest_point, point2, hullpoints);
}