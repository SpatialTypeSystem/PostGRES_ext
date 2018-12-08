#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void generateRandomData(int n, int k)
{
  std::string text = "data/input/random_";
  std::string ext = ".txt";
  std::string filename = text + std::to_string(n) + "_" + std::to_string(k) + ext;
  ofstream file;
  file.open(filename);
  for (int j = 0; j < n; j++)
  {
    file << std::to_string(rand() % n) + "," + std::to_string(rand() % n) + "\n";
  }

  file.close();
}

void straightLine(int n, int k)
{
  std::string text = "data/input/straight_";
  std::string ext = ".txt";
  std::string filename = text + std::to_string(n) + "_" + std::to_string(k) + ext;
  ofstream file;
  file.open(filename);
  for (int j = 0; j < n; j++)
  {
    file << std::to_string(j) + "," + std::to_string(j) + "\n";
  }

  file.close();
}

void horizontalLine(int n, int k)
{
  std::string text = "data/input/horizontal_";
  std::string ext = ".txt";
  int y = (rand() % 100) + 1;
  std::string filename = text + std::to_string(n) + "_" + std::to_string(k) + ext;
  ofstream file;
  file.open(filename);
  for (int j = 0; j < n; j++)
  {
    file << std::to_string(j) + "," + std::to_string(y) + "\n";
  }
  file.close();
}

void verticalLine(int n, int k)
{
  std::string text = "data/input/vertical_";
  std::string ext = ".txt";
  int x = (rand() % 100) + 1;
  std::string filename = text + std::to_string(n) + "_" + std::to_string(k) + ext;
  ofstream file;
  file.open(filename);
  for (int j = 0; j < n; j++)
  {
    file << std::to_string(x) + "," + std::to_string(j) + "\n";
  }
  file.close();
}


int main(int argc, char** argv)
{
  // Number of datasets to generate for each type
  int k = atoi(argv[1]);

  // numbers will be generated in the order 10, 100, 1000
  // till it reaches the below MAX_N
  int n = atoi(argv[2]);
  
  std::cout << "K: " << k << " N: " << n << std::endl;
  
  for (int i = 10; i <= n; i *= 10)
  {
    for (int j = 0; j < k; j++)
    {
      straightLine(i, j);
      horizontalLine(i, j);
      verticalLine(i, j);
      generateRandomData(i, j);
    }
  }

  return 0;
}
