#ifndef LINE2D_H
#define LINE2D_H

#include "RGP.h"
#include "Number.h"
#include "Line2DImpl.h"
#include <string>
#include <vector>

class Line2D{
public:
	// Constructors
	Line2D(std::string listOfLine2DString);
	~Line2D();

	//iterator to run through the list of half segments
	class iterator
	{
		public:
			iterator(RGPHalfSegment2D*);
			RGPHalfSegment2D operator*();
			RGPHalfSegment2D operator++(int);
			RGPHalfSegment2D operator++();
			bool operator!=(const iterator&);
			bool operator==(const iterator&);
			RGPHalfSegment2D *ptr;
	};
		
	iterator begin(); // return an iterator to the first element
	iterator end();   // return an iterator to the last element
		
	bool add(RGPSegment2D rgpSeg2d);	// Adds a new RGPSegment2D
	bool update(iterator it, RGPSegment2D rgpSeg2d);	// Updates RGPSegment2D existing at specified index
	bool remove(iterator it);	// Removes a RGPSegment2D at specified index
		
	// Methods
	void printAllLines(); // print all half segments in the vector
	bool isEmptyLine();
	int getNumberOfSegments();	// Get the total number of RGPSegment2Ds listed

	bool operator==(const Line2D &l2d);	// Override of operator == to check equality of two Line2Ds
	bool operator!=(const Line2D &l2d);	// Override of operator != to check inequality of two Line2Ds

	RGPSegment2D getBoundingBox();
		
private:
	struct Line2DStore;
	Line2DStore *handle;
};

#endif //LINE2D
