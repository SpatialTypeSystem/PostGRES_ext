#include "Point2D.h"
#include "Point2DImpl.h"

struct Point2D::Point2DStore 
{
	Point2DImpl *implPointer;
	// Maintains a dummy copy for iterator to work
	std::vector<RGPPoint2D> vectorOfPoints;

	Point2DStore(std::string pointsString) 
	{
		implPointer = new Point2DImpl(pointsString);
		vectorOfPoints = implPointer->getVectorOfPoints();
	}

	Point2DStore(std::vector<RGPPoint2D> pointVector) 
	{
		implPointer = new Point2DImpl(pointVector);
		vectorOfPoints = implPointer->getVectorOfPoints();
	}
};


Point2D::iterator::iterator(RGPPoint2D *ptr1)
{
	ptr = ptr1;
}

RGPPoint2D Point2D::iterator::operator*()
{
	return *ptr;
}

RGPPoint2D Point2D::iterator::operator++(int junk)
{
	RGPPoint2D *ptr1;
	ptr1 = ptr;
	ptr++;
	return *ptr1;
}

RGPPoint2D Point2D::iterator::operator++()
{
	ptr++;
	return *ptr;
}

bool Point2D::iterator::operator!=(const iterator &it)
{
	if(it.ptr==ptr)
		return false;
	return true;
}
bool Point2D::iterator::operator==(const iterator &it)
{
	if(it.ptr!=ptr)
		return false;
	return true;
}

Point2D::iterator Point2D::begin()
{
	RGPPoint2D *ptr = &(handle->vectorOfPoints[0]);
	return iterator(ptr);
}

Point2D::iterator Point2D::end()
{
	int t = handle->vectorOfPoints.size();
	return (iterator(&(handle->vectorOfPoints[t-1])));
}


Point2D::Point2D(std::string listOfPoint2DString)
{
	handle = new Point2DStore(listOfPoint2DString);
}

Point2D::~Point2D()
{
	delete handle->implPointer;
	delete handle;
}

bool Point2D::isEmptyPoint()
{
	return handle->implPointer->isEmptyPoint();
}

void Point2D::printAllPoints()
{
	handle->implPointer->printAllPoints();
}

int Point2D::getNumberOfPoints()
{
	return handle->implPointer->getNumberOfPoints();
}


//this method is used to add a new point to Point2D object
bool Point2D::add(RGPPoint2D rgpp2d)
{
	bool result = handle->implPointer->add(rgpp2d);
	handle->vectorOfPoints = handle->implPointer->getVectorOfPoints();
	return result;
}

//this method is used to update a point at a particular index
bool Point2D::update(Point2D::iterator it, RGPPoint2D rgpp2d)
{
	Point2DImpl::iterator newIt = handle->implPointer->begin();
	for(Point2DImpl::iterator implit = handle->implPointer->begin(); implit!= handle->implPointer->end();implit++)
	{
		if(*it == *implit)
		{
			newIt = implit;
			break;
		}
	}
	bool result = handle->implPointer->update(newIt, rgpp2d);
	handle->vectorOfPoints = handle->implPointer->getVectorOfPoints();
	return result;
}


//removes a particular point in the vector of points
bool Point2D::remove(Point2D::iterator it)
{
	Point2DImpl::iterator newIt = handle->implPointer->begin();
	for(Point2DImpl::iterator implit = handle->implPointer->begin(); implit!= handle->implPointer->end();implit++)
	{
		if(*it == *implit)
		{
			newIt = implit;
			break;
		}
	}
	bool result = handle->implPointer->remove(newIt);
	handle->vectorOfPoints = handle->implPointer->getVectorOfPoints();
	return result;
}

bool Point2D::operator==(const Point2D &p2d)
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

bool Point2D::operator!=(const Point2D &p2d)
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

RGPSegment2D Point2D::getBoundingBox()
{
	return handle->implPointer->getBoundingBox();
}
