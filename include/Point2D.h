// PUBLIC HEADER FILE

#ifndef POINT2D_H
#define POINT2D_H

#include "Number.h"
#include "RGP.h"
#include <string>
#include <vector>
#include <iterator>

class Point2D{
public:
	// Constructors
	Point2D(std::ifstream& file);	// Take input from a file, convert the data into a Point2D  
	Point2D(std::string listOfPoint2DString);	// Read the string as a vector of RGPPoint2D and form a Point2D
	~Point2D();

	// Methods
	std::string getPointString();  // Get the point as human readable ASCII string
	bool isEmptyPoint();	// Checks if the Point2D object is empty
	bool isValidPoint();	// Checks if the Point2D object is empty
	int getNumberOfPoints();	// Get the total number of RGPPoint2Ds listed

	bool operator==(const Point2D &p2d);	// Override of operator == to check equality of two Point2Ds
	bool operator!=(const Point2D &p2d);	// Override of operator != to check inequality of two Point2Ds

	std::vector<RGPSegment2D> getBoundingBox();

private:
	struct Point2DStore;
	Point2DStore *handle;
};

#endif //POINT2D_H
