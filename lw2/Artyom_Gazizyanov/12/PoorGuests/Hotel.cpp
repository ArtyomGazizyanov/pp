#include "stdafx.h"
#include "Hotel.h"
#include "algorithm"

Hotel::Hotel(std::vector<RoomType> roomTypes)
{
	if (roomTypes.empty())
	{
		throw std::invalid_argument("RoomTypes size can`t be equal to 0");		
	}

	_roomTypes = roomTypes;
	
	for each (RoomType roomType in _roomTypes)
	{
		_unoccupiedNumbers.push_back(std::make_pair(roomType.GetRoomAmmount(), roomType.GetPrice()));
	}

	std::sort(_unoccupiedNumbers.begin(), _unoccupiedNumbers.end());
}

Hotel::~Hotel()
{
}

std::vector<std::pair<unsigned int, unsigned int>>* Hotel::GetUnoccupiedNumbers()
{
	return &_unoccupiedNumbers;
}
