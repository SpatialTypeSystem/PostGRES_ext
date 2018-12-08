#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <utility>
#include <unordered_set>
#include <vector>

#include "include/ConvexHull/Chans.h"
#include "include/ConvexHull/DivideAndConquer.h"
#include "include/ConvexHull/GrahamScan.h"
#include "include/ConvexHull/MonotoneChain.h"
#include "include/ConvexHull/JarvisMarch.h"
#include "include/ConvexHull/QuickHull.h"
#include "include/ConvexHull/Utils.h"
#include "include/Number.h"
#include "include/RGPPoint2D.h"

long int runConvexHullAlgorithm(std::string algorithmName, std::vector<RGPPoint2D *> points, int mode, std::string filename, bool verbose = false);

// Any pre-processing needed for the points before executing the convex hull algorithms
// Akl–Toussaint heuristic is implemented
// Sorting is implemented
std::vector<RGPPoint2D *> preProcessPoints(std::vector<RGPPoint2D *> &points, int flags);

// Any post-processing needed for the points on convex hull
// This is mainly used for getting a unique ordering of points for verifying
void postProcessPoints(std::vector<RGPPoint2D *> &points);

std::vector<RGPPoint2D *> aklToussaintHeuristic(std::vector<RGPPoint2D *> &points);
std::vector<RGPPoint2D *> readPointsDataFile(std::string filename);

// Prints the vector of points
void printPoints(std::vector<RGPPoint2D *> points);

void simpleTest1() {
  // Simple test 1
  std::cout << "Simple test 1" << std::endl;
  std::vector<RGPPoint2D *> points;
  std::vector<std::pair<std::string, std::string>> xs_ys{{"3", "0"}, {"0", "1"}, {"1", "2"}, {"6", "2"}, {"4", "3"}, {"0", "4"}, {"2", "5"}, {"5", "5"}};

  for (int i = 0; i < (int)xs_ys.size(); i++)
  {
    Number x(xs_ys[i].first);
    Number y(xs_ys[i].second);
    RGPPoint2D *p = new RGPPoint2D(x, y);
    points.push_back(p);
  }

  for (int m = 0; m < 3; m++)
  {
    std::cout << "Mode " << m << std::endl;
    runConvexHullAlgorithm("MonotoneChain", points, m, "", true);
    runConvexHullAlgorithm("DivideAndConquer", points, m, "", true);
    runConvexHullAlgorithm("JarvisMarch", points, m, "", true);
    runConvexHullAlgorithm("GrahamScan", points, m, "", true);
    runConvexHullAlgorithm("Chans", points, m, "", true);
    runConvexHullAlgorithm("QuickHull", points, m, "", true);
  }
}

void simpleTest2() {
  // Simple test 2
  std::cout << "Simple test 2" << std::endl;
  std::vector<RGPPoint2D *> points;
  // std::vector<std::pair<std::string, std::string>> xs_ys{{"0", "0"}, {"1", "1"}, {"2", "2"}, {"4", "6"}, {"0", "3"}, {"3", "4"}};
  std::vector<std::pair<std::string, std::string>> xs_ys{{"0", "2"}, {"3", "2"}, {"5", "7"}, {"2", "9"}, {"8", "2"}, {"7", "9"}, {"6", "3"}, {"2", "1"}, {"3", "9"}, {"9", "1"}};
  for (int i = 0; i < (int)xs_ys.size(); i++)
  {
    Number x(xs_ys[i].first);
    Number y(xs_ys[i].second);
    RGPPoint2D *p = new RGPPoint2D(x, y);
    points.push_back(p);
  }

  for (int m = 0; m < 3; m++)
  {
    std::cout << "Mode " << m << std::endl;
    runConvexHullAlgorithm("MonotoneChain", points, m, "", true);
    runConvexHullAlgorithm("DivideAndConquer", points, m, "", true);
    runConvexHullAlgorithm("JarvisMarch", points, m, "", true);
    runConvexHullAlgorithm("GrahamScan", points, m, "", true);
    runConvexHullAlgorithm("Chans", points, m, "", true);
    runConvexHullAlgorithm("QuickHull", points, m, "", true);
  }
}

int main(int argc, char **argv)
{
  simpleTest1();
  simpleTest2();

  if (argc == 3)
  {
    // first level key stores algo
    // second level key stores data pattern
    // vector is k
    // vector is timings for n
    int k = atoi(argv[1]);
    int n = atoi(argv[2]);
    std::cout << "K: " << k << " N: " << n << std::endl;
    std::vector<std::string> patterns{"random"};
    // "straight", "horizontal", "vertical", 
    std::vector<std::string> algorithms{"JarvisMarch", "GrahamScan", "Chans", "QuickHull"};
    // MonotoneChain DivideAndConquer
    std::string ext = ".txt";

    // long int timings[(int)algorithms.size()][(int)patterns.size()][3][n][k];
    std::ofstream file;
    file.open("data/output/timings.txt");
    file << "Algorithm\tPointPattern\tFilteringMode\tn\tk\tTime(ms)\n";

    for (int a = 0; a < (int)algorithms.size(); a++)
    {
      for (int p = 0; p < (int)patterns.size(); p++)
      {
        for (int i = 10; i <= n; i *= 10)
        {
          for (int m = 0; m < 3; m++)
          {
            for (int j = 0; j < k; j++) // k
            {
              std::string inputFileName = "data/input/" + patterns[p] + "_" + std::to_string(i) + "_" + std::to_string(j) + ext;
              std::vector<RGPPoint2D *> points = readPointsDataFile(inputFileName);
              
              std::cout << algorithms[a] << std::endl;
              std::string outputFileName = "data/output/" + algorithms[a] + "_" + patterns[p] + "_" + std::to_string(m) + "_" + std::to_string(i) + "_" + std::to_string(j) + ext;
              long int result = runConvexHullAlgorithm(algorithms[a], points, m, outputFileName);
              
              std::cout << algorithms[a] << "\t" << patterns[p] << "\t" << m << "\t" << i << "\t" << j << "\t" << result << "\n";
              file << algorithms[a] << "\t" << patterns[p] << "\t" << m << "\t" << i << "\t" << j << "\t" << result << "\n";
              // opFile.close();
            }
          }
        }
      }
    }

    file.close();
  }

  return 0;
}

long int runConvexHullAlgorithm(std::string algorithmName, std::vector<RGPPoint2D *> points, int mode, std::string filename, bool verbose)
{
  if (verbose)
  {
    std::cout << "==================================================" << std::endl;
    std::cout << "Algorithm: " << algorithmName << std::endl;
    std::cout << "--------------------------------------------------\n";
  }

  std::vector<RGPPoint2D *> processedPoints;
  processedPoints = preProcessPoints(points, mode);

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
  else if (algorithmName == "QuickHull")
  {
    convexHull = getConvexHullQuickHull(points);
  }

  auto endTime = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
  postProcessPoints(convexHull);

  if (verbose)
  {
    std::cout << "Time taken: " << duration << " (milliseconds)" << std::endl;

    std::cout << "Convex hull: ";
    printPoints(convexHull);
  }

  if (filename.size() > 0)
  {
    std::ofstream f(filename);
    for (int i = 0; i < points.size(); i++)
      f << points[i]->x << "," << points[i]->y << ",0\n";
    
    for (int i = 0; i < convexHull.size(); i++)
      f << convexHull[i]->x << "," << convexHull[i]->y << ",1\n";
    
    f.close();
  }

  // std::pair<long int, std::vector<RGPPoint2D *>> result = std::make_pair(duration, postProcessPoints(convexHull));
  // if (i == 0)
  // {
  //   std::cout << "--------------------------------------------------";
  // }

  // std::cout << "\n\n";
  return duration;
}

void printPoints(std::vector<RGPPoint2D *> points)
{
  for (int i = 0; i < (int)points.size(); i++)
  {
    std::cout << "(" << points[i]->x << "," << points[i]->y << ") ";
  }

  std::cout << std::endl;
}

std::vector<RGPPoint2D *> preProcessPoints(std::vector<RGPPoint2D *> &points, int flags)
{
  // std::cout << "****** FLAG " << flags << std::endl;
  std::vector<RGPPoint2D *> processedPoints;
  // std::cout << points.size() << std::endl;
  if (flags & 1)
  {
    processedPoints = aklToussaintHeuristic(points);
    std::cout << "Reduced " << points.size() << " to " << processedPoints.size() << std::endl;
  }
  else
  {
    processedPoints = points;
  }

  // std::cout << processedPoints.size() << std::endl;
  if (flags & 2)
  {
    std::sort(processedPoints.begin(), processedPoints.end(), pointsComparator());
  }

  return processedPoints;
}

std::vector<RGPPoint2D *> aklToussaintHeuristic(std::vector<RGPPoint2D *> &points)
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

void postProcessPoints(std::vector<RGPPoint2D *> &points)
{
  sort(points.begin(), points.end(), pointsComparator());
}

std::vector<RGPPoint2D *> readPointsDataFile(std::string filename)
{
  std::vector<RGPPoint2D *> points;

  std::cout << "Reading " << filename << std::endl;
  std::ifstream file(filename);

  std::string xy, x, y;
  while (std::getline(file, xy))
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