#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <utility>
#include <vector>

#include "include/ConvexHull/Chans.h"
#include "include/ConvexHull/DivideAndConquer.h"
#include "include/ConvexHull/GrahamScan.h"
#include "include/ConvexHull/MonotoneChain.h"
#include "include/ConvexHull/JarvisMarch.h"
#include "include/ConvexHull/Utils.h"
#include "include/Number.h"
#include "include/RGPPoint2D.h"

long int runConvexHullAlgorithm(std::string algorithmName, std::vector<RGPPoint2D *> points);

// Any pre-processing needed for the points before executing the convex hull algorithms
// Akl–Toussaint heuristic is implemented
// Sorting is implemented
std::vector< RGPPoint2D * > preProcessPoints(std::vector<RGPPoint2D *>& points, int flags);

// Any post-processing needed for the points on convex hull
// This is mainly used for getting a unique ordering of points for verifying
std::vector< RGPPoint2D * > postProcessPoints(std::vector<RGPPoint2D *>& points);

std::vector< RGPPoint2D * > aklToussaintHeuristic(std::vector < RGPPoint2D * >& points);
std::vector< RGPPoint2D * > readPointsDataFile(std::string filename);

// Prints the vector of points
void printPoints(std::vector<RGPPoint2D *> points);

int main(int argc, char** argv)
{

  // Simple test 1
  std::vector< RGPPoint2D * > points;
  std::vector< std::pair < std::string, std::string > > xs_ys_1{{"3", "0"}, {"0", "1"}, {"1", "2"}, {"6", "2"}, {"4", "3"}, {"0", "4"}, {"2", "5"}, {"5", "5"}};

  for (int i = 0; i < (int)xs_ys_1.size(); i++)
  {
    Number x(xs_ys_1[i].first);
    Number y(xs_ys_1[i].second);
    RGPPoint2D *p = new RGPPoint2D(x, y);
    points.push_back(p);
  }

  runConvexHullAlgorithm("MonotoneChain", points);
  runConvexHullAlgorithm("DivideAndConquer", points);
  runConvexHullAlgorithm("JarvisMarch", points);
  runConvexHullAlgorithm("GrahamScan", points);
  runConvexHullAlgorithm("Chans", points);

  if (argc == 3)
  {
    // first level key stores algo
    // second level key stores data pattern
    // vector is k
    // vector is timings for n
    int k = atoi(argv[1]);
    int n = atoi(argv[2]);
    std::cout << "K: " << k << " N: " << n << std::endl;
    std::vector < std::string > patterns{"straight", "horizontal", "vertical"};
    std::vector < std::string > algorithms{"MonotoneChain", "DivideAndConquer", "JarvisMarch", "GrahamScan", "Chans"};
    std::string ext = ".txt";

    long int timings[(int)algorithms.size()][(int)patterns.size()][k][n] = {0};
    
    for (int a = 0; a < (int)algorithms.size(); a++)
    {
      std::vector < std::vector < long int > > timingsForAs;
      for (int p = 0; p < (int)patterns.size(); p++)
      {
        std::vector < std::vector < long int > > timingsForKs;
        for (int i = 0; i < k; i++)
        {
          std::vector < long int > times;
          for (int j = 10; j <= n; j *= 10)
          {
            std::vector < RGPPoint2D * > points = readPointsDataFile("data/" + patterns[p] + "_" + std::to_string(i) + "_" + std::to_string(j) + ext);
            long int duration = runConvexHullAlgorithm(algorithms[a], points);
            timings[a][p][i][j] = duration;
          }
        }
      }
    }

    for (int a = 0; a < (int)algorithms.size(); a++)
    {
      std::cout << algorithms[a] << std::endl;
      for (int p = 0; p < (int)patterns.size(); p++)
      {
        std::cout << patterns[p] << std::endl;
        for (int i = 0; i < k; i++)
        {
          for (int j = 10; j <= n; j *= 10)
          {
            std::cout << timings[a][p][i][j] << " ";
          }

          std::cout << "\n";
        }

        std::cout << "\n";
      }
    }
  }

  return 0;
}

long int runConvexHullAlgorithm(std::string algorithmName, std::vector<RGPPoint2D *> points)
{
  std::cout << "==================================================" << std::endl;
  std::cout << "Algorithm: " << algorithmName << std::endl;
  std::cout << "--------------------------------------------------\n\n";

  for (int i = 0; i < 3; i++)
  {
    std::vector<RGPPoint2D *> processedPoints;
    processedPoints = preProcessPoints(points, i);
    
    // Executing the algorithm and calculating time
    auto startTime = std::chrono::high_resolution_clock::now();
    std::vector<RGPPoint2D *> convexHull;
    
    if (algorithmName == "MonotoneChain")
    {
      convexHull = getMonotone(points);
    }
    else if (algorithmName == "DivideAndConquer")
    {
      convexHull = getConvexHullDivideAndConquer(points);
    }
    else if (algorithmName == "JarvisMarch")
    {
      convexHull = getConvexHullJarvisMarch(points);
    }
    else if (algorithmName == "GrahamScan")
    {
      convexHull = getGraham(points);
    }
    else if (algorithmName == "Chans")
    {
      convexHull = getConvexHullChans(points);
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    std::cout << "Time taken: " << duration << " (microseconds)" << std::endl;

    std::cout << "Convex hull: ";
    printPoints(convexHull);

    if (i == 0)
    {
      std::cout << "--------------------------------------------------";
    }

    std::cout << "\n\n";
    return duration;    
  }
}

void printPoints(std::vector<RGPPoint2D *> points)
{
  for (int i = 0; i < (int)points.size(); i++)
  {
    std::cout << "(" << points[i]->x << "," << points[i]->y << ") ";
  }

  std::cout << std::endl;
}

std::vector<RGPPoint2D *> preProcessPoints(std::vector<RGPPoint2D *>& points, int flags)
{
  std::vector< RGPPoint2D * > processedPoints;
  if (flags & 1)
  {
    processedPoints = aklToussaintHeuristic(points);
  }
  else
  {
    processedPoints = points;
  }

  if (flags & 2)
  {
    std::sort(processedPoints.begin(), processedPoints.end(), pointsComparator());
  }
  
  return processedPoints;
}

std::vector< RGPPoint2D * > aklToussaintHeuristic(std::vector < RGPPoint2D * >& points)
{
  int pointsSize = (int)points.size();
  RGPPoint2D *bottomPoint = NULL, *rightPoint = NULL, *topPoint = NULL, *leftPoint = NULL;
  std::vector<RGPPoint2D *> filteredPoints;
  for (int i = 0; i < pointsSize; i++)
  {
    if (leftPoint == NULL || points[i]->x < leftPoint->x)
    {
      leftPoint = points[i];
    }

    if (rightPoint == NULL || points[i]->x > rightPoint->x)
    {
      rightPoint = points[i];
    }

    if (bottomPoint == NULL || points[i]->y < bottomPoint->y)
    {
      bottomPoint = points[i];
    }

    if (topPoint == NULL || points[i]->y > topPoint->y)
    {
      topPoint = points[i];
    }
  }

  filteredPoints.push_back(topPoint);
  filteredPoints.push_back(bottomPoint);

  if (leftPoint != topPoint && leftPoint != bottomPoint)
    filteredPoints.push_back(leftPoint);

  if (rightPoint != topPoint && rightPoint != bottomPoint)
    filteredPoints.push_back(rightPoint);

  Number zero("0");
  for (int i = 0; i < pointsSize; i++)
  {
    RGPPoint2D *p = points[i];

    if (p == topPoint)
      continue;
    if (p == bottomPoint)
      continue;
    if (p == rightPoint)
      continue;
    if (p == leftPoint)
      continue;

    Number d = (topPoint->x - leftPoint->x) * (p->y - leftPoint->y) - (topPoint->y - leftPoint->y) * (p->x - leftPoint->x);
    if (d > zero)
    {
      filteredPoints.push_back(p);
      continue;
    }

    d = (rightPoint->x - topPoint->x) * (p->y - topPoint->y) - (rightPoint->y - topPoint->y) * (p->x - topPoint->x);
    if (d > zero)
    {
      filteredPoints.push_back(p);
      continue;
    }

    d = (bottomPoint->x - rightPoint->x) * (p->y - rightPoint->y) - (bottomPoint->y - rightPoint->y) * (p->x - rightPoint->x);
    if (d > zero)
    {
      filteredPoints.push_back(p);
      continue;
    }

    d = (leftPoint->x - bottomPoint->x) * (p->y - bottomPoint->y) - (leftPoint->y - bottomPoint->y) * (p->x - bottomPoint->x);
    if (d > zero)
    {
      filteredPoints.push_back(p);
      continue;
    }
  }

  return filteredPoints;
}

std::vector< RGPPoint2D * > postProcessPoints(std::vector<RGPPoint2D *>& points)
{
  sort(points.begin(), points.end(), pointsComparator());
}

std::vector< RGPPoint2D * > readPointsDataFile(std::string filename)
{
  std::vector < RGPPoint2D * > points;

  std::cout << "Reading " << filename << std::endl;
  std::ifstream file(filename);
  
  std::string xy, x, y;
  while(std::getline(file, xy))
  {
    std::istringstream ss(xy);
    std::string token;

    std::getline(ss, x, ',');
    std::getline(ss, y, '\n');

    // std::cout << x << " " << y << std::endl;
    Number nx(x);
    Number ny(y);
    RGPPoint2D *p = new RGPPoint2D(nx, ny);
    points.push_back(p);
  }

  file.close();

  std::cout << "Read " << points.size() << " points." << std::endl;
  return points;
}