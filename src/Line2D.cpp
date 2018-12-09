#include "Line2D.h"
#include "Line2DImpl.h"

struct Line2D::Line2DStore {
	Line2DImpl *implPointer;
	std::vector<RGPHalfSegment2D> vectorOfSegments;

	Line2DStore(std::string linesString) 
	{
		implPointer = new Line2DImpl(linesString);
		vectorOfSegments = implPointer->getVectorOfSegments();
	}

	Line2DStore(std::ifstream& file) 
	{
		implPointer = new Line2DImpl(file);
		vectorOfSegments = implPointer->getVectorOfSegments();
	}
};

//constructor for Line2D iterator
Line2D::iterator::iterator(RGPHalfSegment2D *ptr1)
{
	ptr = ptr1;
}

//overloading * to get output
RGPHalfSegment2D Line2D::iterator::operator*()
{
	return *ptr;
}

//operator overloading ++ (post) for incrementing the iterator
RGPHalfSegment2D Line2D::iterator::operator++(int junk)
{
	RGPHalfSegment2D *ptr1;
	ptr1 = ptr;
	ptr++;
	return *ptr1;
}

//operator overloading ++ (pre) for incrementing the iterator
RGPHalfSegment2D Line2D::iterator::operator++()
{
	ptr++;
	return *ptr;
}

bool Line2D::iterator::operator!=(const iterator &it)
{
	if(it.ptr==ptr)
		return false;
	return true;
}

//overloading == to check if two iterators are equal
bool Line2D::iterator::operator==(const iterator &it)
{
	if(it.ptr!=ptr)
		return false;
	return true;
}

//Line2D begin method, return an iterator to the first segment in the sorted order.
Line2D::iterator Line2D::begin()
{
	RGPHalfSegment2D *ptr = &(handle->vectorOfSegments[0]);
	return iterator(ptr);
}

//Line2D begin method, return an iterator to the last segment in the sorted order.
Line2D::iterator Line2D::end()
{
	int t = handle->vectorOfSegments.size();
	return (iterator(&(handle->vectorOfSegments[t-1])));
}

//method to add new segments to our list of segments
bool Line2D::add(RGPSegment2D rgpSeg2d)
{
	bool res = handle->implPointer->add(rgpSeg2d);
	handle->vectorOfSegments = handle->implPointer->getVectorOfSegments();
	return res;
}

//method to update a segment in our current list of segments
bool Line2D::update(Line2D::iterator it, RGPSegment2D rgpSeg2d)
{
	Line2DImpl::iterator newIt = handle->implPointer->begin();
	for(Line2DImpl::iterator implit = handle->implPointer->begin(); implit!= handle->implPointer->end();++implit)
	{
		if(*it == *implit)
		{
			newIt = implit;
			break;
		}
	}
	bool result = handle->implPointer->update(newIt, rgpSeg2d);
	handle->vectorOfSegments = handle->implPointer->getVectorOfSegments();
	return result;

}

//method to remove a segment using an iterator
bool Line2D::remove(Line2D::iterator it)
{
	Line2DImpl::iterator newIt = handle->implPointer->begin();
	for(Line2DImpl::iterator implit = handle->implPointer->begin(); implit!= handle->implPointer->end();++implit)
	{
		if(*it == *implit)
		{
			newIt = implit;
			break;
		}
	}
	bool result = handle->implPointer->remove(newIt);
	handle->vectorOfSegments = handle->implPointer->getVectorOfSegments();
	return result;
}

Line2D::Line2D(std::string listOfLine2DString)
{
	handle = new Line2DStore(listOfLine2DString);
}

Line2D::~Line2D()
{
	delete handle->implPointer;
	delete handle;
}

// Methods
bool Line2D::isEmptyLine()
{
	return handle->implPointer->isEmptyLine();
}

void Line2D::printAllLines()
{
	handle->implPointer->printAllLines();
}

int Line2D::Line2D::getNumberOfSegments()
{
	return handle->implPointer->getNumberOfSegments();
}

bool Line2D::operator==(const Line2D &l2d)
{
	// TODO
	//return handle->implPointer->operator==(&l2d);
}

bool Line2D::operator!=(const Line2D &l2d)
{
	// TODO
	//return handle->implPointer->operator!=(&l2d);
}

RGPSegment2D Line2D::getBoundingBox()
{
	return handle->implPointer->getBoundingBox();
}