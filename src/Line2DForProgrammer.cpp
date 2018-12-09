#include "Line2D.h"
#include "Line2DImpl.h"
#include "Line2DForProgrammer.h"

struct Line2DForProgrammer::Line2DProgrammerStore
{
	Line2DImpl *implPointer;
		// Maintains a dummy copy for iterator to work
	std::vector<RGPHalfSegment2D> vectorOfSegments;
	Line2DProgrammerStore(std::string linesString) 
	{
		implPointer = new Line2DImpl(linesString);
		vectorOfSegments = implPointer->getVectorOfSegments();

	}
};


//constructor for Line2D iterator
Line2DForProgrammer::iterator::iterator(RGPHalfSegment2D *ptr1)
{
	ptr = ptr1;
}

//overloading * to get output
RGPHalfSegment2D Line2DForProgrammer::iterator::operator*()
{
	return *ptr;
}

//operator overloading ++ (post) for incrementing the iterator
RGPHalfSegment2D Line2DForProgrammer::iterator::operator++(int junk)
{
	RGPHalfSegment2D *ptr1;
	ptr1 = ptr;
	ptr++;
	return *ptr1;
}

//operator overloading ++ (pre) for incrementing the iterator
RGPHalfSegment2D Line2DForProgrammer::iterator::operator++()
{
	ptr++;
	return *ptr;
}

bool Line2DForProgrammer::iterator::operator!=(const iterator &it)
{
	if(it.ptr==ptr)
		return false;
	return true;
}

//overloading == to check if two iterators are equal
bool Line2DForProgrammer::iterator::operator==(const iterator &it)
{
	if(it.ptr!=ptr)
		return false;
	return true;
}

//Line2D begin method, return an iterator to the first segment in the sorted order.
Line2DForProgrammer::iterator Line2DForProgrammer::begin()
{
	RGPHalfSegment2D *ptr = &(handle->vectorOfSegments[0]);
	return iterator(ptr);
}

//Line2D begin method, return an iterator to the last segment in the sorted order.
Line2DForProgrammer::iterator Line2DForProgrammer::end()
{
	int t = handle->vectorOfSegments.size();
	return (iterator(&(handle->vectorOfSegments[t-1])));
}

//method to add new segments to our list of segments
bool Line2DForProgrammer::add(RGPSegment2D rgpSeg2d)
{
	bool res = handle->implPointer->add(rgpSeg2d);
	handle->vectorOfSegments = handle->implPointer->getVectorOfSegments();
	return res;
}

//method to update a segment in our current list of segments
bool Line2DForProgrammer::update(Line2DForProgrammer::iterator it, RGPSegment2D rgpSeg2d)
{
	Line2DImpl::iterator newIt = handle->implPointer->begin();
	for(Line2DImpl::iterator implit = handle->implPointer->begin(); implit!= handle->implPointer->end();implit++)
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
bool Line2DForProgrammer::remove(Line2DForProgrammer::iterator it)
{
	Line2DImpl::iterator newIt = handle->implPointer->begin();
	for(Line2DImpl::iterator implit = handle->implPointer->begin(); implit!= handle->implPointer->end();implit++)
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

Line2DForProgrammer::Line2DForProgrammer(std::string listOfLine2DString)
{
	handle = new Line2DProgrammerStore(listOfLine2DString);
}

Line2DForProgrammer::~Line2DForProgrammer()
{
	delete handle->implPointer;
	delete handle;
}
