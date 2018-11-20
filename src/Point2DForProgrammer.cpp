#include "Point2DForProgrammer.h"
#include "Point2DImpl.h"

struct Point2DForProgrammer::Point2DProgrammerStore 
{
	Point2DImpl *implPointer;

	Point2DProgrammerStore(std::string pointsString) 
	{
		implPointer = new Point2DImpl(pointsString);
	}

	Point2DProgrammerStore(std::ifstream& file) 
	{
		implPointer = new Point2DImpl(file);
	}
};

Point2DForProgrammer::Point2DForProgrammer(std::ifstream& file)
{
	handle = new Point2DProgrammerStore(file);
}

Point2DForProgrammer::Point2DForProgrammer(std::string listOfPoint2DString)
{
	handle = new Point2DProgrammerStore(listOfPoint2DString);
}

Point2DForProgrammer::~Point2DForProgrammer()
{
	delete handle->implPointer;
	delete handle;
}

// Adds a new RGPPoint2D to the existing Point2D object
bool Point2DForProgrammer::add(RGPPoint2D rgpp2d)
{	
	//TODO
}

// Updates RGPPoint2D existing at specified index
bool Point2DForProgrammer::update(int index, RGPPoint2D rgpp2d) 
{
	//TODO
}

// Removes a RGPPoint2D at specified index
bool Point2DForProgrammer::remove(int index) 
{
	//TODO
}
