#ifndef LINE2DIMPL_H
#define LINE2DIMPL_H

#include "RGP.h"
#include "RGPSegment2D.h"
#include "RGPHalfSegment2D.h"
#include <string>
#include <vector>
#include <iterator>

class Line2DImpl
{
	public:	
		// Constructors
		Line2DImpl(std::vector<RGPHalfSegment2D> listOfSegments);
		Line2DImpl(std::string listOfLine2DString);
		Line2DImpl(std::ifstream& file); // Send in file for constructor
		~Line2DImpl();

		// Methods
		std::string getLineString(); // Get the line as human readable ASCII string
		bool isEmptyLine();
		bool isValidLine();
		int getNumberOfSegments();	// Get the total number of RGPSegment2Ds listed
		std::vector<RGPSegment2D> getBoundingBox();
		
		bool add(RGPHalfSegment2D rgpSeg2d);	// Adds a new RGPSegment2D
		bool update(std::vector<RGPHalfSegment2D>::iterator it, RGPHalfSegment2D rgpSeg2d);	// Updates RGPSegment2D existing at specified index
		bool remove(std::vector<RGPHalfSegment2D>::iterator it);	// Removes a RGPSegment2D at specified index
		
		bool operator==(const Line2DImpl &l2d);	// Override of operator == to check equality of two Line2Ds
		bool operator!=(const Line2DImpl &l2d);	// Override of operator != to check inequality of two Line2Ds
		RGPSegment2D operator[](int index);	// Retrieves a RGPSegment2D at specified index
	
	private:
		struct Line2DImplStore;
		Line2DImplStore *handle;
		void lineSort(std::vector<RGPHalfSegment2D> &bar);
		void mergeSort(std::vector<RGPHalfSegment2D> &left, std::vector<RGPHalfSegment2D> &right, std::vector<RGPHalfSegment2D> &bars);
		bool parseStringToVectorOfLines(std::string st);
};

#endif //POINT2DIMPL_H