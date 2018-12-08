#include <cmath>
#include <vector>

#include "../../include/ConvexHull/GrahamScan.h"
#include "../../include/ConvexHull/Utils.h"
#include "../../include/RGPPoint2D.h"

std::pair<int, int> extremeHullPointPair(std::vector<std::vector<RGPPoint2D *>> &hulls)
{
  int h = 0, p = 0;
  for (int i = 0; i < hulls.size(); ++i)
  {
    int min_index = 0;
    Number min_x = hulls[i][0]->x, min_y = hulls[i][0]->y;
    for (int j = 1; j < hulls[i].size(); ++j)
    {
      if (hulls[i][j]->x < min_x ||
          (hulls[i][j]->x == min_x && hulls[i][j]->y < min_y))
      {
        min_x = hulls[i][j]->x;
        min_y = hulls[i][j]->y;
        min_index = j;
      }
    }

    if (hulls[i][min_index]->x < hulls[h][p]->x ||
        (hulls[i][min_index]->x == hulls[h][p]->x && hulls[i][min_index]->y < hulls[h][p]->y))
    {
      h = i;
      p = min_index;
    }
  }
  return std::make_pair(h, p);
}

int getTangent(std::vector<RGPPoint2D *> &v, RGPPoint2D *p)
{
  int l = 0;
  int r = v.size() - 1;
  int l_before = getPositionOfPoint(p, v[0], v[v.size() - 1]);
  int l_after = getPositionOfPoint(p, v[0], v[(l + 1) % (int)v.size()]);
  while (l < r)
  {
    int c = ((l + r) >> 1);
    int c_before = getPositionOfPoint(p, v[c], v[c == 0 ? (v.size() - 1) : (c - 1)]);
    int c_after = getPositionOfPoint(p, v[c], v[(c + 1) % (int)v.size()]);
    int c_side = getPositionOfPoint(p, v[l], v[c]);

    if (c_before != -1 and c_after != -1)
      return c;
    else if ((c_side == 1) and (l_after == -1 or l_before == l_after) or (c_side == -1 and c_before == -1))
      r = c;
    else
      l = c + 1;

    l_before = -c_after;
    l_after = getPositionOfPoint(p, v[l], v[(l + 1) % (int)v.size()]);
  }

  return l;
}

std::pair<int, int> nextHullPointPair(std::vector<std::vector<RGPPoint2D *>> &hulls, std::pair<int, int> lpoint)
{
  RGPPoint2D *p = hulls[lpoint.first][lpoint.second];
  std::pair<int, int> next = std::make_pair(lpoint.first, (lpoint.second + 1) % hulls[lpoint.first].size());
  for (int h = 0; h < hulls.size(); h++)
  {
    if (h != lpoint.first)
    {
      int s = getTangent(hulls[h], p);
      RGPPoint2D *q = hulls[next.first][next.second];
      RGPPoint2D *r = hulls[h][s];
      int t = getPositionOfPoint(p, q, r);
      if (t == -1 || (t == 0) && distanceSquare(p, r) > distanceSquare(p, q))
        next = std::make_pair(h, s);
    }
  }

  // std::cout << "nextHullPointPair" << std::endl;
  return next;
}

std::vector<RGPPoint2D *> mergeHulls(std::vector<std::vector<RGPPoint2D *>> &hulls, int m, bool &isCompleteHullObtained)
{
  std::vector<RGPPoint2D *> convexHull;

  std::vector<std::pair<int, int>> hull;
  hull.push_back(extremeHullPointPair(hulls));
  // std::cout << "|| " << hulls[hull[0].first][hull[0].second]->x << " " << hulls[hull[0].first][hull[0].second]->y << std::endl;
  for (int i = 0; i < m; ++i)
  {
    // std::cout << "mergeHulls" << std::endl;
    std::pair<int, int> p = nextHullPointPair(hulls, hull[hull.size() - 1]);
    // std::cout << p.first << " " << p.second << std::endl;
    std::vector<RGPPoint2D *> output;
    if (p == hull[0])
    {
      // std::cout << hull[0].first << " **** " << hull[0].second << " " << hull.size() << std::endl;
      for (int j = 0; j < hull.size(); ++j)
      {
        output.push_back(hulls[hull[j].first][hull[j].second]);
      }

      isCompleteHullObtained = true;
      return output;
    }
    hull.push_back(p);
  }

  isCompleteHullObtained = false;
  return convexHull;
}

std::vector<std::vector<RGPPoint2D *>> getSubHulls(std::vector<RGPPoint2D *> &points, int m)
{
  std::vector<std::vector<RGPPoint2D *>> subHulls;
  int pointsSize = (int)points.size();

  std::vector<RGPPoint2D *> currentPoints;
  for (int i = 0; i < pointsSize; i++)
  {
    currentPoints.push_back(points[i]);

    if ((int)currentPoints.size() == m)
    {
      subHulls.push_back(getGraham(currentPoints));
      // if (subHulls[subHulls.size() - 1].size() > 1)
      // subHulls[subHulls.size() - 1].push_back(subHulls[subHulls.size() - 1][0]);
      // printPoints2(subHulls[subHulls.size() - 1]);
      currentPoints.clear();
    }
  }

  if ((int)currentPoints.size() > 0)
  {
    subHulls.push_back(getGraham(currentPoints));
    // if (subHulls[subHulls.size() - 1].size() > 1)
    // subHulls[subHulls.size() - 1].push_back(subHulls[subHulls.size() - 1][0]);
    // printPoints2(subHulls[subHulls.size() - 1]);
    currentPoints.clear();
  }

  return subHulls;
}

std::vector<RGPPoint2D *> getConvexHullChansInternal(std::vector<RGPPoint2D *> &points)
{
  int t = 1;
  int m;
  bool isCompleteHullObtained = false;
  std::vector<RGPPoint2D *> convexHullPoints;
  std::vector<std::vector<RGPPoint2D *>> subHulls;

  do
  {
    m = pow(2, pow(2, t));
    // std::cout << m << " " << isCompleteHullObtained << std::endl;
    subHulls = getSubHulls(points, m);
    convexHullPoints = mergeHulls(subHulls, m, isCompleteHullObtained);
    t++;
  } while (!isCompleteHullObtained);

  return convexHullPoints;
}

/*
 * Computes convex hull using divide and conquer method
 */
std::vector<RGPPoint2D *> getConvexHullChans(std::vector<RGPPoint2D *> &points)
{
  std::vector<RGPPoint2D *> pointsCopy(points);

  std::vector<RGPPoint2D *> convexHullPoints = getConvexHullChansInternal(pointsCopy);
  return convexHullPoints;
}