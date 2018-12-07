#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void generateRandomData(int k, int n)
{
  std::string text = "data/random_";
  std::string ext = ".txt";
  std::string filename = text + std::to_string(k) + "_" + std::to_string(n) + ext;
  ofstream file;
  file.open(filename);
  for (int j = 0; j < n; j++)
  {
    file << std::to_string(rand() % n) + "," + std::to_string(rand() % n) + "\n";
  }

  file.close();
}

void straightLine(int k, int n)
{
  std::string text = "data/straight_";
  std::string ext = ".txt";
  std::string filename = text + std::to_string(k) + "_" + std::to_string(n) + ext;
  ofstream file;
  file.open(filename);
  for (int j = 0; j < n; j++)
  {
    file << std::to_string(j) + "," + std::to_string(j) + "\n";
  }

  file.close();
}

void horizontalLine(int k, int n)
{
  std::string text = "data/horizontal_";
  std::string ext = ".txt";
  int y = (rand() % 100) + 1;
  std::string filename = text + std::to_string(k) + "_" + std::to_string(n) + ext;
  ofstream file;
  file.open(filename);
  for (int j = 0; j < n; j++)
  {
    file << std::to_string(j) + "," + std::to_string(y) + "\n";
  }
  file.close();
}

void verticalLine(int k, int n)
{
  std::string text = "data/vertical_";
  std::string ext = ".txt";
  int x = (rand() % 100) + 1;
  std::string filename = text + std::to_string(k) + "_" + std::to_string(n) + ext;
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
  
  for (int i = 0; i < k; i++)
  {
    for (int j = 10; j <= n; j *= 10)
    {
      straightLine(i, j);
      horizontalLine(i, j);
      verticalLine(i, j);
      generateRandomData(i, j);
    }
  }

  return 0;
}
