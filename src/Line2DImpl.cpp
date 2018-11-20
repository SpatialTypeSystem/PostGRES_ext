#include "../include/Line2D.h"
#include "../include/Line2DImpl.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <exception>

struct Line2DImpl::Line2DImplStore {
	std::vector<RGPHalfSegment2D> vectorOfSegments;
};

Line2DImpl::Line2DImpl(std::vector<RGPHalfSegment2D> listOfSegments)
{
	handle = new Line2DImplStore;
	handle->vectorOfSegments = listOfSegments;
}

Line2DImpl::Line2DImpl(std::string listOfLine2DString)
{
	handle = new Line2DImplStore;
	
	//TODO: parseStringToVectorOfLines() needs to be updated
	//handle->vectorOfSegments = parseStringToVectorOfLines(listOfLine2DString);
}

Line2DImpl::Line2DImpl(std::ifstream& file) // Send in file for constructor
{
	handle = new Line2DImplStore;
	
	std::string inputString;
	if(file.is_open())
	{
		std::stringstream strBuffer;
		strBuffer << file.rdbuf();
		inputString = strBuffer.str();
	}
	else
	{
		throw std::runtime_error("Error while reading the file");
	}
	
	//TODO: parseStringToVectorOfLines() needs to be updated
	//handle->vectorOfSegments = parseStringToVectorOfLines(inputString);
}

Line2DImpl::~Line2DImpl()
{
	// TODO
	// delete handle->vectorOfSegments;
	// delete handle;
}

// Methods
std::string Line2DImpl::getLineString() // Get the line as human readable ASCII string
{
	/*std::string resultString;
	if(!isEmptyLine())
	{
		resultString += "(";
		for (RGPHalfSegment2D rgpLine : handle->vectorOfSegments)
		{
			std::ostringstream stream;
			stream << rgpLine;
			std::string str =  stream.str();

			resultString += str;
			resultString += ",";
		}
		resultString += ")";
	}

	return resultString;*/
}

bool Line2DImpl::isEmptyLine()
{
	return handle->vectorOfSegments.empty();
}

bool Line2DImpl::isValidLine()
{
	bool validity = false;
	if(!handle->vectorOfSegments.empty()) 
	{
		//Check for validity
		//TODO
	}

	return validity;
}

int Line2DImpl::Line2DImpl::getNumberOfSegments()
{
	return handle->vectorOfSegments.size();
}

std::vector<RGPSegment2D> Line2DImpl::getBoundingBox()
{
	//TODO
	//Call convex hull implementation
	//return NULL;
}

bool Line2DImpl::add(RGPHalfSegment2D rgpSeg2d)
{
	try
	{
		if(isEmptyLine()){
			handle->vectorOfSegments.push_back(rgpSeg2d);
		}
		else{
			int i = 0;
			// TODO: fix error with operator > comparison
			//while(rgpSeg2d > handle->vectorOfSegments[i]){i++;}
			handle->vectorOfSegments.insert(handle->vectorOfSegments.begin()+i, rgpSeg2d);
		}
	}
	catch(int e)
	{
		return false;
	}
	return true;
}

bool Line2DImpl::update(std::vector<RGPHalfSegment2D>::iterator it, RGPHalfSegment2D rgpSeg2d)
{
	try
    {
		if(isEmptyLine()){
			return false;
		}
		else{
			int index = distance(handle->vectorOfSegments.begin(), it);
			handle->vectorOfSegments.erase(handle->vectorOfSegments.begin()+index);
			add(rgpSeg2d);
		}
    }
    catch(int e)
    {
        return false;
    }
    return true;
}

bool Line2DImpl::remove(std::vector<RGPHalfSegment2D>::iterator it)
{
	try
	{
		if(isEmptyLine()){
			return false;
		}
		else{
			int index = distance(handle->vectorOfSegments.begin(), it);
			handle->vectorOfSegments.erase(handle->vectorOfSegments.begin()+index);
		}
	}
	catch(int e)
	{
		return false;
	}
	return true;
}

bool Line2DImpl::operator==(const Line2DImpl &l2d)
{
	int i = 0;
	if(handle->vectorOfSegments.size() != l2d.handle->vectorOfSegments.size()){
		return false;
	}
	
	while(i < l2d.handle->vectorOfSegments.size())
    {
		if(handle->vectorOfSegments[i] != l2d.handle->vectorOfSegments[i])
			return false;
		else
			i++;
	}
	return true;
}

bool Line2DImpl::operator!=(const Line2DImpl &l2d)
{
	int i = 0;
	if(handle->vectorOfSegments.size() != l2d.handle->vectorOfSegments.size()){
		return true;
	}

	while(i < l2d.handle->vectorOfSegments.size())
    {
		if(handle->vectorOfSegments[i] != l2d.handle->vectorOfSegments[i])
			return true;
		else
			i++;
	}
	return false;
}

RGPSegment2D Line2DImpl::operator[](int index)
{
	// TODO: returned data type is NOT correct
	//return handle->vectorOfSegments[index];
}

void Line2DImpl::lineSort(std::vector<RGPHalfSegment2D> &bar)
{
	if (bar.size() <= 1) 
		return;

    int mid = bar.size() / 2;
    std::vector<RGPHalfSegment2D> l;
    std::vector<RGPHalfSegment2D> r;

    for (size_t j = 0; j < mid;j++)
        l.push_back(bar[j]);
    for (size_t j = 0; j < (bar.size()) - mid; j++)
        r.push_back(bar[mid + j]);

    lineSort(l);
    lineSort(r);
    mergeSort(l, r, bar);
}


void Line2DImpl::mergeSort(std::vector<RGPHalfSegment2D> &left, std::vector<RGPHalfSegment2D> &right, std::vector<RGPHalfSegment2D> &bars)
{
	int nL = left.size();
    int nR = right.size();
    int i = 0, j = 0, k = 0;

    while (j < nL && k < nR) 
    {
        if (left[j] <=
		right[k]) {
            bars[i] = left[j];
            j++;
        }
        else {
            bars[i] = right[k];
            k++;
        }
        i++;
    }
    while (j < nL) {
        bars[i] = left[j];
        j++; i++;
    }
    while (k < nR) {
        bars[i] = right[k];
        k++; i++;
    }
}

bool Line2DImpl::parseStringToVectorOfLines(std::string st)
{
	int pos;
	std::string num1;
	std::string s =st;
	std::string delimeter = ",";
	s.erase(0,1);
	s.erase(s.length()-1,1);
	std::cout << s << "\n";
	pos = s.find(delimeter);
	std::cout << pos << "\n";
	try{
		while(pos!= std::string::npos)
		{
			std::string a = s.substr(0, pos);
			std::cout << a << "\n";
			if(a.length()==2)
			{
				try
				{
					if(a[0]=='(')
					{
						num1 = a[1];
					}
					else if(a[1]==')')
					{
						std::string temp = a[0]+"";
						std::cout << temp << "\t" << num1 << "\n";
						// TODO: modify for line2d NOT point2d
						/*Number q(temp);
						Number p(num1);
						RGPHalfSegment2D poi(p,q);
						add(poi);*/
					}
					else
						return false;
				}
				catch(int e){
					return false;
				}
			}
			else
			{
				return false;
			}
			s.erase(0, pos + delimeter.length());
			pos = s.find(delimeter);
			
		}
	}
	catch(int e){
		return false;

	}
}