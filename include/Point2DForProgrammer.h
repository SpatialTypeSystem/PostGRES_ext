// PUBLIC HEADER FILE

#ifndef POINT2DFORPROGRAMMER_H
#define POINT2DFORPROGRAMMER_H

#include "Number.h"
#include "RGP.h"
#include <string>
#include <vector>
#include <iterator>

class Point2DForProgrammer{
public:
	// Constructors
	Point2DForProgrammer(std::vector<RGPPoint2D>);	// Take input from a file, convert the data into a Point2DForProgrammer  
	Point2DForProgrammer(std::string listOfPoint2DString);	// Read the string as a vector of RGPPoint2D and form a Point2DForProgrammer
	~Point2DForProgrammer();

	//iterator
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
	bool add(RGPPoint2D rgpp2d);	// Adds a new RGPPoint2D to the existing Point2D object
	bool update(iterator it, RGPPoint2D rgpp2d);	// Updates RGPPoint2D existing at specified index
	bool remove(iterator it);	// Removes a RGPPoint2D at specified index

private:
	struct Point2DProgrammerStore;
	Point2DProgrammerStore *handle;
};

#endif //POINT2D_H
