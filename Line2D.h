#ifndef LINE2D_H
#define LINE2D_H

#include "Number.h"
#include "RGP.h"
#include <string>
#include <vector>

class Line2D{

private:
	// Fields
	Point2DImplStruct implstruct;

public:
	// Constructors
	Line2D();
	Line2D(std::vector<RGPSegment2D> listOfSegments);
	Line2D(string listOfLine2DString);
	Line2D(ifstream& file); // Send in file for constructor
	~Line2D();

	// Methods
	string getLineString(); // Get the line as human readable ASCII string
	static bool isValidPoint();
	int getNumberPoints();
	std::vector<RGPSegment2D> getBoundingBox();
	bool add(RGPSegment2D rgp2d);
	// bool update(const iterator iter, RGPSegment2D rgp2d);
	// bool remove(const iterator iter);
	bool operator==(const Line2D &l2d);
	bool operator!=(const Line2D &l2d);
};

#endif //LINE2D
