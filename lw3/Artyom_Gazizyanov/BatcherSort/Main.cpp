#include "stdafx.h"
#include "BatcherLib.h"
#include <time.h>
#include <chrono>

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		std::cout << "Use: BatcherSort.exe <file name>" << std::endl;

		return 1;
	}

	std::ifstream file(argv[1]);
	if (!file.is_open())
	{
		std::cout << "Can`t open this file\n";

		return 1;
	}

	std::vector<int> data;
	int value;
	while (file >> value)
	{
		data.push_back(value);
	}
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime = std::chrono::high_resolution_clock::now();

	BatcherLib<decltype(data)::value_type>::Sort(data);
	std::chrono::time_point<std::chrono::high_resolution_clock> endTime = std::chrono::high_resolution_clock::now();
	long long timeElapsedInMs = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
	
	std::cout << "Worked : " << timeElapsedInMs << "ms" << std::endl;
	for (auto &el : data)
	{
		std::cout << el << std::endl;
	}

	return 0;
}

