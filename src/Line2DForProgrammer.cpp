#include "Line2D.h"
#include "Line2DImpl.h"
#include "Line2DForProgrammer.h"

struct Line2DForProgrammer::Line2DProgrammerStore
{
	Line2DImpl *implPointer;

	Line2DProgrammerStore(std::string linesString) 
	{
		implPointer = new Line2DImpl(linesString);
	}

	Line2DProgrammerStore(std::ifstream& file) 
	{
		implPointer = new Line2DImpl(file);
	}
};

Line2DForProgrammer::Line2DForProgrammer(std::string listOfLine2DString)
{
	handle = new Line2DProgrammerStore(listOfLine2DString);
}

Line2DForProgrammer::Line2DForProgrammer(std::ifstream& file) // Send in file for constructor
{
	handle = new Line2DProgrammerStore(file);
}

Line2DForProgrammer::~Line2DForProgrammer()
{
	delete handle->implPointer;
	delete handle;
}

bool Line2DForProgrammer::add(RGPSegment2D rgpSeg2d)
{
	//TODO
}

bool Line2DForProgrammer::remove(std::vector<RGPSegment2D>::iterator it)
{
	//TODO
}

bool update(std::vector<RGPSegment2D>::iterator it, RGPSegment2D rgpSeg2d)
{
	//TODO
}
