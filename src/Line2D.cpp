#include "Line2D.h"

//struct Line2DImplStruct {};

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
bool Line2D::isEmptyLine()
{
	// Emtpy
}

int Line2D::Line2D::getNumberOfSegments()
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

bool Line2D::remove(int index)
{
	// Emtpy
}

bool update(int index, RGPSegment2D rgps2d)
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

RGPSegment2D Line2D::operator[](int index)
{
	// Emtpy
}
