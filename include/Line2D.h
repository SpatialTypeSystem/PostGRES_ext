#ifndef LINE2D_H
#define LINE2D_H

#include "Number.h"
#include "RGP.h"
#include <string>
#include <vector>

class Line2D{
public:
	// Constructors
	Line2D(std::string listOfLine2DString);
	Line2D(std::ifstream& file); // Send in file for constructor
	~Line2D();

	// Methods
	std::string getLineString(); // Get the line as human readable ASCII string
	bool isEmptyLine();
	bool isValidLine();
	int getNumberOfSegments();	// Get the total number of RGPSegment2Ds listed

	bool operator==(const Line2D &l2d);	// Override of operator == to check equality of two Line2Ds
	bool operator!=(const Line2D &l2d);	// Override of operator != to check inequality of two Line2Ds

	std::vector<RGPSegment2D> getBoundingBox();
		
private:
	struct Line2DStore;
	Line2DStore *handle;
};

#endif //LINE2D
