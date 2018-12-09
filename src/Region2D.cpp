#include "Region2D.h"

class Region2D::Region2DImpl {};

Region2D::Region2D()
{
	// Emtpy
}

Region2D::Region2D(std::vector<std::vector<RGPAnnotatedHalfSegment2D>> listOfRegions)
{
	// Emtpy
}

Region2D::Region2D(std::string listOfRegion2DString)
{
	// Emtpy
}

Region2D::Region2D(std::ifstream& file)
{
	// Emtpy
}

Region2D::~Region2D()
{
	// Emtpy
}

std::string Region2D::getRegionString() // Get the region as human readable ASCII string
{
	// Emtpy
}

Number Region2D::area()
{
	// Emtpy
}

// static
bool Region2D::isEmptyRegion(Region2D region)
{
	// Emtpy
}

int Region2D::getNumberOfFaces()
{
	// Emtpy
}

std::vector<RGPSegment2D> Region2D::getBoundingBox()
{
	// Emtpy
}

bool Region2D::addFace(std::vector<RGPSegment2D>)
{
	// Emtpy
}

bool Region2D::update(int index, std::vector<RGPSegment2D>)
{
	// Emtpy
}

bool Region2D::remove(int index)
{
	// Emtpy
}

bool Region2D::operator==(const Region2D &p2d)
{
	// Emtpy
}

bool Region2D::operator!=(const Region2D &p2d)
{
	// Emtpy
}

std::vector<RGPSegment2D> Region2D::operator[](int index)
{
	// Empty
}

template <class T> std::vector<RGPSegment2D> getCycle(T it)
{
	// Emtpy
}

template <class T> std::vector<RGPSegment2D> getFace(T it)
{
	// Emtpy
}

