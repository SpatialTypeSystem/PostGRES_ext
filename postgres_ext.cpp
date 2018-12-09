#include "iostream"

// Including all headers to test
#include "include/RGPHalfSegment2D.h"
#include "include/RGPOperations2D.h"
#include "include/RGPPoint2D.h"
#include "include/RGPSegment2D.h"
#include "include/Region2D.h"
#include "include/Point2D.h"
#include "include/Region2DImpl.h"

#include "include/Point2D.h"
#include "include/Line2D.h"

void callLine();
int main(void)
{
	//For point2D
	std::cout<<"Point implementation from here : "<<std::endl;
	std::cout<<std::endl;
	
	//adding through strings.
	std::string str = "((333.33,22.22),(12,6),(3,4),(9,7),(4,5))";
  	Point2D x(str);
	std::string str2 = "((9,7),(333.33,22.22),(3,4),(4,5),(12,6))";
	Point2D y(str2);

	//adding through strings when input format is not correct. Checked all other cases as well
	std::string str3 = "((333.3322.22),(4,5),(3,4),(4,5))";
	Point2D z(str3);

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

	//working of Point2D iterator. This covers all methods of iterator like end(), begin(), !=, ==, *
	std::cout<<"working of iterator and printing all the points in the vector"<<std::endl;
	for(Point2D::iterator it = x.begin(); it!= x.end();++it)
		std::cout<<*it;
	std::cout<<std::endl;

	//creation of point and adding it to the Point2D object
	RGPPoint2D pt(Number("31"),Number("22"));
	x.add(pt);
	//output after adding
	std::cout<<"object after adding point"<<std::endl;
	for(Point2D::iterator it = x.begin(); it!= x.end();++it)
		std::cout<<*it;
	std::cout<<std::endl;

	//working of remove method for Point2D object
	Point2D::iterator it = x.begin();
	it++;
	it++;
	x.remove(it);
	std::cout<<"object after removing point"<<std::endl;
	for(Point2D::iterator it = x.begin(); it!= x.end();++it)
		std::cout<<*it;
	std::cout<<std::endl;

	//working of update method for Point2D
	Point2D::iterator it1 = x.begin();
	it1++;
	RGPPoint2D pt1(Number("23"),Number("2"));
	x.update(it1,pt1);
	std::cout<<"object after updating point"<<std::endl;
	for(Point2D::iterator it = x.begin(); it!= x.end();++it)
		std::cout<<*it;
	std::cout<<std::endl;	

	//code for getting the bounding box of the set of points
	RGPSegment2D bou = y.getBoundingBox();
	std::cout<<"segment in the bounding box"<<std::endl;
	std::cout<<bou;

	std::cout<<std::endl;

	//-------------------------------------------

	//Line2D
	std::cout<<std::endl;
	std::cout<<"Line implementation from here : "<<std::endl;
	std::cout<<std::endl;
	callLine();

	//-------------------------------------------

	//For Region2D
	std::cout<<std::endl;
	std::cout<<"Region implementation from here : "<<std::endl;
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

void callLine()
{
	//For Line2D

	
	//adding through strings.
	std::string str = "(((3,4),(2,2)),((6,2),(5,3)),((6,1),(7,9)),((8,4),(6,6)))";
	Line2D ln(str);
	std::string str2 = "(((3,4),(2,2)),((6,2),(5,3)),((6,1),(7,9)),((8,4),(6,6)))";
	Line2D ln2(str2);

	//adding through strings when input format is not correct
	std::string str3 = "(((3,4),(2,2)),((6,2),(5,3)),((6,1)(7,9)),((8,4),(6,6)))";
	Line2D wrongInp(str3);

	//checking operator !=
	std::cout<<"check if ln1!=ln2"<<std::endl;
	if(ln!=ln2)
		std::cout<<"true"<<std::endl;
	else
		std::cout<<"false"<<std::endl;
	
	//checking operator ==
	std::cout<<"check if ln1==ln2"<<std::endl;
	if(ln==ln2)
		std::cout<<"true"<<std::endl;
	else
		std::cout<<"false"<<std::endl;
	
	//checking if any object is empty
	bool empty = ln.isEmptyLine();
	std::cout<<"check if ln is empty : "<<empty<<std::endl;

	//method to get total number of segments in the object
	std::cout<<"total number of segments in our object are : "<<ln.getNumberOfSegments()<<empty<<std::endl;

	//checking the functionality of an iterator
	std::cout<<"Travesed segments through iterators"<<std::endl;
	for(Line2D::iterator it = ln.begin(); it!=ln.end(); it++)
	{
		std::cout<<(*it).segment;
	}
	std::cout<<std::endl;

	//adding a segment to line2D
	RGPPoint2D p1(Number("21"),Number("31"));
	RGPPoint2D p2(Number("22"),Number("33"));
	RGPSegment2D seg(p1,p2);
	std::cout<<"list after adding"<<std::endl;
	ln.add(seg);
	for(Line2D::iterator it = ln.begin(); it!=ln.end(); it++)
	{
		std::cout<<(*it).segment;
	}
	std::cout<<std::endl;

	//code for removing a segment from an object
	Line2D::iterator it = ln.begin();
	it++;
	it++;
	ln.remove(it);
	std::cout<<"list after removing the segment"<<std::endl;
	for(Line2D::iterator it = ln.begin(); it!=ln.end(); it++)
	{
		std::cout<<(*it).segment;
	}
	std::cout<<std::endl;

	//code for updating a segment through iterator
	Line2D::iterator it1 = ln.begin();
	it1++;
	RGPPoint2D p3(Number("12"),Number("5"));
	RGPPoint2D p4(Number("2"),Number("5"));
	RGPSegment2D seg2(p3,p4);
	std::cout<<"list of segments after updating "<<std::endl;
	ln.update(it1,seg2);
	for(auto it = ln.begin(); it!=ln.end(); it++)
	{
		std::cout<<(*it).segment;
	}
	std::cout<<std::endl;

	//checking method to print all lines
	std::cout<<"method to print all the segments in our object"<<std::endl;
	ln.printAllLines();
	std::cout<<std::endl;

	//method to get the bounding boxe
	RGPSegment2D ln4 = ln.getBoundingBox();
	std::cout<<"bounding box is "<<std::endl;
	std::cout<<ln4<<std::endl;
}