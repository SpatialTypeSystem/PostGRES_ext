#include "../include/Line2D.h"
#include "../include/Line2DImpl.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <exception>

struct Line2DImpl::Line2DImplStore {
	std::vector<RGPHalfSegment2D> vectorOfSegments;
	std::vector<RGPHalfSegment2D> boundingBox;
};

Line2DImpl::iterator::iterator(RGPHalfSegment2D *ptr1)
{
	ptr = ptr1;
}

RGPHalfSegment2D Line2DImpl::iterator::operator*()
{
	return *ptr;
}

RGPHalfSegment2D Line2DImpl::iterator::operator++(int junk)
{
	RGPHalfSegment2D *ptr1;
	ptr1 = ptr;
	ptr++;
	return *ptr;
}

RGPHalfSegment2D Line2DImpl::iterator::operator++()
{
	ptr++;
	return *ptr;
}

bool Line2DImpl::iterator::operator!=(const iterator &it)
{
	if(it.ptr==ptr)
		return false;
	return true;
}

bool Line2DImpl::iterator::operator==(const iterator &it)
{
	if(it.ptr!=ptr)
		return false;
	return true;
}

Line2DImpl::iterator Line2DImpl::begin()
{
	RGPHalfSegment2D *ptr = &(handle->vectorOfSegments[0]);
	return iterator(ptr);
}

Line2DImpl::iterator Line2DImpl::end()
{
	int t = handle->vectorOfSegments.size();
	return (iterator(&(handle->vectorOfSegments[t-1])));
}

//Constructors
Line2DImpl::Line2DImpl(std::vector<RGPHalfSegment2D> listOfSegments)
{
	handle = new Line2DImplStore;
	handle->vectorOfSegments = listOfSegments;
}

Line2DImpl::Line2DImpl(std::string listOfLine2DString)
{
	handle = new Line2DImplStore;
	
	if(parseStringToVectorOfLines(listOfLine2DString))
		std::cout << "success" << std::endl;
	else
		std::cout << "failed" << std::endl;
}

Line2DImpl::Line2DImpl(std::ifstream& file)
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
	
	if(parseStringToVectorOfLines(inputString))
		std::cout << "success" << std::endl;
	else
		std::cout << "failed" << std::endl;
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

void Line2DImpl::printAllLines()
{
	/*std::cout<<"(";
	std::vector<RGPHalfSegment2D> x = handle->vectorOfSegments;
	for(auto i = x.begin(); i!=x.end(); i++)
		std::cout<<*i;
	std::cout<<")";*/
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

Line2DImpl Line2DImpl::getBoundingBox()
{
	std::vector<RGPHalfSegment2D> box;
	box = handle->boundingBox;
	Line2DImpl pt(box);
	return pt;
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

bool Line2DImpl::update(Line2DImpl::iterator it, RGPHalfSegment2D rgpSeg2d)
{
	try
    {
		if(isEmptyLine()){
			return false;
		}
		else{
			int index = it.ptr - &(handle->vectorOfSegments[0]);
			handle->vectorOfSegments.erase(handle->vectorOfSegments.begin()+index);
			add(rgpSeg2d);
			lineSort(handle->vectorOfSegments);
		}
    }
    catch(int e)
    {
        return false;
    }
    return true;
}

bool Line2DImpl::remove(Line2DImpl::iterator it)
{
	try
	{
		if(isEmptyLine()){
			return false;
		}
		else{
			int index = it.ptr - &(handle->vectorOfSegments[0]);
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

Line2DImpl Line2DImpl::operator[](int index)
{
	std::vector<RGPHalfSegment2D> t;
	t.push_back(handle->vectorOfSegments[index]);
	Line2DImpl temp(t);
	return temp;
}

Line2DImpl Line2DImpl::operator=(const Line2DImpl &l2d)
{
	handle->vectorOfSegments.clear();
	handle->vectorOfSegments = l2d.handle->vectorOfSegments;
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
	// line2ed format
	// (((a1,b1),(c1,d1)),((a2,b2),(c2,d2)),((a3,b3),(c3,d3)),((a4,b4),(c4,d4)))

	int pos,flag = 0;
	std::string num1,num2,num3,num4;
	std::string s = st;
	std::string delimeter = ",";

	//std::vector<Number> nums;		// unused

	// QUESTION:
	// should we reset vectorOfSegments for any possible changes that
	// may have already happened with push_back() before returning false..?
	// for instance data could be pushed but, then additional data is then
	// formatted incorrectly, possibly corrupting vectorOfSegments ..?
	
	try{
		s.erase(0,1);
		s.erase(s.length()-1,1);
		s.append(",");
		std::cout << s << "\n";
		pos = s.find(delimeter);
		std::string a = "";
		
		while(pos != std::string::npos)
		{
			if(flag == 0){
				s.erase(0,1); // delete starting '('
			}
			else if(flag == 3){
				s.erase(pos-1,1); // delete ending ')'
				flag=-1;
			}
			
			if(flag == 0){
				a = s.substr(0, pos);
			}
			else if(flag == -1){
				a = s.substr(0, pos-1);
			}
			else{
				a = s.substr(0, pos+1);
			}
			
			if(a.length() >= 2)
			{
				try
				{
					if(a[0]=='(' && flag == 0)
					{
						num1 = a.substr(1,a.length()-2);
					}
					else if(!(a.substr(a.length()-2,1)).compare(")") && flag == 1)
					{
						num2 = a.substr(0,a.length()-2);
					}
					else if(a[0]=='(' && flag == 2)
					{
						num3 = a.substr(1,a.length()-2);
					}
					else if(!(a.substr(a.length()-1,1)).compare(")") && flag == -1)
					{
						num4 = a.substr(0,a.length()-1);
            			
						std::cout<<"num1 and num2 is "<<num1<<" "<<num2<<std::endl;
						std::cout<<"num3 and num4 is "<<num3<<" "<<num4<<std::endl;
						
						Number *n1 = new Number(num1);
						Number *n2 = new Number(num2);
						Number *n3 = new Number(num3);
						Number *n4 = new Number(num4);
						
						RGPPoint2D *point1 = new RGPPoint2D(*n1,*n2);
						RGPPoint2D *point2 = new RGPPoint2D(*n3,*n4);
						
						RGPSegment2D seg(*point1,*point2);
						RGPHalfSegment2D halfseg(seg, *point1); // how to decide dominant point (2nd param)?
						
						// Could dominant point be decided based on initial inputted format??
						// ex: (((non-dominant),(dominant)),(non-dominant),(dominant),...)
						
						handle->vectorOfSegments.push_back(halfseg);
					}
					else{
						return false;
					}
				}
				catch(int e){
					return false;
				}
			}
			else
			{
				return false;
			}
			
			if(flag < 1){
				s.erase(0, pos);
			}
			else{
				s.erase(0, pos + delimeter.length());
			}
      		std::cout <<"string s is"<< s << "\n";
			pos = s.find(delimeter);
			flag++;
		}
		return true;
	}
	catch(int e){
		return false;
	}
}