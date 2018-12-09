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
	Point2D(std::string listOfPoint2DString);	// Read the string as a vector of RGPPoint2D and form a Point2D
	~Point2D();

	class iterator
	{
		public:
			iterator(RGPPoint2D*);
			RGPPoint2D operator*();
			RGPPoint2D operator++(int);
			RGPPoint2D operator++();
			bool operator!=(const iterator&);
			bool operator==(const iterator&);
			RGPPoint2D *ptr;
	};

	iterator begin();
	iterator end();

	// Methods
	bool isEmptyPoint();	// Checks if the Point2D object is empty
	int getNumberOfPoints();	// Get the total number of RGPPoint2Ds listed
	void printAllPoints();
	bool add(RGPPoint2D rgpp2d);	// Adds a new RGPPoint2D to the existing Point2D object
	bool update(iterator it, RGPPoint2D rgpp2d);	// Updates RGPPoint2D existing at specified index
	bool remove(iterator it);	// Removes a RGPPoint2D at specified index


	bool operator==(const Point2D &p2d);	// Override of operator == to check equality of two Point2Ds
	bool operator!=(const Point2D &p2d);	// Override of operator != to check inequality of two Point2Ds
	RGPSegment2D getBoundingBox();

private:
	struct Point2DStore;
	Point2DStore *handle;
};

#endif //POINT2D_H
