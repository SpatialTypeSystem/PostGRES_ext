#include "Point2D.h"

class Point2D::Point2DImpl {};

Point2D::Point2D()
{
	// Emtpy
}

Point2D::Point2D(std::vector<RGPPoint2D> listOfPoints)
{
	// Emtpy
}

Point2D::Point2D(std::ifstream& file)
{
	// Emtpy
}

Point2D::Point2D(std::string listOfPoint2DString)
{
	// Emtpy
}

Point2D::~Point2D()
{
	// Emtpy
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
