#include "Line2D.h"
#include "Line2DForProgrammer.h"

struct Line2D::Line2DUserStore {
	Line2DForProgrammer *poi;

	Line2DUserStore(std::vector<RGPHalfSegment2D> listOfSegments) {
		poi = new Line2DForProgrammer(listOfSegments);
	}

	Line2DUserStore(std::string listOfLine2DString) {
		poi = new Line2DForProgrammer(listOfLine2DString);
	}	

	Line2DUserStore(std::ifstream& file) {
		poi = new Line2DForProgrammer(file);
	}
	
	~Line2DUserStore()
	{
		poi = nullptr;
	}
};

Line2D::Line2D(std::vector<RGPHalfSegment2D> listOfSegments)
{
	impl = new Line2DUserStore(listOfSegments);
}

Line2D::Line2D(std::string listOfLine2DString)
{
	impl = new Line2DUserStore(listOfLine2DString);
}

Line2D::Line2D(std::ifstream& file) // Send in file for constructor
{
	impl = new Line2DUserStore(file);
}

Line2D::~Line2D()
{
	impl = nullptr;
}

// Methods
std::string Line2D::getLineString() // Get the line as human readable ASCII string
{
	return impl->poi->getLineString();
}

// static
bool Line2D::isEmptyLine()
{
	return impl->poi->isEmptyLine();
}

int Line2D::Line2D::getNumberOfSegments()
{
	return impl->poi->getNumberOfSegments();
}

std::vector<RGPSegment2D> Line2D::getBoundingBox()
{
	return impl->poi->getBoundingBox();
}

bool Line2D::add(RGPSegment2D rgp2d)
{
	return impl->poi->add(rgp2d);
}

bool Line2D::remove(int index)
{
	return impl->poi->remove(index);
}

bool update(int index, RGPSegment2D rgps2d)
{
	return impl->poi->update(index, rgps2d);
}

bool Line2D::operator==(const Line2D &l2d)
{
	return impl->poi->operator==(&l2d);
}

bool Line2D::operator!=(const Line2D &l2d)
{
	return impl->poi->operator!=(&l2d);
}

RGPSegment2D Line2D::operator[](int index)
{
	return impl->poi->operator[](index);
}