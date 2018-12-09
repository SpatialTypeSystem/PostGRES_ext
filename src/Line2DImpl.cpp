#include "../include/Line2D.h"
#include "../include/Line2DImpl.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <exception>

struct Line2DImpl::Line2DImplStore {
	std::vector<RGPHalfSegment2D> vectorOfSegments;
	std::vector<RGPSegment2D> boundingBox;
};

//constructor for Line2DImpl iterator
Line2DImpl::iterator::iterator(RGPHalfSegment2D *ptr1)
{
	ptr = ptr1;
}

//overloading * to get output
RGPHalfSegment2D Line2DImpl::iterator::operator*()
{
	return *ptr;
}

//operator overloading ++ (post) for incrementing the iterator
RGPHalfSegment2D Line2DImpl::iterator::operator++(int junk)
{
	RGPHalfSegment2D *ptr1;
	ptr1 = ptr;
	ptr++;
	return *ptr1;
}

//operator overloading ++ (pre) for incrementing the iterator
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

//overloading == to check if two iterators are equal
bool Line2DImpl::iterator::operator==(const iterator &it)
{
	if(it.ptr!=ptr)
		return false;
	return true;
}

//Line2DImpl begin method, return an iterator to the first segment in the sorted order.
Line2DImpl::iterator Line2DImpl::begin()
{
	RGPHalfSegment2D *ptr = &(handle->vectorOfSegments[0]);
	return iterator(ptr);
}

//Line2DImpl begin method, return an iterator to the last segment in the sorted order.
Line2DImpl::iterator Line2DImpl::end()
{
	int t = handle->vectorOfSegments.size();
	return (iterator(&(handle->vectorOfSegments[t-1])));
}

//constructor without arguments, just initializes handle
Line2DImpl::Line2DImpl()
{
	handle = new Line2DImplStore();
}
//Constructors

//constructor which takes in a vector of segments, converts them into half segments and stores it.
Line2DImpl::Line2DImpl(std::vector<RGPSegment2D> listOfSegments)
{
	try{
	handle = new Line2DImplStore;
	std::vector<RGPHalfSegment2D> halfSegments;
	//getting segments and converting them to half segments
	for(auto it = listOfSegments.begin(); it!=listOfSegments.end();it++)
	{
		halfSegments.push_back(RGPHalfSegment2D(*it,(*it).point1));
		halfSegments.push_back(RGPHalfSegment2D(*it,(*it).point2));	
	}
	//sorts all half segments to store a sorted array of segments
	lineSort(halfSegments);
	handle->vectorOfSegments = halfSegments;
	}
	catch(int e)
	{
		std::cout<<"failed"<<std::endl;
		handle->vectorOfSegments.clear();
	}
}

//constructor that takes in a string and creates our required segments
Line2DImpl::Line2DImpl(std::string listOfLine2DString)
{
	handle = new Line2DImplStore;
	
	//pareses string, if successful prints success else prints failed.
	if(parseStringToVectorOfLines(listOfLine2DString))
		std::cout << "success" << std::endl;
	else{
		handle->vectorOfSegments.clear();
		std::cout << "failed" << std::endl;
	}
}

Line2DImpl::~Line2DImpl()
{
	delete handle;
}

// Methods

std::vector<RGPHalfSegment2D> Line2DImpl::getVectorOfSegments()
{
	return handle->vectorOfSegments;
}	

//method to print all the segments in the object
void Line2DImpl::printAllLines()
{
	std::cout<<"(";
	std::vector<RGPHalfSegment2D> x = handle->vectorOfSegments;
	for(auto i = x.begin(); i!=x.end(); i++)
		std::cout<<(*i).segment;
	std::cout<<")";
}

//method to check if our object is empty or has data.
bool Line2DImpl::isEmptyLine()
{
	return handle->vectorOfSegments.empty();
}

//method to get total number of segments in out object
int Line2DImpl::Line2DImpl::getNumberOfSegments()
{
	return (handle->vectorOfSegments.size())/2;
}

//method to find bounding box diagonal for the given list of segments
RGPSegment2D Line2DImpl::getBoundingBox()
{
	//we are computing bounding box every time because it may change after adds, updates or removes
	std::vector<RGPHalfSegment2D> halfSegments;
	halfSegments = handle->vectorOfSegments;

	//p1 is the first point of the bounding box segment
	RGPPoint2D p1(halfSegments[0].segment.point1.x,halfSegments[0].segment.point1.y);
	RGPPoint2D p2(halfSegments[halfSegments.size()-1].segment.point2.x,halfSegments[halfSegments.size()-1].segment.point2.y);
	auto maxy = halfSegments[0].segment.point2.y;

	//iterate through the loop to find max y coordinate in the given lis of points
	for(auto it = halfSegments.begin();it!= halfSegments.end();it++)
	{
		if(maxy<(*it).segment.point1.y)
			maxy = (*it).segment.point1.y;
		if(maxy<(*it).segment.point2.y)
			maxy = (*it).segment.point2.y;	
	}

	//we make the next point taking the x of p2 and maxy found in the above loop
	RGPSegment2D seg(p1,RGPPoint2D(p2.x,maxy));

	//returing the diagonal that tells us the bounding box
	return seg;
}

//method to add new segments to our list of segments
bool Line2DImpl::add(RGPSegment2D rgpSeg2d)
{
	try
	{
		
		//check if the line object is empty
		if(isEmptyLine()){

			//if empty pushback
			handle->vectorOfSegments.push_back(RGPHalfSegment2D(rgpSeg2d,rgpSeg2d.point1));
			handle->vectorOfSegments.push_back(RGPHalfSegment2D(rgpSeg2d,rgpSeg2d.point2));
		}
		else{

			//if not empty, add them and sort the segments in the object
			handle->vectorOfSegments.push_back(RGPHalfSegment2D(rgpSeg2d,rgpSeg2d.point1));
			handle->vectorOfSegments.push_back(RGPHalfSegment2D(rgpSeg2d,rgpSeg2d.point2));
			lineSort(handle->vectorOfSegments);
		}
	}
	catch(int e)
	{
		return false;
	}
	return true;
}

//method to update a segment in our current list of segments
bool Line2DImpl::update(Line2DImpl::iterator it, RGPSegment2D rgpSeg2d)
{
	try
    {
		if(isEmptyLine()){
			//check if empty and return false because we cannot update
			return false;
		}
		else{
			
			//run through the list, find the segment to be updated and remove that segment
			for(std::vector<RGPHalfSegment2D>::iterator i = handle->vectorOfSegments.begin(); i!= handle->vectorOfSegments.end() ; i++)
			{
				if((*i).segment == (*it).segment)
				{
					int index = it.ptr - &(handle->vectorOfSegments[0]);
					handle->vectorOfSegments.erase(handle->vectorOfSegments.begin()+index);
				}	
			}
			//add the new segment and sort it
			handle->vectorOfSegments.push_back(RGPHalfSegment2D(rgpSeg2d,rgpSeg2d.point1));
			handle->vectorOfSegments.push_back(RGPHalfSegment2D(rgpSeg2d,rgpSeg2d.point2));
			lineSort(handle->vectorOfSegments);
		}
    }
    catch(int e)
    {
        return false;
    }
    return true;
}

//method to remove a segment using an iterator
bool Line2DImpl::remove(Line2DImpl::iterator it)
{
	try
	{
		if(isEmptyLine()){

			//return false if the object is empty
			return false;
		}
		else{

			//run a loop through the vector, find and remove the segment.
			for(std::vector<RGPHalfSegment2D>::iterator i = handle->vectorOfSegments.begin(); i!= handle->vectorOfSegments.end() ; i++)
			{
				if((*i).segment == (*it).segment)
				{
					int index = it.ptr - &(handle->vectorOfSegments[0]);
					handle->vectorOfSegments.erase(handle->vectorOfSegments.begin()+index);
				}	
			}
		}
	}
	catch(int e)
	{
		return false;
	}
	return true;
}

//overloading == operator for the Line2DImpl type
bool Line2DImpl::operator==(const Line2DImpl &l2d)
{
	int i = 0;
	if(handle->vectorOfSegments.size() != l2d.handle->vectorOfSegments.size())
	{
		return false;
	}
	
	while(i < l2d.handle->vectorOfSegments.size())
    {
		if(handle->vectorOfSegments[i] != l2d.handle->vectorOfSegments[i])
		{
			return false;
		}
		else
			i++;
	}
	return true;
}

//overloading != operator for the Line2DImpl type
bool Line2DImpl::operator!=(const Line2DImpl &l2d)
{
	int i = 0;
	if(handle->vectorOfSegments.size() != l2d.handle->vectorOfSegments.size())
	{
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

//overloading [] operator for the Line2DImpl type
Line2DImpl Line2DImpl::operator[](int index)
{
	std::vector<RGPSegment2D> t;
	t.push_back(handle->vectorOfSegments[index].segment);
	Line2DImpl temp(t);
	return temp;
}

//overloading = operator for the Line2DImpl type
Line2DImpl Line2DImpl::operator=(const Line2DImpl &l2d)
{
	handle->vectorOfSegments.clear();
	handle->vectorOfSegments = l2d.handle->vectorOfSegments;
}

//merge sort to sort our vector of halfsegments
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

//method to parse a string of segments to make our vector
bool Line2DImpl::parseStringToVectorOfLines(std::string st)
{
	// line2ed format
	// (((a1,b1),(c1,d1)),((a2,b2),(c2,d2)),((a3,b3),(c3,d3)),((a4,b4),(c4,d4)))

	int pos,flag = 0;
	std::string num1,num2,num3,num4;
	std::string s = st;
	std::string delimiter = ",";
	std::vector<RGPSegment2D> segments;
	std::vector<RGPHalfSegment2D> halfSegments;
	
	try{

		//erase first and last (..*) and append a ,
		s.erase(0,1);
		s.erase(s.length()-1,1);
		s.append(",");
		pos = s.find(delimiter);
		std::string a = "";
		
		//keep finding the delimiter and get our required numbers
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
					//find num1, num2, num3, num4
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

						//make the required segments and half segments and push back into a temporary segment and half segment vector
						segments.push_back(RGPSegment2D(RGPPoint2D(Number(num1),Number(num2)),RGPPoint2D(Number(num3),Number(num4))));
						halfSegments.push_back(RGPHalfSegment2D(RGPSegment2D(RGPPoint2D(Number(num1),Number(num2)),RGPPoint2D(Number(num3),Number(num4))),RGPPoint2D(Number(num1),Number(num2))));
						halfSegments.push_back(RGPHalfSegment2D(RGPSegment2D(RGPPoint2D(Number(num1),Number(num2)),RGPPoint2D(Number(num3),Number(num4))),RGPPoint2D(Number(num3),Number(num4))));
						
					}
					else{
						//return false for an erroneous input
						return false;
					}
				}
				catch(int e){
					return false;
				}
			}
			else
			{
				//return false for an erroneous input
				return false;
			}
			//delete till the first delimiter and continue until we get all the segments
			if(flag < 1){
				s.erase(0, pos);
			}
			else{
				s.erase(0, pos + delimiter.length());
			}
			pos = s.find(delimiter);
			flag++;
		}
		//sort the list of half segments obtained and assign them to the vector of segments
		lineSort(halfSegments);
		handle->vectorOfSegments = halfSegments;
		return true;
	}
	catch(int e){
		return false;
	}
}