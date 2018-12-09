#include "iostream"

// Including all headers to test
#include "include/RGPHalfSegment2D.h"
#include "include/RGPOperations2D.h"
#include "include/RGPPoint2D.h"
#include "include/RGPSegment2D.h"
#include "include/Region2D.h"
#include "include/Point2D.h"
#include "include/Region2DImpl.h"

int main(void)
{
  Number n;
  Number b("5");
  //std::cout<<b;
 // Point2D p("avc");


 //RGPPoint2D a(Number("2"),Number("3"));
//std::cout<< a.x;



/*  int i=0;
  while(i<3){
	 RGPPoint2D a(b,b);
	 std::cout<< a.x << " " << a.y;
	 i++;
  }
*/
	std::string str = "[WCR((0 0,3.2 0,3 3.4,0 3,0 0),(1 2,2 2,1 2),(1 1,2 2,1 1))]";
	
	//Number("12/24");

	Point2D poi("((1,2),(2,3))");
	std::cout<<poi.getPointString();

	RGPPoint2D p(Number("5"),Number("6"));
	RGPPoint2D p1(Number("4"),Number("8"));
	RGPSegment2D s(p,p1);
	std::cout<<s<<std::endl;
	RGPAnnotatedHalfSegment2D seg(s,p,true);

	Region2DImpl r(str);
	RGPPoint2D pt(Number("31"),Number("24"));
	//std::cout<<pt;

  std::cout << "All includes successfull!" << std::endl;
  return 0;
}
