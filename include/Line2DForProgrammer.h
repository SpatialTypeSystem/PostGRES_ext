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
	
private:
	struct Line2DProgrammerStore;
	Line2DProgrammerStore *handle;
};

#endif //LINE2D