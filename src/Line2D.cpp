#include "../include/Line2D.h"

struct Line2DImplStruct {};

Line2D::Line2D()
{
	// Emtpy
}

Line2D::Line2D(std::vector<RGPSegment2D> listOfSegments)
{
	// Emtpy
}

Line2D::Line2D(std::string listOfLine2DString)
{
	// Emtpy
}

Line2D::Line2D(std::ifstream& file) // Send in file for constructor
{
	// Emtpy
}

Line2D::~Line2D()
{
	// Emtpy
}


// Methods
std::string Line2D::getLineString() // Get the line as human readable ASCII string
{
	// Emtpy
}

// static
bool Line2D::isValidPoint()
{
	// Emtpy
}

int Line2D::Line2D::getNumberPoints()
{
	// Emtpy
}

std::vector<RGPSegment2D> Line2D::getBoundingBox()
{
	// Emtpy
}

bool Line2D::add(RGPSegment2D rgp2d)
{
	// Emtpy
}

template <class T> bool Line2D::remove(T it)
{
	// Emtpy
}

template <class T> bool update(T it, RGPSegment2D rgps2d)
{
	// Emtpy
}

bool Line2D::operator==(const Line2D &l2d)
{
	// Emtpy
}

bool Line2D::operator!=(const Line2D &l2d)
{
	// Emtpy
}

