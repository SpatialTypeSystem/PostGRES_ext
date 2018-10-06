#include "../include/Point2D.h"

struct Point2DImplStruct {};

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
bool Point2D::isValidPoint()
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

int Point2D::getNumberPoints()
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

template <class T> bool Point2D::update(T it, RGPPoint2D rgpp2d)
{
	// Emtpy
}

template <class T> bool Point2D::remove(T it)
{
	// Emtpy
}
