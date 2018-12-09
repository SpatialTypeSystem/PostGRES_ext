#ifndef LINE2DFORPROGRAMMER_H
#define LINE2DFORPROGRAMMER_H

#include "Number.h"
#include "RGP.h"
#include "RGPSegment2D.h"
#include <string>
#include <vector>
#include <iterator>

class Line2DForProgrammer{
public:
	// Constructors
	Line2DForProgrammer(std::string listOfLine2DString);
	Line2DForProgrammer(std::ifstream& file); // Send in file for constructor
	~Line2DForProgrammer();

	// Methods
	bool add(RGPSegment2D rgpSeg2d);	// Adds a new RGPSegment2D
	bool update(std::vector<RGPSegment2D>::iterator it, RGPSegment2D rgpSeg2d);	// Updates RGPSegment2D existing at specified index
	bool remove(std::vector<RGPSegment2D>::iterator it);	// Removes a RGPSegment2D at specified index

private:
	struct Line2DProgrammerStore;
	Line2DProgrammerStore *handle;
};

#endif //LINE2D