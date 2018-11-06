// PRIVATE SOURCE FILE

#include "Point2D.h"
#include "Point2DImpl.h"

//class Point2D::Point2DImpl {};

Point2D::Point2DStruct *getStruct()
{
	// return someObject->mystruct;
}

Point2D::Point2D()
{
	// Will NOT be used. Never create Point2D object without points.
}

Point2D::Point2D(std::vector<RGPPoint2D> listOfPoints)
{
	// 1) Takes in listOfPoints
	// 2) gets '.points' vector from struct (call *getStruct())
	// 3) re-assign struct vector to listOfPoints
}

Point2D::Point2D(std::ifstream& file)
{
	// Emtpy
}

Point2D::Point2D(std::string listOfPoint2DString)
{
	// Takes in listOfPoint2DString and converts to vector<RGPPoint2D>
	// and assigns vector to vector in struct
}

Point2D::~Point2D()
{
	// Assign vector in struct = null
}


std::string getPointString() // Get the point as human readable ASCII string
{
	// Emtpy
}

// static
bool Point2D::isEmptyPoint()
{
	// Emtpy
}

bool Point2D::operator==(const Point2D &p2d)
{
	// Emtpy
}

bool Point2D::operator!=(const Point2D &p2d)
{
	// Emtpy
}

RGPPoint2D Point2D::operator[](int index)
{
	// Emtpy
}

int Point2D::getNumberOfPoints()
{
	// Emtpy
}

std::vector<RGPSegment2D> Point2D::getBoundingBox()
{
	// Emtpy
}

bool Point2D::add(RGPPoint2D rgpp2d)
{
	// Emtpy
}

bool Point2D::update(int index, RGPPoint2D rgpp2d)
{
	// Emtpy
}

bool Point2D::remove(int index)
{
	// Emtpy
}
