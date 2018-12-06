#include <iostream> 
#include <stack> 
#include <stdlib.h> 
#include <algorithm>
#include <vector>

#include "../../include/RGPPoint2D.h"
#include "../../include/ConvexHull/Utils.h"

using namespace std; 

// A utility function to find next to top in a stack 
RGPPoint2D* nextToTop(stack<RGPPoint2D*> &S) 
{ 
    RGPPoint2D* p = S.top(); 
    S.pop(); 
    RGPPoint2D* res = S.top(); 
    S.push(p); 
    return res; 
} 
  
// A utility function to swap two RGPPoint2Ds 
void swap(vector < RGPPoint2D* > &RGPPoint2Ds, int a, int b) 
{ 
    if (a == b)
        return;

    RGPPoint2D* temp = RGPPoint2Ds[a]; 
    RGPPoint2Ds[a] = RGPPoint2Ds[b];
    RGPPoint2Ds[b] = temp;
} 
  
// A utility function to return square of distance 
// between p1 and p2 
Number distSq(const RGPPoint2D* p1, const RGPPoint2D* p2) 
{ 
    return (p1->x - p2->x)*(p1->x - p2->x) + 
          (p1->y - p2->y)*(p1->y - p2->y); 
} 

struct pointsComparatorGraham
{
    pointsComparatorGraham(RGPPoint2D** p0) { 
        cout << (*p0)->x << " " << (*p0)->y << endl;
        this->p0 = p0;
    }

    inline bool operator() (const RGPPoint2D* p1, const RGPPoint2D* p2)
    {
        int o = getPositionOfPoint(*p0, p1, p2); 
        if (o == 0) 
            return (distSq(*p0, p2) >= distSq(*p0, p1))? false : true; 
        
        return o < 0 ? true : false; 
    }

    RGPPoint2D** p0;
};

/*
 * Prints the vector of points
 */
void printPoints1(std::vector < RGPPoint2D* > points) {
    for (int i = 0; i < (int)points.size(); i++) {
        std::cout << "(" << points[i]->x << "," << points[i]->y << ") ";
    }

    std::cout << std::endl;
}

// PrNumbers convex hull of a set of n RGPPoint2Ds. 
std::vector < RGPPoint2D* > getGraham(std::vector < RGPPoint2D* > RGPPoint2DsOriginal) 
{
   std::vector < RGPPoint2D* > RGPPoint2Ds(RGPPoint2DsOriginal);
//    printPoints1(RGPPoint2Ds);
//    printPoints1(RGPPoint2DsOriginal);

   int n = RGPPoint2Ds.size();
   // Find the bottommost RGPPoint2D 
   Number ymin = RGPPoint2Ds[0]->y;
   int min = 0; 
   for (int i = 1; i < n; i++) 
   {   
     // Pick the bottom-most or chose the left 
     // most RGPPoint2D in case of tie 
     if ((RGPPoint2Ds[i]->y < ymin) ||
            (RGPPoint2Ds[i]->y == ymin && RGPPoint2Ds[i]->x < RGPPoint2Ds[min]->x)) 
     {
        ymin = RGPPoint2Ds[i]->y;
        min = i; 
     }
   } 
  
   // Place the bottom-most RGPPoint2D at first position 
   swap(RGPPoint2Ds, 0, min); 
  
   // Sort n-1 RGPPoint2Ds with respect to the first RGPPoint2D. 
   // A RGPPoint2D p1 comes before p2 in sorted ouput if p2 
   // has larger polar angle (in counterclockwise 
   // direction) than p1 
   sort(RGPPoint2Ds.begin() + 1, RGPPoint2Ds.end(), pointsComparatorGraham(&RGPPoint2Ds[0])); 

   cout << "After sorting -- > ";
   printPoints1(RGPPoint2Ds);

   // If two or more RGPPoint2Ds make same angle with p0, 
   // Remove all but the one that is farthest from p0 
   // Remember that, in above sorting, our criteria was 
   // to keep the farthest RGPPoint2D at the end when more than 
   // one RGPPoint2Ds have same angle. 
   int m = 1; // Initialize size of modified array 
   for (int i=1; i<n; i++) 
   { 
       // Keep removing i while angle of i and i+1 is same 
       // with respect to p0 
       while (i < n-1 && getPositionOfPoint(RGPPoint2Ds[0], RGPPoint2Ds[i], 
                                    RGPPoint2Ds[i+1]) == 0)
        {
          cout << RGPPoint2Ds[i]->x << " " << RGPPoint2Ds[i]->y << endl;
          cout << RGPPoint2Ds[i + 1]->x << " " << RGPPoint2Ds[i + 1]->y << endl;
          i++; 
        }
  
  
       RGPPoint2Ds[m] = RGPPoint2Ds[i]; 
       m++;  // Update size of modified array 
   } 
  
   while (RGPPoint2Ds.size() > m)
     RGPPoint2Ds.pop_back();

   std::vector < RGPPoint2D* > convexHull;
   // If modified array of RGPPoint2Ds has less than 3 RGPPoint2Ds, 
   // convex hull is not possible 
   if (m < 3) return convexHull; 
  
   // Create an empty stack and push first three RGPPoint2Ds 
   // to it. 
   stack<RGPPoint2D*> S; 
   S.push(RGPPoint2Ds[0]); 
   S.push(RGPPoint2Ds[1]); 
   S.push(RGPPoint2Ds[2]); 
  
   // Process remaining n-3 RGPPoint2Ds 
   for (int i = 3; i < m; i++) 
   { 
      // Keep removing top while the angle formed by 
      // RGPPoint2Ds next-to-top, top, and RGPPoint2Ds[i] makes 
      // a non-left turn 
      while (getPositionOfPoint(nextToTop(S), S.top(), RGPPoint2Ds[i]) != -1) 
         S.pop(); 
      S.push(RGPPoint2Ds[i]); 
   } 
  
   // Now stack has the output RGPPoint2Ds, prNumber contents of stack 
   while (!S.empty()) 
   { 
       RGPPoint2D* p = S.top();
       convexHull.push_back(p);
       S.pop(); 
   } 

    cout << "Before exiting --> " << endl;
   printPoints1(RGPPoint2DsOriginal);
   printPoints1(RGPPoint2Ds); 
   printPoints1(convexHull);
   cout << "Exit" << endl;
   return convexHull;
} 
  
/*// Driver program to test above functions 
Number main() 
{ 
    RGPPoint2D RGPPoint2Ds[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, 
                      {0, 0}, {1, 2}, {3, 1}, {3, 3}}; 
    Number n = sizeof(RGPPoint2Ds)/sizeof(RGPPoint2Ds[0]); 
    convexHull(RGPPoint2Ds, n); 
    return 0; 
} 
*/