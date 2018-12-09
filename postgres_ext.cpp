#include "iostream"

// Including all headers to test
#include "include/RGPHalfSegment2D.h"
#include "include/RGPOperations2D.h"
#include "include/RGPPoint2D.h"
#include "include/RGPSegment2D.h"
#include "include/Region2D.h"
#include "include/Point2D.h"
#include "include/Region2DImpl.h"

#include "include/Point2DImpl.h"
#include "include/Line2DImpl.h"

int main(void)
{
	//adding through strings.
	std::string str = "((333.33,22.22),(12,6),(3,4),(9,7),(4,5))";
  	Point2DImpl x(str);
	std::string str2 = "((9,7),(333.33,22.22),(3,4),(4,5),(12,6))";
	Point2DImpl y(str2);

	//adding through strings when input format is not correct. Checked all other cases as well
	std::string str3 = "((333.3322.22),(4,5),(3,4),(4,5))";
	Point2DImpl z(str3);

	//method to print all the points in our object

	std::cout<<"All points in x are"<<std::endl;
	x.printAllPoints();
	std::cout<<std::endl;

	//checking operator !=
	std::cout<<"check if x!=y"<<std::endl;
	if(x!=y)
		std::cout<<"true"<<std::endl;
	else
		std::cout<<"false"<<std::endl;

	//checking operator ==
	std::cout<<"check if x==y"<<std::endl;
	if(x==y)
		std::cout<<"true"<<std::endl;
	else
		std::cout<<"false"<<std::endl;

	//check if the Point2D object is Empty
	bool empty = x.isEmptyPoint();
	std::cout<<"output after checking if empty is : "<<empty<<std::endl;

	//get the total number of points in the object
	std::cout<<"total number of points in x are : "<<x.getNumberOfPoints()<<std::endl;

	//working of Point2DImpl iterator. This covers all methods of iterator like end(), begin(), !=, ==, *
	std::cout<<"working of iterator and printing all the points in the vector"<<std::endl;
	for(Point2DImpl::iterator it = x.begin(); it!= x.end();++it)
		std::cout<<*it;
	std::cout<<std::endl;

	//creation of point and adding it to the Point2DImpl object
	RGPPoint2D pt(Number("31"),Number("22"));
	x.add(pt);
	//output after adding
	std::cout<<"object after adding point"<<std::endl;
	for(Point2DImpl::iterator it = x.begin(); it!= x.end();++it)
		std::cout<<*it;
	std::cout<<std::endl;

	//working of remove method for Point2DImpl object
	Point2DImpl::iterator it = x.begin();
	it++;
	it++;
	x.remove(it);
	std::cout<<"object after removing point"<<std::endl;
	for(Point2DImpl::iterator it = x.begin(); it!= x.end();++it)
		std::cout<<*it;
	std::cout<<std::endl;

	//working of update method for Point2DImpl
	Point2DImpl::iterator it1 = x.begin();
	it1++;
	RGPPoint2D pt1(Number("23"),Number("2"));
	x.update(it1,pt1);
	std::cout<<"object after updating point"<<std::endl;
	for(Point2DImpl::iterator it = x.begin(); it!= x.end();++it)
		std::cout<<*it;
	std::cout<<std::endl;	
	
	//working of = operator for Point2DImpl
	x=y;
	//x was updated multiple times, now it is equal to y
	std::cout<<"output after doing ="<<std::endl;
	for(Point2DImpl::iterator it = x.begin(); it!= x.end();++it)
		std::cout<<*it;
	std::cout<<std::endl;
	
	//working of [] in point2DImpl
	Point2DImpl t;
	t = y[2];
	Point2DImpl::iterator it2 = t.begin();
	std::cout<<"index works and the point added was "<<*it2<<std::endl;

	//code for getting the bounding box of the set of points
	Line2DImpl bx;
	bx = y.getBoundingBox();
	std::cout<<"segment in the bounding box"<<std::endl;
	for(Line2DImpl::iterator it = bx.begin(); it!= bx.end();it++)
		std::cout<<(*it).segment;

	std::cout<<std::endl;

	std::string regStr = "[WCR((0 0,5 0,5 5,0 5,0 0),(1 1,3 1,3 3,1 3,1 1))]";
	std::cout<<"region to be added: "<<regStr<<std::endl;
	Region2DImpl r(regStr);
	std::cout<<"area of the region: "<< r.area() <<std::endl;
	std::cout<<"number of faces in region: "<< r.getNumberOfFaces() <<std::endl;
	std::cout<<"number of holes in region: "<< r.getNumberOfHoles() <<std::endl;
	std::cout<<"is the region empty? "<< r.isEmptyRegion() <<std::endl;

	Region2DImpl::iteratorforFaces it3 = r.beginFaces();
	for(Region2DImpl::iteratorforFaces it = r.beginFaces(); it!= r.endFaces();it++)
	{
		std::vector<RGPAnnotatedHalfSegment2D> vec = *it;
		std::cout<<vec[0].segment;
	}
	std::cout<<"iterator works over the faces. Printing the points on first segment: "<<(*it3)[0].segment<<std::endl;

	Region2DImpl::iteratorforHoles it4 = r.beginHoles();
	for(Region2DImpl::iteratorforHoles it = r.beginHoles(); it!= r.endHoles();it++)
	{
		std::vector<RGPAnnotatedHalfSegment2D> vec = *it;
		std::cout<<vec[0].segment;
	}
	std::cout<<"iterator works over the Holes. Printing the points on first segment: "<<(*it4)[0].segment<<std::endl;
	std::cout<<"diagonal of the bounding box for the region: "<<r.getBoundingBox()<<std::endl;

	std::string invalidRegString = "[WCR((0 0,1 1,2 2))]";
	try
	{
		std::cout<< "Trying to construct an invalid/illegal region: " << std::endl;
		Region2DImpl reg(invalidRegString);
	}
	catch (const std::exception &exc)
	{
		std::cerr << "Exception caught while creating region: " <<exc.what() << std::endl;
	}
	
	std::cout << "All successfull!" << std::endl;
	return 0;
}
