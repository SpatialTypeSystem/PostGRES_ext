#ifndef LINE2D_H
#define LINE2D_H

#include "Number.h"
#include "RGP.h"
#include <string>
#include <vector>

struct Line2DImplStruct;

class Line2D{

private:
	// Fields
	Line2DImplStruct *implstruct;

public:
	// Constructors
	Line2D();
	Line2D(std::vector<RGPSegment2D> listOfSegments);
	Line2D(std::string listOfLine2DString);
	Line2D(std::ifstream& file); // Send in file for constructor
	~Line2D();

	// Methods
	std::string getLineString(); // Get the line as human readable ASCII string
	static bool isValidPoint();
	int getNumberPoints();
	std::vector<RGPSegment2D> getBoundingBox();
	bool add(RGPSegment2D rgp2d);
	template <class T> bool remove(T it);
	template <class T> bool update(T it, RGPSegment2D rgps2d);
	bool operator==(const Line2D &l2d);
	bool operator!=(const Line2D &l2d);
};

#endif //LINE2D
