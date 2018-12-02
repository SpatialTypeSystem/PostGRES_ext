#include <iostream> 
#include <stack> 
#include <stdlib.h> 
#include <algorithm>
#include <vector>

#include "../../include/RGPPoint2D.h"
using namespace std; 
  
// A globle RGPPoint2D needed for  sorting RGPPoint2Ds with reference 
// to  the first RGPPoint2D Used in compare function of qsort() 
RGPPoint2D* p0; 
  
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
Number swap(RGPPoint2D* p1, RGPPoint2D* p2) 
{ 
    RGPPoint2D* temp = p1; 
    p1 = p2; 
    p2 = temp; 
} 
  
// A utility function to return square of distance 
// between p1 and p2 
Number distSq(RGPPoint2D* p1, RGPPoint2D* p2) 
{ 
    return (p1->x - p2->x)*(p1->x - p2->x) + 
          (p1->y - p2->y)*(p1->y - p2->y); 
} 
  
// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(RGPPoint2D* p, RGPPoint2D* q, RGPPoint2D* r) 
{ 
    Number val = (q->y - p->y) * (r->x - q->x) - 
              (q->x - p->x) * (r->y - q->y); 
  
    Number zero("0");
    if (val == zero) return 0;  // colinear 
    return (val > zero)? 1: 2; // clock or counterclock wise 
} 
  
// A function used by library function qsort() to sort an array of 
// RGPPoint2Ds with respect to the first RGPPoint2D 
int compare(const void *vp1, const void *vp2) 
{ 
   RGPPoint2D *p1 = (RGPPoint2D *)vp1; 
   RGPPoint2D *p2 = (RGPPoint2D *)vp2; 
  
   // Find orientation 
   int o = orientation(p0, p1, p2); 
   if (o == 0) 
     return (distSq(p0, p2) >= distSq(p0, p1))? -1 : 1; 
  
   return (o == 2)? -1: 1; 
} 
  
// PrNumbers convex hull of a set of n RGPPoint2Ds. 
std::vector < RGPPoint2D* > getGraham(std::vector < RGPPoint2D* > RGPPoint2Ds) 
{
   int n = RGPPoint2Ds.size();
   // Find the bottommost RGPPoint2D 
   Number ymin = RGPPoint2Ds[0]->y;
   int min = 0; 
   for (int i = 1; i < n; i++) 
   { 
     Number y = RGPPoint2Ds[i]->y; 
  
     // Pick the bottom-most or chose the left 
     // most RGPPoint2D in case of tie 
     if ((y < ymin) || (ymin == y && 
         RGPPoint2Ds[i]->x < RGPPoint2Ds[min]->x)) 
        ymin = RGPPoint2Ds[i]->y, min = i; 
   } 
  
   // Place the bottom-most RGPPoint2D at first position 
   swap(RGPPoint2Ds[0], RGPPoint2Ds[min]); 
  
   // Sort n-1 RGPPoint2Ds with respect to the first RGPPoint2D. 
   // A RGPPoint2D p1 comes before p2 in sorted ouput if p2 
   // has larger polar angle (in counterclockwise 
   // direction) than p1 
   p0 = RGPPoint2Ds[0]; 
   qsort(RGPPoint2Ds[1], n-1, sizeof(RGPPoint2D), compare); 
  
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
       while (i < n-1 && orientation(p0, RGPPoint2Ds[i], 
                                    RGPPoint2Ds[i+1]) == 0) 
          i++; 
  
  
       RGPPoint2Ds[m] = RGPPoint2Ds[i]; 
       m++;  // Update size of modified array 
   } 
  
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
      while (orientation(nextToTop(S), S.top(), RGPPoint2Ds[i]) != 2) 
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