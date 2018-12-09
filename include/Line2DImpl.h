#ifndef LINE2DIMPL_H
#define LINE2DIMPL_H

#include <string>
#include <vector>

#include "RGP.h"
#include "RGPSegment2D.h"
#include "RGPHalfSegment2D.h"

class Line2DImpl
{
	public:	
		// Constructors
		Line2DImpl(); // no args
		Line2DImpl(std::vector<RGPSegment2D> listOfSegments); //send in a vector of segments
		Line2DImpl(std::string listOfLine2DString); // send in a string
		~Line2DImpl(); //destructor

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
		
		// Methods
		void printAllLines(); // print all half segments in the vector
		bool isEmptyLine(); // checks if the line object is empty
		int getNumberOfSegments();	// Get the total number of RGPSegment2Ds listed
		RGPSegment2D getBoundingBox(); // find the bounding box diaginal
		std::vector<RGPHalfSegment2D> getVectorOfSegments();
		
		bool add(RGPSegment2D rgpSeg2d);	// Adds a new RGPSegment2D
		bool update(iterator it, RGPSegment2D rgpSeg2d);	// Updates RGPSegment2D existing at specified index
		bool remove(iterator it);	// Removes a RGPSegment2D at specified index
		
		bool operator==(const Line2DImpl &l2d);	// Override of operator == to check equality of two Line2Ds
		bool operator!=(const Line2DImpl &l2d);	// Override of operator != to check inequality of two Line2Ds
		Line2DImpl operator[](int index);	// Retrieves a RGPSegment2D at specified index
		Line2DImpl operator=(const Line2DImpl &l2dImpl);
		
	private:
		struct Line2DImplStore;
		Line2DImplStore *handle;
		void lineSort(std::vector<RGPHalfSegment2D> &bar);
		void mergeSort(std::vector<RGPHalfSegment2D> &left, std::vector<RGPHalfSegment2D> &right, std::vector<RGPHalfSegment2D> &bars);
		bool parseStringToVectorOfLines(std::string st);
};

#endif //POINT2DIMPL_H