#ifndef POINT2D_H
#define POINT2D_H

#include "Number.h"
#include "RGP.h"
#include <string>
#include <vector>
#include <iterator>

class Point2D{
public:
	// Fields

	// Constructors
	Point2D();
	Point2D(std::vector<RGPPoint2D> listOfPoints);	// Create the Point2D as a vector of RGPPoint2Ds
	Point2D(std::ifstream& file);	// Take input from a file, convert the data into a Point2D  
	Point2D(std::string listOfPoint2DString);	// Read the string as a vector of RGPPoint2D and form a Point2D
	~Point2D();

	// Methods
	std::string getPointString();  // Get the point as human readable ASCII string
	static bool isEmptyPoint();	// Checks if the Point2D object is empty
	static bool isValidPoint();	// Checks if the Point2D object is empty
	bool operator==(const Point2D &p2d);	// Override of operator == to check equality of two Point2Ds
	bool operator!=(const Point2D &p2d);	// Override of operator != to check inequality of two Point2Ds
	int getNumberOfPoints();	// Get the total number of RGPPoint2Ds listed
	std::vector<RGPSegment2D> getBoundingBox();	
	bool add(RGPPoint2D rgpp2d);	// Adds a new RGPPoint2D to the existing Point2D object
	bool update(int index, RGPPoint2D rgpp2d);	// Updates RGPPoint2D existing at specified index
	bool remove(int index);	// Removes a RGPPoint2D at specified index
	RGPPoint2D operator[](int index);	// Retrieves a RGPPoint2D at specified index
	
	private:
		struct Point2DImplStruct;
		
		// Fields
		Point2DImplStruct *implstruct;
};

#endif //POINT2D_H
