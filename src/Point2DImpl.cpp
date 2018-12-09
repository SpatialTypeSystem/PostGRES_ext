#include "Point2DImpl.h"
#include "RGPPoint2D.h"
#include "RGP.h"
#include "RGPSegment2D.h"
#include "RGPHalfSegment2D.h"
#include "Line2DImpl.h"
#include <Number.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <exception>

//creates vectors to store points and bounding
struct Point2DImpl::Point2DImplStore 
{
	std::vector<RGPPoint2D> vectorOfPoints;
	std::vector<RGPPoint2D> boundingBox;
};

//iterator to iterate through our data structure and return elements accordingly.
//constructor to the iterator, points iterator to a particular element of our data type. 
Point2DImpl::iterator::iterator(RGPPoint2D *ptr1)
{
	ptr = ptr1;
}

//overloading * operator to return the pointing element
RGPPoint2D Point2DImpl::iterator::operator*()
{
	return *ptr;
}

//overloading ++ operator to move the iterator through our set of points
//this method is for postincrement
RGPPoint2D Point2DImpl::iterator::operator++(int junk)
{
	RGPPoint2D *ptr1;
	ptr1 = ptr;
	ptr++;
	return *ptr1;
}

//overloading ++ operator to move the iterator through our set of points
//this method is for preincrement
RGPPoint2D Point2DImpl::iterator::operator++()
{
	ptr++;
	return *ptr;
}

//checks if both the iterators are not equal.
bool Point2DImpl::iterator::operator!=(const iterator &it)
{
	if(it.ptr==ptr)
		return false;
	return true;
}

//checks if both the iterators are equal.
bool Point2DImpl::iterator::operator==(const iterator &it)
{
	if(it.ptr!=ptr)
		return false;
	return true;
}

//method for pointImpl, used mainly with iterators. returns iterator to the first point in the list of Points.
Point2DImpl::iterator Point2DImpl::begin()
{
	RGPPoint2D *ptr = &(handle->vectorOfPoints[0]);
	return iterator(ptr);
}

//method for pointImpl, used mainly with iterators. returns iterator to the last point in the list of Points.
Point2DImpl::iterator Point2DImpl::end()
{
	int t = handle->vectorOfPoints.size();
	return (iterator(&(handle->vectorOfPoints[t-1])));
}

//Constructors
//constructor to initialise point with a vector of RGPPoints.
Point2DImpl::Point2DImpl(std::vector<RGPPoint2D> listOfPoints)
{
	handle = new Point2DImplStore;
	handle->vectorOfPoints = listOfPoints;
}

//this constructor does not have any args. This just re initializes the handle.
Point2DImpl::Point2DImpl()
{
	handle = new Point2DImplStore;
}

//constructor to read points from a file
Point2DImpl::Point2DImpl(std::ifstream& file)
{
	std::string inputString;
	if(file.is_open())
	{
		std::stringstream strBuffer;
		strBuffer << file.rdbuf();
		inputString = strBuffer.str();
	}
	else
	{
		throw std::runtime_error("Error while reading the file");
	}
	
	if(parseStringToVectorOfPoints(inputString))
		std::cout << "success" << std::endl;
	else{
		std::cout << "failed" << std::endl;
		handle->vectorOfPoints.clear();
	}
}


//This constructor creates a Point2DImpl object based on a passed in string of points. We follow a specific convention here.
//((a,b),(c,d))
Point2DImpl::Point2DImpl(std::string listOfPoint2DString)
{
	handle = new Point2DImplStore;
	if(parseStringToVectorOfPoints(listOfPoint2DString))
	{
		std::cout<<"All points are added successfully"<<std::endl;
	}
	else
	{
		std::cout<<"Input Format is not correct"<<std::endl;
		handle->vectorOfPoints.clear();

	}
}

Point2DImpl::~Point2DImpl()
{
	delete handle;
}

//this method checks if the structure is empty
bool Point2DImpl::isEmptyPoint()
{
	return handle->vectorOfPoints.empty();
}

//method to print all points in the Point2D object
void Point2DImpl::printAllPoints()
{
	std::cout<<"(";
	std::vector<RGPPoint2D> x = handle->vectorOfPoints;
	for(auto i = x.begin(); i!=x.end(); i++)
		std::cout<<*i;
	std::cout<<")";
}

//this method return total number of points in the Point2D object.
int Point2DImpl::getNumberOfPoints()
{
	return handle->vectorOfPoints.size();
}

//returns bounding box for the object
RGPSegment2D Point2DImpl::getBoundingBox()
{
	std::vector<RGPPoint2D> points;
	std::vector<RGPPoint2D> boundPoints;
	//get all the points in the object
	points = handle->vectorOfPoints;

	//get the least point to get the first point for diagonal
	boundPoints.push_back(points[0]);

	//get the maxy for the secound point
	auto maxy = points[0].y;
	for(auto it = points.begin(); it!=points.end() ;it++)
	{
		if((*it).y > maxy)
			maxy=(*it).y;
	}
	//make the secound point from the set of points
	RGPPoint2D pt(points[points.size() - 1].x,maxy);
	//push back the secound point
	boundPoints.push_back(pt);

	//create the diagonal
	RGPSegment2D seg(boundPoints[0],boundPoints[1]);
	std::vector<RGPSegment2D> segs;

	segs.push_back(seg);
	Line2DImpl ln(segs);
	return seg;
}

//method checks if the both Point2D objects are equal
bool Point2DImpl::operator==(const Point2DImpl &p2d)
{
	int i=0;
	while(i< p2d.handle->vectorOfPoints.size())
    {
		if(handle->vectorOfPoints[i] != p2d.handle->vectorOfPoints[i])
			return false;
		else
			i++;
	}
	if(handle->vectorOfPoints.size() == p2d.handle->vectorOfPoints.size())
		return true;
	else
		return false;
}

//method checks if the both Point2D objects are not equal
bool Point2DImpl::operator!=(const Point2DImpl &p2d)
{
	int i=0;
	if(handle->vectorOfPoints.size() != p2d.handle->vectorOfPoints.size())
		return true;
	while(i< p2d.handle->vectorOfPoints.size())
    {
		if(handle->vectorOfPoints[i] != p2d.handle->vectorOfPoints[i])
			return true;
		else
			i++;
	}
	return false;
}

//returns the point at that particular index of the Point2D object
Point2DImpl Point2DImpl::operator[](int index)
{
	std::vector<RGPPoint2D> t;
	t.push_back(handle->vectorOfPoints[index]);
	Point2DImpl temp(t);
	return temp;
}

//assigns the object to the right to the object in the left.
Point2DImpl Point2DImpl::operator=(const Point2DImpl &p2d)
{
	handle->vectorOfPoints.clear();
	handle->vectorOfPoints = p2d.handle->vectorOfPoints;
}

std::vector<RGPPoint2D> Point2DImpl::getVectorOfPoints()
{
	return handle->vectorOfPoints;
}

//this method is used to add a new point to Point2D object
bool Point2DImpl::add(RGPPoint2D rgpp2d)
{
	try
    {
		//check if the vector is empty
		if(handle->vectorOfPoints.empty()) 
		{
			handle->vectorOfPoints.push_back(rgpp2d);
			return true;
		}

		int i=0;
		while(rgpp2d > handle->vectorOfPoints[i] && i < handle->vectorOfPoints.size())
			i++;
		if(i==handle->vectorOfPoints.size())
			handle->vectorOfPoints.push_back(rgpp2d);
		else
			handle->vectorOfPoints.insert(handle->vectorOfPoints.begin()+i, rgpp2d);
	}
	catch(int e)
    {
		return false;
	}
	return true;
}

//this method is used to update a point at a particular index
bool Point2DImpl::update(Point2DImpl::iterator it, RGPPoint2D rgpp2d)
{
	try
    {
		if(isEmptyPoint())
		{
			return false;
		}
		else
		{
			int index = it.ptr - &(handle->vectorOfPoints[0]);
			handle->vectorOfPoints.erase(handle->vectorOfPoints.begin()+index);
			add(rgpp2d);
			pointSort(handle->vectorOfPoints);
		}
    }
    catch(int e)
    {
        return false;
    }
    return true;
}

//removes a particular point in the vector of points
bool Point2DImpl::remove(Point2DImpl::iterator it)
{
	try
    {
		if(isEmptyPoint())
		{
			return false;
		}
		else
		{
			int index = it.ptr - &(handle->vectorOfPoints[0]);
        	handle->vectorOfPoints.erase(handle->vectorOfPoints.begin()+index);
		}
    }
    catch(int e)
    {
        return false;
    }
    return true;
}

//merge sort imlementation to sort all points
void Point2DImpl::pointSort(std::vector<RGPPoint2D> &bar)
{
	if (bar.size() <= 1) 
		return;

    int mid = bar.size() / 2;
    std::vector<RGPPoint2D> l;
    std::vector<RGPPoint2D> r;

    for (size_t j = 0; j < mid;j++)
        l.push_back(bar[j]);
    for (size_t j = 0; j < (bar.size()) - mid; j++)
        r.push_back(bar[mid + j]);

    pointSort(l);
    pointSort(r); 
    mergeSort(l, r, bar);
}


void Point2DImpl::mergeSort(std::vector<RGPPoint2D> &left, std::vector<RGPPoint2D> &right, std::vector<RGPPoint2D> &bars)
{
	int nL = left.size();
    int nR = right.size();
    int i = 0, j = 0, k = 0;

    while (j < nL && k < nR) 
    {
        if (left[j] <=
		right[k]) {
            bars[i] = left[j];
            j++;
        }
        else {
            bars[i] = right[k];
            k++;
        }
        i++;
    }
    while (j < nL) {
        bars[i] = left[j];
        j++; i++;
    }
    while (k < nR) {
        bars[i] = right[k];
        k++; i++;
    }
}

//parse method to parse all points from the string and make the vector of points
bool Point2DImpl::parseStringToVectorOfPoints(std::string st)
{
	std::vector<RGPPoint2D> points;
	int pos,fl=0;
	std::string num1,num2;
	std::string s =st;
	std::vector<Number> nums;

	//initialize the delimiter
	std::string delimeter = ",";

	//erase first and last (..*)
	s.erase(0,1);
	s.erase(s.length()-1,1);
  	s.append(",");
	  
	//keep finding the substrings 
	pos = s.find(delimeter);
	try{
		while(pos!= std::string::npos)
		{
			std::string a = s.substr(0, pos);
			if(a.length()>=2)
			{
				try
				{
					if(a[0]=='(')
					{
						//get the complete number and store it.
						std::string temp = "";
						int i =1;
						while(((a[i]<='9'&&a[i]>='0')||a[i]=='.'||a[i]=='-')&&i<a.length())
						{
							temp+=a[i];
							i++;
						} 
						num1=temp;
						fl++;
					}
					else if(a[a.length()-1]==')'&&fl==1)
					{
						//get the secound number
						fl=0;
						std::string temp = "";
						int i =0;
						while(((a[i]<='9'&&a[i]>='0')||a[i]=='.'||a[i]=='-')&&i<a.length()-1)
						{
							temp+=a[i];
							i++;
						} 
						num2=temp;
						//make RGPPoints and push back into the points vector
						points.push_back(RGPPoint2D(Number(num1),Number(num2)));
					}
					else
					{
						//return false if the input string is corrupt	
						return false;
					}
				}
				catch(int e){
					//return false if the input string is corrupt
					return false;
				}
			}
			else
			{
				//return false if the input string is corrupt
				return false;
			}
			//keep erasing the strings till we get our delimiter
			s.erase(0, pos + delimeter.length());
			pos = s.find(delimeter);
		}
	}
	catch(int e){
		return false;
	}
	//sort all points and add it to the vector
	pointSort(points);
	handle->vectorOfPoints = points;
}
