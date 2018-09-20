class Line2D{
private:
		Private vector<RGPSegment2D> listOfSegments;
public:
	Line2D(); //Empty constructor
	Line2D(vector <RGPSegment2D> listOfSegments);
	Line2D(string listOfLine2DString);
	Line2D(ifstream& file); // Send in file for constructor (possibly .txt)
	~Line2D();
	String getLineString(); // Get the line as human readable ASCII string
};
