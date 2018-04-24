#pragma once
#include "RoomType.h"
#include <set>
#include <vector>
#include <utility>  

class Hotel
{
public:
	Hotel(std::vector<RoomType> roomTypes);
	~Hotel() = default;
	std::vector<std::pair<unsigned int, unsigned int>>* GetUnoccupiedNumbers();
private:
	std::vector<RoomType> _roomTypes;
	std::vector<std::pair<unsigned int, unsigned int>> _unoccupiedNumbers;
};