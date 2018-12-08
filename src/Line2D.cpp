#include "Line2D.h"
#include "Line2DImpl.h"

struct Line2D::Line2DStore {
	Line2DImpl *implPointer;

	Line2DStore(std::string linesString) 
	{
		implPointer = new Line2DImpl(linesString);
	}

	Line2DStore(std::ifstream& file) 
	{
		implPointer = new Line2DImpl(file);
	}
};

Line2D::Line2D(std::string listOfLine2DString)
{
	handle = new Line2DStore(listOfLine2DString);
}

Line2D::Line2D(std::ifstream& file) // Send in file for constructor
{
	handle = new Line2DStore(file);
}

Line2D::~Line2D()
{
	delete handle->implPointer;
	delete handle;
}

// Methods
std::string Line2D::getLineString() // Get the line as human readable ASCII string
{
	return handle->implPointer->getLineString();
}

// static
bool Line2D::isEmptyLine()
{
	return handle->implPointer->isEmptyLine();
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

Line2DImpl Line2D::getBoundingBox()
{
	return handle->implPointer->getBoundingBox();
}