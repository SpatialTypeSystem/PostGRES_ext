#ifndef LINE2DFORPROGRAMMER_H
#define LINE2DFORPROGRAMMER_H

#include "Number.h"
#include "RGP.h"
#include <string>
#include <vector>

class Line2DForProgrammer{
public:
	// Constructors
	Line2DForProgrammer(std::vector<RGPHalfSegment2D> listOfSegments);
	Line2DForProgrammer(std::string listOfLine2DString);
	Line2DForProgrammer(std::ifstream& file); // Send in file for constructor
	~Line2DForProgrammer();

	// Methods
	std::string getLineString(); // Get the line as human readable ASCII string
	static bool isEmptyLine();
	static bool isValidLine();
	int getNumberOfSegments();	// Get the total number of RGPSegment2Ds listed
	std::vector<RGPSegment2D> getBoundingBox();
	bool operator==(const Line2D &l2d);	// Override of operator == to check equality of two Line2Ds
	bool operator!=(const Line2D &l2d);	// Override of operator != to check inequality of two Line2Ds
	bool add(RGPSegment2D rgpSeg2d);	// Adds a new RGPSegment2D 
	bool update(int index, RGPSegment2D rgpSeg2d);	// Updates RGPSegment2D existing at specified index
	bool remove(int index);	// Removes a RGPSegment2D at specified index
	RGPSegment2D operator[](int index);	// Retrieves a RGPSegment2D at specified index

private:
	struct Line2DImplStore;
	Line2DImplStore *impl;
};

#endif //LINE2D