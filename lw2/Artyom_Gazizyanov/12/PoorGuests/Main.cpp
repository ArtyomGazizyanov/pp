#include "stdafx.h"
#include "FileReader.h"
#include "RoomType.h"
#include "Hotel.h"
#include "SimulationHelper.h"
#include <set>

using namespace std;

int main()
{
	FileReader fileReader("input.txt");
	vector<RoomType> roomTypes;
	vector<unsigned int> vectorLine;
	vectorLine = fileReader.ReadLine();
	do
	{
		RoomType roomInfo(vectorLine[0], vectorLine[1]);
		roomTypes.push_back(roomInfo);
		vectorLine = fileReader.ReadLine();
	} while (vectorLine.size() != 0);

	Hotel hotel(roomTypes);
	SimulationHelper simulation;
	simulation.Start(&hotel);

    return 0;
}

