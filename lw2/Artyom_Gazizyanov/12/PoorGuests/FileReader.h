#pragma once
#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
class FileReader
{
public:
	FileReader(string filePath);
	~FileReader();
	vector<unsigned int> ReadLine();
private:
	string _filePath;
	std::ifstream _fileStream;
};
