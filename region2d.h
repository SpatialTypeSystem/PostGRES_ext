class Region2D{
private:
  vector<vector<RGPSegment2D>> listOfRegions;
public:
  static bool isValidRegion(Region2d region);
  Region2D(); //Empty constructor
  Region2D(vector<vector<RGPSegment2D>> listOfRegions);
  Region2D(string listOfRegion2DString);
  Region2D(ifstream& file)); // Send in file for constructor (possibly .txt)
  ~Region2D();
  String getRegionString(); // Get the region as human readable ASCII string
  Number area();
};
