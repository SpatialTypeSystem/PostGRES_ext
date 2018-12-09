#include "Point2DForProgrammer.h"
#include "Point2DImpl.h"

struct Point2DForProgrammer::Point2DProgrammerStore 
{
	Point2DImpl *implPointer;
	// Maintains a dummy copy for iterator to work
	std::vector<RGPPoint2D> vectorOfPoints;

	Point2DProgrammerStore(std::string pointsString) 
	{
		implPointer = new Point2DImpl(pointsString);
		vectorOfPoints = implPointer->getVectorOfPoints();
	}

	Point2DProgrammerStore(std::vector<RGPPoint2D> pointVector) 
	{
		implPointer = new Point2DImpl(pointVector);
		vectorOfPoints = implPointer->getVectorOfPoints();
	}
};

Point2DForProgrammer::iterator::iterator(RGPPoint2D *ptr1)
{
	ptr = ptr1;
}

RGPPoint2D Point2DForProgrammer::iterator::operator*()
{
	return *ptr;
}

RGPPoint2D Point2DForProgrammer::iterator::operator++(int junk)
{
	RGPPoint2D *ptr1;
	ptr1 = ptr;
	ptr++;
	return *ptr1;
}

RGPPoint2D Point2DForProgrammer::iterator::operator++()
{
	ptr++;
	return *ptr;
}

bool Point2DForProgrammer::iterator::operator!=(const iterator &it)
{
	if(it.ptr==ptr)
		return false;
	return true;
}
bool Point2DForProgrammer::iterator::operator==(const iterator &it)
{
	if(it.ptr!=ptr)
		return false;
	return true;
}

Point2DForProgrammer::iterator Point2DForProgrammer::begin()
{
	RGPPoint2D *ptr = &(handle->vectorOfPoints[0]);
	return iterator(ptr);
}

Point2DForProgrammer::iterator Point2DForProgrammer::end()
{
	int t = handle->vectorOfPoints.size();
	return (iterator(&(handle->vectorOfPoints[t-1])));
}


Point2DForProgrammer::Point2DForProgrammer(std::vector<RGPPoint2D> pointVector)
{
	handle = new Point2DProgrammerStore(pointVector);
}

Point2DForProgrammer::Point2DForProgrammer(std::string listOfPoint2DString)
{
	handle = new Point2DProgrammerStore(listOfPoint2DString);
}

Point2DForProgrammer::~Point2DForProgrammer()
{
	delete handle->implPointer;
	delete handle;
}

// Adds a new RGPPoint2D to the existing Point2D object
bool Point2DForProgrammer::add(RGPPoint2D rgpp2d)
{	
	bool result = handle->implPointer->add(rgpp2d);
	handle->vectorOfPoints = handle->implPointer->getVectorOfPoints();
	return result;
}

// Updates RGPPoint2D existing at specified index
bool Point2DForProgrammer::update(Point2DForProgrammer::iterator it, RGPPoint2D rgpp2d) 
{
	Point2DImpl::iterator newIt = handle->implPointer->begin();
	for(Point2DImpl::iterator implit = handle->implPointer->begin(); implit!= handle->implPointer->end();++implit)
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

// Removes a RGPPoint2D at specified index
bool Point2DForProgrammer::remove(Point2DForProgrammer::iterator it) 
{
	Point2DImpl::iterator newIt = handle->implPointer->begin();
	for(Point2DImpl::iterator implit = handle->implPointer->begin(); implit!= handle->implPointer->end();++implit)
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
