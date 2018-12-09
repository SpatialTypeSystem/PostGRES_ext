#include "Point2D.h"
#include "Point2DImpl.h"

struct Point2D::Point2DStore 
{
	Point2DImpl *implPointer;

	Point2DStore(std::string pointsString) 
	{
		implPointer = new Point2DImpl(pointsString);
	}

	Point2DStore(std::ifstream& file) 
	{
		implPointer = new Point2DImpl(file);
	}
};

Point2D::Point2D(std::ifstream& file)
{
	handle = new Point2DStore(file);
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


std::string Point2D::getPointString() 
{
	return handle->implPointer->getPointString();
}

bool Point2D::isEmptyPoint()
{
	return handle->implPointer->isEmptyPoint();
}

bool Point2D::isValidPoint()
{
	return handle->implPointer->isValidPoint();
}

int Point2D::getNumberOfPoints()
{
	return handle->implPointer->getNumberOfPoints();
}

bool Point2D::operator==(const Point2D &p2d)
{
	//TODO
}

bool Point2D::operator!=(const Point2D &p2d)
{
	//TODO
}

std::vector<RGPSegment2D> Point2D::getBoundingBox()
{
	//return handle->implPointer->getBoundingBox();
}
