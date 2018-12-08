#include "Region2DImpl.h"
#include<map>

struct Region2DImpl::Region2DImplStore 
{
	std::vector<RGPSegment2D> sortedVectorOfSegments;    
	std::vector<RGPAnnotatedHalfSegment2D> vectorOfAnnHalfSegments;
	std::vector<std::vector<RGPAnnotatedHalfSegment2D>> vectorOfFaces;
	std::vector<std::vector<RGPAnnotatedHalfSegment2D>> vectorOfHoles;
	std::map<int,int> faceToHoleRelationMap;
	Number areaOfRegion;

	//std::vector<RGPAnnotatedHalfSegment2D> outerCycle;
};

//Constructors

Region2DImpl::Region2DImpl()
{
	
}

Region2DImpl::Region2DImpl(std::vector<RGPAnnotatedHalfSegment2D> listOfRegions)
{
	handle = new Region2DImplStore;
	handle->vectorOfAnnHalfSegments = listOfRegions;
}

Region2DImpl::Region2DImpl(std::string listOfRegion2DString)
{
	handle = new Region2DImplStore;
	bool result = parseWDR(listOfRegion2DString);
	if(result == true)
	{
		// check areas if adding upto positive Number
		std::vector<Number> faceAreas;
		std::vector<Number> holeAreas;

		Number tfaceArea("0");
		for(int i=0; i<handle->vectorOfFaces.size(); i++)
		{
			Number area = getAreaOfCycle(handle->vectorOfFaces[i]);
			if(area <= Number("0"))
			{
				//TODO Throw exception
			}
			faceAreas.push_back(area);
			tfaceArea = tfaceArea + area;
		}
		Number tholeArea("0");
		for(int i=0; i<handle->vectorOfHoles.size(); i++)
		{
			Number area = getAreaOfCycle(handle->vectorOfHoles[i]);
			if(area <= Number("0"))
			{
				//TODO Throw exception
			}
			holeAreas.push_back(area);
			tholeArea = tholeArea + area;
		}
		handle->areaOfRegion = tfaceArea - tholeArea;
		
		if(handle->areaOfRegion <= Number("0"))
		{
			//TODO throw exception
		}

		// Check if all holes are contained in their respective faces
		std::map<int, int>::iterator itr; 
		int faceIndex = 0;
		int holeIndex = 0;
		for (itr = handle->faceToHoleRelationMap.begin(); itr != handle->faceToHoleRelationMap.end(); ++itr) { 			
			Number fArea = faceAreas[faceIndex];
			Number hArea("0");
			for(int i=holeIndex; i<holeIndex + itr->second; i++)
			{
				hArea = hArea + holeAreas[i];
			}
			
			if(fArea - hArea <= Number("0"))
			{
				//TODO throw exeption

			}

			faceIndex++;
			holeIndex = holeIndex + itr->second;
		} 		

		//Check if any 2 cycles are intersecting

	}
	else
	{
		
	}
}

Number Region2DImpl::getAreaOfCycle(std::vector<RGPAnnotatedHalfSegment2D> vectorOfSegments) 
{
	Number area("0");
	Number xCoord[vectorOfSegments.size()/2];
	Number yCoord[vectorOfSegments.size()/2];
	int j =0;
	for(int i=0; i<vectorOfSegments.size();i=i+2)
	{
		std::cout<<vectorOfSegments[i].dominantPoint<<std::endl;
		xCoord[j] = vectorOfSegments[i].dominantPoint.x;
		yCoord[j] = vectorOfSegments[i].dominantPoint.y;
		j++;
	}

	int k = j-1;
	for(int a=0; a<j; a++)
	{
		area = area + (xCoord[k]+xCoord[a]) * (yCoord[k]-yCoord[a]); 
		k = a;
	}	
	if(area < Number("0"))
	{
		//area = area * Number("-1");
	}
	std::cout<<"area "<<area<<std::endl;

	return area/Number("2");

}

bool Region2DImpl::parseWDR(std::string inputString) 
{
	std::map<int,int> faceToHoleMap;
	if(inputString.length() < 2)
	{
		return false;
	}
	
	std::string firstChar = inputString.substr(0,1);
	std::string lastChar = inputString.substr(inputString.length()-1, inputString.length());
	if(firstChar != "[" || lastChar != "]")
	{
		return false;
	}

	std::string notation = inputString.substr(1,3);
	if(notation == "WCS")
	{
		return false;
	}
	
	// formattedString = ((1 1,2 2),(1 1,2 2))&
	std::string formattedString = inputString.substr(4);
	formattedString.erase(formattedString.length()-1,1);

	std::string delimiter = "&";

	int numOfFaces = 1;
	int numOfHoles = 0;
	
	while(formattedString.length() > 0)
	{
		// ((1 1,2 2),(1 1,3 3)) = faceHoleSetString
		int pos = formattedString.find(delimiter);
		std::string faceHoleSetString = formattedString;
		if(pos != -1)
		{
			faceHoleSetString = formattedString.substr(0,pos);
		}

		// (1 1,2 2),(1 1,3 3) = partString
		std::string partString = faceHoleSetString.substr(0,pos);
		partString.erase(0,1);
		partString.erase(partString.length()-1,1);
		
		// 1 1,2 2 = faceSegmentString
		std::vector<RGPPoint2D> facePoints;
		int faceClosingPoint = partString.find(")");
		std::string faceSegmentString = partString.substr(1,faceClosingPoint-1);
		int faceSegmentStringLength = faceSegmentString.length();
		while(faceSegmentString.length() > 0)
		{
			int l = faceSegmentString.find(" ");
			std::string coord1 = faceSegmentString.substr(0,l);
			faceSegmentString.erase(0,l+1);
			int r = faceSegmentString.find(",");
			std::string coord2 = faceSegmentString.substr(0,r);
			if(r == -1) 
			{
				faceSegmentString.erase(0,faceSegmentString.length());
			} 
			else 
			{
				faceSegmentString.erase(0,r+1);
			}
			facePoints.push_back(RGPPoint2D(Number(coord1), Number(coord2)));
		}
		if(facePoints[0] != facePoints[facePoints.size()-1])
		{
			return false;
		}

		std::vector<RGPAnnotatedHalfSegment2D> emptyFaceVec;
		handle->vectorOfFaces.push_back(emptyFaceVec);
		
		for(int i=0; i<facePoints.size()-1;i++)
		{
			RGPSegment2D seg(facePoints[i],facePoints[i+1]);
			RGPAnnotatedHalfSegment2D annHS(seg,facePoints[i],true);
			RGPAnnotatedHalfSegment2D annHS2(seg,facePoints[i+1],true);
			handle->vectorOfFaces[numOfFaces-1].push_back(annHS);
			handle->vectorOfFaces[numOfFaces-1].push_back(annHS2);
		}

		std::vector<std::vector<RGPPoint2D>> holePointVector;
		std::string holesString = partString.substr(faceSegmentStringLength+3, partString.length());
		
		while(holesString.find(")") != std::string::npos)
		{
			int holeClosingPoint = holesString.find(")");
			std::string holeSegmentString = holesString.substr(1,holeClosingPoint-1);
			int holeSegmentStringLength = holeSegmentString.length();
			std::vector<RGPPoint2D> emptyVec;
			std::vector<RGPAnnotatedHalfSegment2D> emptyHoleVec;
			holePointVector.push_back(emptyVec);
			handle->vectorOfHoles.push_back(emptyHoleVec);
			while(holeSegmentString.length() > 0)
			{
				int l = holeSegmentString.find(" ");
				std::string coord1 = holeSegmentString.substr(0,l);
				holeSegmentString.erase(0,l+1);
				int r = holeSegmentString.find(",");
				std::string coord2 = holeSegmentString.substr(0,r);
				if(r == -1) 
				{
					holeSegmentString.erase(0,holeSegmentString.length());
				} 
				else 
				{
					holeSegmentString.erase(0,r+1);
				}

				holePointVector[numOfHoles].push_back(RGPPoint2D(Number(coord1), Number(coord2)));
			}

			std::vector hole = holePointVector[numOfHoles];
			if(hole[0] != hole[hole.size()-1])
			{
				return false;
			}

			for(int i=0; i<hole.size()-1;i++)
			{
				RGPSegment2D seg(hole[i],hole[i+1]);
				RGPAnnotatedHalfSegment2D annHS(seg,hole[i],true);
				RGPAnnotatedHalfSegment2D annHS2(seg,hole[i+1],true);
				handle->vectorOfHoles[numOfHoles].push_back(annHS);
				handle->vectorOfHoles[numOfHoles].push_back(annHS2);
			}


			holesString = holesString.substr(holeSegmentStringLength+2, holesString.length());
			if(holesString.length() != 0 && holesString.substr(0,1) == ",")
			{
					holesString.erase(0,1);
			}
			numOfHoles++;
		}

		faceToHoleMap.insert(std::pair<int, int>(numOfFaces,numOfHoles));
		numOfFaces++;	

		int faceHoleSetStringLength = faceHoleSetString.length();
		if(pos != -1)
		{
			faceHoleSetStringLength++;
		}
		formattedString = formattedString.substr(faceHoleSetStringLength,formattedString.length());		
	}

			std::map<int, int>::iterator itr; 
		for (itr = faceToHoleMap.begin(); itr != faceToHoleMap.end(); ++itr) { 
			std::cout << '\t' << itr->first 
             << '\t' << itr->second << '\n'; 
		} 
	handle->faceToHoleRelationMap = faceToHoleMap;
	return true;
}

/*
std::vector<RGPAnnotatedHalfSegment2D> Region2DImpl::constructRegion(std::string formattedInputString)
{
	// Parse the string into half segments + create a set of dp-array<annHS>
	std::map<RGPPoint2D, std::vector<RGPAnnotatedHalfSegment2D>> mapOfDpToAnnHS;
	

	// sort the annotated half segments

	// implement the algorithm
	int numberOfHalfSegments = annHalfSegmentsVector.length;
	int visitedHalfSegments = 0;
	while(visitedHalfSegments != numberOfHalfSegments) 
	{
		RGPAnnotatedHalfSegment2D annHalfSegment = handle->vectorOfAnnHalfSegments[visitedHalfSegments];
		if(annHalfSegment.isCycleComputed) 
		{
			visitedHalfSegments++;
			continue;
		}
		//TODO
		// Find if this segment is a part of a outer cycle or hole cycle
		annHalfSegment.isPartOfHole = computeCyclicStructure();

		//NewCycle(h)
		annHalfSegment.isCycleComputed = true;
		std::vector<RGPAnnotatedHalfSegment2D> newCycleSegments;
		if(annHalfSegment.isPartOfHole)
		{
			annHalfSegment.insideIsAbove = false;
		} 
		else 
		{
			annHalfSegment.insideIsAbove = true;
		}
		newCycleSegments.push_back(annHalfSegment);

		//Visit(dp(h))
		annHalfSegment.isPointVisited = true;

		if(annHalfSegment.isPartOfHole) 
		{
			//TODO
			//Using sweep line status, retrieve halfsegment f from its owning outer cycle;
			//Owns(h, f);
			//Set cycle walk mode to use counter-clockwise adjacency;
		}
		else 
		{
			//TODO Set cycle walk mode to use clockwise adjacency
		}

		// Cycle walk
		//1. Mark the other annotated hs to the current Cycle
		RGPPoint2D otherDp = annHalfSegment.segment.point1;
		

		visitedHalfSegments++;
	}
}
*/
Region2DImpl::Region2DImpl(std::ifstream& file)
{
	// Emtpy
}

Region2DImpl::~Region2DImpl()
{
	// Emtpy
}

std::string Region2DImpl::getRegionString() // Get the region as human readable ASCII string
{
	// Emtpy
}

Number Region2DImpl::area()
{
	// Emtpy
}

// static
bool Region2DImpl::isEmptyRegion(Region2DImpl region)
{
	// Emtpy
}

int Region2DImpl::getNumberOfFaces()
{
	// Emtpy
}

std::vector<RGPSegment2D> Region2DImpl::getBoundingBox()
{
	// Emtpy
}

bool Region2DImpl::addFace(std::vector<RGPSegment2D>)
{
	// Emtpy
}

bool Region2DImpl::update(int index, std::vector<RGPSegment2D>)
{
	// Emtpy
}

bool Region2DImpl::remove(int index)
{
	// Emtpy
}

bool Region2DImpl::operator==(const Region2DImpl &p2d)
{
	// Emtpy
}

bool Region2DImpl::operator!=(const Region2DImpl &p2d)
{
	// Emtpy
}

std::vector<RGPSegment2D> Region2DImpl::operator[](int index)
{
	// Empty
}

template <class T> std::vector<RGPSegment2D> getCycle(T it)
{
	// Emtpy
}

template <class T> std::vector<RGPSegment2D> getFace(T it)
{
	// Emtpy
}

