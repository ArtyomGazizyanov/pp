#include "stdafx.h"
#include <string>
#include "FileReader.h"
#include <sstream>
FileReader::FileReader(string filePath)
{
	_filePath = filePath;
	_fileStream = std::ifstream(_filePath);
}

FileReader::~FileReader()
{
}

vector<unsigned int>FileReader::ReadLine()
{
	string line = "";
	if (!getline(_fileStream, line))
	{
		return vector<unsigned int>();
	}
	stringstream stringStream(line);
	istream_iterator<unsigned int> start(stringStream), end;
	vector<unsigned int> tokens(start, end);
	
	return tokens;
}
