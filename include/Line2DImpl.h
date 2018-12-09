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
		Line2DImpl();
		Line2DImpl(std::vector<RGPSegment2D> listOfSegments);
		Line2DImpl(std::string listOfLine2DString);
		Line2DImpl(std::ifstream& file); // Send in file for constructor
		~Line2DImpl();

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
		
		iterator begin();
		iterator end();
		
		// Methods
		std::string getLineString(); // Get the line as human readable ASCII string
		void printAllLines();
		bool isEmptyLine();
		bool isValidLine();
		int getNumberOfSegments();	// Get the total number of RGPSegment2Ds listed
		Line2DImpl getBoundingBox();
		
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
